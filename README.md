# CS50
All of these are assignments done for the online course CS50's Introduction to Computer Science by Harvard. 

**Python**
1) Mario

This is a program used to display the following:

       #     
      ##    
     ###   
    ####   
    
The number of rows and columns created depends on the input. For eg. if the input is 4, you get the shape provided above.

2) Cash

This is a program that calculates how many coins a customer is owed based on the change that is owed. For example, if a customer is owed 41 cents, then the printed value will be 4 given 25 cents + 10 cents + 5 cents + 1 cent= 41 cents. We are only only to use 25, 10, 5 and 1 cents. 

3) Readability

This is a program that reads a text and determines for which grade this text is applicable. We were provided with a formula to determine this value using the
number of words, sentences and letters in a text.
For eg.

Text: Congratulations! Today is your day. You're off to Great Places! You're off and away!

Grade 3

Text: As the average number of letters and words per sentence increases, the Coleman-Liau index gives the text a higher reading level. If you were to take this paragraph, for instance, which has longer words and sentences than either of the prior two examples, the formula would give the text an eleventh grade reading level.

Grade 11

The text is the input and the grade is the output.

4) DNA

This is a program that will take a sequence of DNA and a CSV file containing STR counts for a list of individuals and then output
to whom the DNA (most likely) belongs. The CSV files and the DNA sequences were provided. 
For more details on how this program works, visit the following page - https://cs50.harvard.edu/x/2020/psets/6/dna/

5) SQL and Python

This is a program that imports student data into a database from a CSV file and then produces class rosters.
Characters.csv and students.db were already provided. This is how it works:

$ python import.py characters.csv

$ python roster.py Gryffindor

Lavender Brown, born 1979

Colin Creevey, born 1981

Seamus Finnigan, born 1979

Hermione Jean Granger, born 1979

Neville Longbottom, born 1980

Parvati Patil, born 1979

Harry James Potter, born 1980

Dean Thomas, born 1980

Romilda Vane, born 1981

Ginevra Molly Weasley, born 1981

Ronald Bilius Weasley, born 1980 


**Web_Development**

Languages used: Python, Flask, Jinja, HTML/CSS

Program: A website via which users can “buy” and “sell” stocks. 

Check 0:10 to 2:30 of the following video to understand how this website works- https://www.youtube.com/watch?v=kAvCTffbH04&list=PLhQjrBD2T382xHP1dYqfF6kRqL7xBTQNJ&index=10&t=0s

Files already provided- layout.html, login.html, helpers.py, login/logout routes within application.py, finance.db

**C**
1) Caesar

A program that encrypts messages using Caesar’s cipher, per the following example:

$ ./caesar 13
plaintext:  HELLO
ciphertext: URYYB

Ceasar's cipher encrypts messages by shifting each letter therein by some number of places. 

2) Substitution

Implements a substitution cipher, per the following example:

$ ./substitution JTREKYAVOGDXPSNCUIZLFBMWHQ
plaintext:  HELLO
ciphertext: VKXXN

In a substitution cipher, we “encrypt” a message by replacing every letter with another letter. To do so, we use a key: in this case, a mapping of each of the letters of the alphabet to the letter it should correspond to when we encrypt it.

3) Credit

A program that identifies the type of a credit card. For eg:

$ ./credit
Number: 4003600000000014
VISA

$ ./credit
Number: 6176292929
INVALID

4) Plurality

A program that runs a plurality election. For eg:

$ ./plurality Alice Bob Charlie
Number of voters: 4
Vote: Alice
Vote: Bob
Vote: Charlie
Vote: Alice
Alice

5) Runoff

A program that runs a runoff election. For eg:

./runoff Alice Bob Charlie
Number of voters: 5
Rank 1: Alice
Rank 2: Bob
Rank 3: Charlie

Rank 1: Alice
Rank 2: Charlie
Rank 3: Bob

Rank 1: Bob
Rank 2: Charlie
Rank 3: Alice

Rank 1: Bob
Rank 2: Alice
Rank 3: Charlie

Rank 1: Charlie
Rank 2: Alice
Rank 3: Bob

Alice

6) Filter

A program that applies filters to BMPs. Filters implemented are Grayscale, Sepia, Reflection and Blur. 
File provided was filter.c . File worked on is helpers.c

7) Speller

A program that spell-checks a file using a hash table. 

Files provided were speller.c , dictionaries and texts. File worked on is dictionaries.c . 


