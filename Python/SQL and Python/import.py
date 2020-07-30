import csv
import cs50
from sys import argv, exit

if len (argv) != 2:
    print("Error")
    exit(1)

#Open file for SQLite
db = cs50.SQL("sqlite:///students.db")

with open(argv[1], "r") as students:
    reader = csv.DictReader(students)

    for row in reader:
        name = row["name"].split()
        house = row["house"]
        birth = row["birth"]

        if len(name) == 2:
            first = name[0]
            middle = None
            last = name [1]

            db.execute("INSERT INTO students (first, middle, last, house, birth) VALUES(?, ?, ?, ?, ?)",
            first, middle, last, house, birth)


        elif len(name) == 3:
            first = name[0]
            middle = name[1]
            last = name[2]

            db.execute("INSERT INTO students (first, middle, last, house, birth) VALUES(?, ?, ?, ?, ?)",
            first, middle, last, house, birth)
