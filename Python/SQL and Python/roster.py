from sys import argv, exit
import csv
import cs50

if len(argv) != 2:
    print("Error")
    exit()

db = cs50.SQL("sqlite:///students.db")

list = db.execute("SELECT first, middle, last, birth FROM students WHERE house = ? ORDER BY last, first ASC", argv[1])

for row in list:
    if row["middle"] == None:
        print(row["first"] + " " + row["last"] + ", born " + str(row["birth"]))
    else:
        print(row["first"] + " " + row["middle"] + " " + row["last"] + ", born " + str(row["birth"]))
