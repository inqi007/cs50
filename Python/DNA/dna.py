from sys import argv, exit
import csv

def main():
    #Checks if there are exactly 3 command line arguments
    if len(argv) != 3:
        print("Usage: python dna.py data.csv sequence.txt")
        exit(1)
    #Opens the csv file
    with open(argv[1], "r") as file:
        #Reads the csv file into memory
        dna_database = csv.reader(file)
        #Stores the csv file as a list
        row = list(dna_database)
    #Opens text file 
    with open(argv[2], 'r') as f:
        #Reads the text file into memory
        sequence = f.read()
    counter = 0
    #Creates a list
    data = list()
    #Counts the number of DNA sequences to be matched 
    for i in range(len(row[0][1:])):
        counter += 1
    #Iterates over all the substrings to be matched
    for j in range(counter):
        #Stores the number of substrings
        number = count_substring(sequence, row[0][j + 1])
        #The total number for each substring is added to a list
        data.append(number)
    
    name = 0
    #Counts the number of rows in the csv file
    line_count = sum(1 for line in row)
    #Starts from the 2nd row of the csv file and goes through all the rows
    for i in range(1, line_count):
        name = 0
        for j in range(counter):
            #Compares the 1st number 
            if data[0] == int(row[i][1]):
                #Compares each individual number
                if data[j] == int(row[i][j + 1]):
                    name += 1
        #Prints the name if all the numbers match
        if name == counter:
            print(row[i][0])
            exit(0)
    if name != counter:
        print("No match")
            
def count_substring(string,sub_string):
    l = len(sub_string)
    count = 0
    number = 0
    for i in range(len(string) - len(sub_string) + 1):
        #Checking if substring is in string
        if(string[i:i + len(sub_string)] == sub_string):      
            count += 1
            #Keeps count of back-to-back substrings
            if (number < count):
                number = count
            #Resets counter if back-to-back substrings do not match
            if(string[i + len(sub_string):i + len(sub_string) + len(sub_string)] != sub_string):
                count = 0
    return number 
    
main()
