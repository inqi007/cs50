import os

from cs50 import SQL
from flask import Flask, flash, jsonify, redirect, render_template, request, session
from flask_session import Session
from tempfile import mkdtemp
from werkzeug.exceptions import default_exceptions, HTTPException, InternalServerError
from werkzeug.security import check_password_hash, generate_password_hash
from datetime import datetime

from helpers import apology, login_required, lookup, usd

# Configure application
app = Flask(__name__)

# Ensure templates are auto-reloaded
app.config["TEMPLATES_AUTO_RELOAD"] = True

# Ensure responses aren't cached
@app.after_request
def after_request(response):
    response.headers["Cache-Control"] = "no-cache, no-store, must-revalidate"
    response.headers["Expires"] = 0
    response.headers["Pragma"] = "no-cache"
    return response

# Custom filter
app.jinja_env.filters["usd"] = usd

# Configure session to use filesystem (instead of signed cookies)
app.config["SESSION_FILE_DIR"] = mkdtemp()
app.config["SESSION_PERMANENT"] = False
app.config["SESSION_TYPE"] = "filesystem"
Session(app)

# Configure CS50 Library to use SQLite database
db = SQL("sqlite:///finance.db")

# Make sure API key is set
if not os.environ.get("API_KEY"):
    raise RuntimeError("API_KEY not set")


@app.route("/")
@login_required
def index():
    """Show portfolio of stocks"""
    name = db.execute("SELECT username FROM users WHERE id = :session", session=session["user_id"])
    rows = db.execute("SELECT * FROM stocks WHERE username = :name", name=name[0]['username'])
    cash = db.execute("SELECT cash FROM users WHERE username = :name", name=name[0]['username'])
    total = db.execute("SELECT SUM(total) FROM stocks WHERE username = :name", name=name[0]['username'])
    total = total[0]["SUM(total)"]
    if total == None:
        total_price = cash[0]["cash"]
    else:
        total_price = total + cash[0]["cash"]
    return render_template("index.html", rows=rows, cash=cash[0]["cash"], total=total_price)

@app.route("/buy", methods=["GET", "POST"])
@login_required
def buy():
    """Buy shares of stock"""
    if request.method == "GET":
        return render_template("buy.html")
    else:
        symbol = request.form.get("stock")
        name = lookup(symbol)["name"]
        if not symbol or name == None:
            return apology("You must provide a correct name.")
        shares = request.form.get("shares")
        if int(shares) < 1 and shares.isnumeric() == False:
            return apology("Provide correct number of shares.")
        exists = False
        price = lookup(symbol)["price"]
        total = float(shares) * float(price)
        money = db.execute("SELECT cash FROM users WHERE id = :session", session=session["user_id"])
        money = money[0]["cash"]
        cash = money - total
        person = db.execute("SELECT username FROM users WHERE id = ?", session["user_id"])
        rows = db.execute("SELECT * FROM stocks WHERE username = :name", name=person[0]['username'])
        for row in rows:
            if symbol == row['symbol'] and person[0]['username'] == row['username']:
                exists = True
        if total > money:
            return apology("Not enough cash.")
        else:
            db.execute("UPDATE users SET cash = ? WHERE id = ?", cash, session["user_id"])
        now = datetime.now()
        db.execute("INSERT INTO history (symbol, shares, price, transacted, username) VALUES(?, ?, ?, ?, ?)",
        symbol, shares, price, now.strftime("%Y-%m-%d %H:%M:%S"), person[0]['username'])
        if exists == False:
            db.execute("INSERT INTO stocks (symbol, name, shares, price, total, username) VALUES (?, ?, ?, ?, ?, ?)",
            symbol, name, shares, price, total, person[0]["username"])
        elif exists == True:
            total_s = db.execute("SELECT total FROM stocks WHERE symbol = ? AND username = ?", symbol, person[0]['username'])
            shares_s = db.execute("SELECT shares FROM stocks WHERE symbol = ? AND username = ?", symbol, person[0]['username'])
            total_s = total_s[0]["total"]
            shares_s = shares_s[0]["shares"]
            new_total = total + total_s
            new_shares = int(shares) + int(shares_s)
            db.execute("UPDATE stocks SET shares = :shares, total = :total WHERE symbol = :symbol AND username = :name",
            shares=new_shares, total=new_total, symbol=symbol, name = person[0]["username"])
        return redirect("/")


@app.route("/history")
@login_required
def history():
    """Show history of transactions"""
    name = db.execute("SELECT username FROM users WHERE id = :session", session=session["user_id"])
    rows = db.execute("SELECT * FROM history WHERE username = ?", name[0]['username'])
    return render_template("history.html", rows=rows)


@app.route("/login", methods=["GET", "POST"])
def login():
    """Log user in"""

    # Forget any user_id
    session.clear()

    # User reached route via POST (as by submitting a form via POST)
    if request.method == "POST":

        # Ensure username was submitted
        if not request.form.get("username"):
            return apology("must provide username", 403)

        # Ensure password was submitted
        elif not request.form.get("password"):
            return apology("must provide password", 403)

        # Query database for username
        rows = db.execute("SELECT * FROM users WHERE username = :username",
                          username=request.form.get("username"))

        # Ensure username exists and password is correct
        if len(rows) != 1 or not check_password_hash(rows[0]["hash"], request.form.get("password")):
            return apology("invalid username and/or password", 403)

        # Remember which user has logged in
        session["user_id"] = rows[0]["id"]

        # Redirect user to home page
        return redirect("/")

    # User reached route via GET (as by clicking a link or via redirect)
    else:
        return render_template("login.html")


@app.route("/logout")
def logout():
    """Log user out"""

    # Forget any user_id
    session.clear()

    # Redirect user to login form
    return redirect("/")


@app.route("/quote", methods=["GET", "POST"])
@login_required
def quote():
    """Get stock quote."""
    if request.method == "GET":
        return render_template("quote.html")
    else:
        symbol = request.form.get("symbol")
        if not symbol:
            return apology("No input")
        name = lookup(symbol)["name"]
        if name == None:
            return apology("Error-can't find stock.")
        price = lookup(symbol)["price"]
        abr = lookup(symbol)["symbol"]
        return render_template("quoted.html", company=name, short=abr, price=price)



@app.route("/register", methods=["GET", "POST"])
def register():
    """Register user"""
    if request.method == "GET":
        return render_template("register.html")
    else:
        name = request.form.get("username")
        if not name:
            return apology("You must provide a name.")
        password = request.form.get("password")
        hash_password = generate_password_hash(password)
        if not password:
            return apology("You must provide a password.")
        confirmation = request.form.get("confirmation")
        if not confirmation:
            return apology("You must confirm password.")
        elif confirmation != password:
            return apology("Passwords do not match.")
        db.execute("INSERT INTO users (username, hash) VALUES (:name, :password)", name=name, password=hash_password)
        return redirect("/login")


@app.route("/sell", methods=["GET", "POST"])
@login_required
def sell():
    """Sell shares of stock"""
    if request.method == "GET":
        return render_template("sell.html")
    else:
        symbol = request.form.get("symbol")
        if not symbol:
            return apology("No input.")
        shares = request.form.get("shares")
        if not shares:
            return apology("No input.")
        exists = False
        person = db.execute("SELECT username FROM users WHERE id = ?", session["user_id"])
        rows = db.execute("SELECT * FROM stocks WHERE username = :name", name=person[0]['username'])
        existing_shares = db.execute("SELECT shares FROM stocks WHERE symbol = ? AND username = ?", symbol, person[0]['username'])
        if int(shares) > int(existing_shares[0]['shares']):
            return apology("Not enough shares.")
        for row in rows:
            if symbol == row['symbol'] and person[0]['username'] == row['username']:
                exists = True
        if exists == False:
            return apology("Share does not exist.")
        elif exists == True:
            total_s = db.execute("SELECT total FROM stocks WHERE symbol = ? AND username = ?", symbol, person[0]['username'])
            shares_s = db.execute("SELECT shares FROM stocks WHERE symbol = ? AND username = ?", symbol, person[0]['username'])
            price_s = db.execute("SELECT price FROM stocks WHERE symbol = ? AND username = ?", symbol, person[0]['username'])
            price_s = price_s[0]['price']
            total_s = total_s[0]["total"]
            shares_s = shares_s[0]["shares"]
            price = lookup(symbol)['price']
            total_for_cash = float(shares) * float(price)
            money = db.execute("SELECT cash FROM users WHERE id = :session", session=session["user_id"])
            money = money[0]["cash"]
            cash = money + total_for_cash
            new_shares = int(shares_s) - int(shares)
            total = float(new_shares) * float(price)
            db.execute("UPDATE users SET cash = ? WHERE id = ?", cash, session["user_id"])
            now = datetime.now()
            negative_shares = -1 * int(shares)
            db.execute("INSERT INTO history (symbol, shares, price, transacted, username) VALUES(?, ?, ?, ?, ?)",
            symbol, negative_shares, price, now.strftime("%Y-%m-%d %H:%M:%S"), person[0]['username'])
            if int(shares) == int(shares_s):
                db.execute("DELETE FROM stocks WHERE symbol = ? AND username = ?", symbol, person[0]['username'])
            else:
                db.execute("UPDATE stocks SET shares = ?, total = ?, price = ? WHERE symbol = ? AND username = ?",
                new_shares, total, price, symbol, person[0]['username'])
        return redirect("/")



def errorhandler(e):
    """Handle error"""
    if not isinstance(e, HTTPException):
        e = InternalServerError()
    return apology(e.name, e.code)


# Listen for errors
for code in default_exceptions:
    app.errorhandler(code)(errorhandler)
