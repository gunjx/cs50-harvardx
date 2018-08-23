# README

A collection of programs written in C and Python. The programs are in order from less to more difficult. All programs were created as solutions to the problem sets of Harvard University's online course: CS50's Introduction to Computer Science. In lectures and problem sets the course teaches students how to think algorithmically and solve problems efficiently.

In many cases the CS50 staff provides a rudimentary structure for the solutions. Therefore the programs below are often a mix between code that is provided and my code as part of the solution to the problem sets. More information about CS50: https://docs.cs50.net/2018/spring/syllabus/cscie50.html.

## Cash

A program that calculates the minimum number of coins required to give a user change.

### Theory

When giving change to a customer you likely want to minimize the number of coins you are dispensing. This program does so with a greedy algorithm. The algorithm iteratively reduces the problem with the maximal possible solution until the problem is fully solved.

### Features

The program iteratively reduces the amount owed by the largest possible coin that does not exceed the amount owed until no change is owed anymore. If for example 0.41 USD is owed, the program would calculate that a minimum of 4 coins are needed, i.e. one quarter, one dime, one nickel and one penny.

### Installation & Usage

To ask for user input, the cs50 learning library is used, both in the C and the Python implementation of the program.

For C:
* Make sure the cs50 library is installed. For more information see: https://github.com/cs50/libcs50.
* Run ```make``` (the cs50 library will be linked with the compiler flag -lcs50 and compiled with CLANG).
* Run ```./cash```.
* When asked, type the amount in USD that is owed in change and press return.

For Python:
* Install the cs50 library with ```pip3 install cs50```. For more information see: https://github.com/cs50/python-cs50.
* Run ```python3 cash.py```.
* When asked, type in the amount in USD that is owed in change and press return.

### Learning Goal
Getting familiar with data types, arithmetic operators and loops.

## Crack

A program that cracks passwords with a maximum of five characters.

### Theory

Assuming you somehow got possession of a file in a linux system called /etc/shadow, which contains usernames and hashed passwords, you could attempt to crack the users' passwords using brute force.

Here is an example list of what /etc/shadow might look like (formatting username:hash):\
brian:50mjprEcqC/ts\
stelios:51u8F0dkeDSbY\
maria:509nVI8B9VfuA\
zamyla:50cI2vYkF0YU2\
anushree:50xcIMJ0y.RXo\
natmelo:50JIIyhDORqMU\
rob:50JGnXUgaafgc\
malan:50CcfIk1QrPr6\
lloyd:50n0AAUD.pL8g\
bjbrown:50GApilQSG3E2

Further assumptions:
* Passwords are hashed with C's DES crypt function.
* Each password is no longer than five characters.
* Each password has only alphabetical characters (uppercase and/or lowercase).

### Features

The program takes a hashed password as user input and returns the corresponding password in plaintext by iteratively encrypting (DES crypt function) and comparing all combinations of alphabetical characters with the user input until a match is found.

### Installation & Usage

For C:
* Run ```make```.
* Run ```./crack hash```, where ```hash```is one of the hashed passwords from the above list.
* It can take several minutes for the result to display. Abort with CTRL + C, if needed.

For Python:
* Run ```python3 crack.py hash```, where ```hash```is one of the hashed passwords from the above list.
* The Python implementation runs much slower than the C implementation. It can take considerable time for the result to display. Abort with CTRL + C, if needed.

### Learning Goal

Learning the foundations of functions, variables and scope, arrays and cryptography.

### TODO

* The implementation is done with a five times nested loop and needs refactoring.
* The Python implementation runs an order of magnitude slower than it's counterpart in C. I assume inefficiencies in the code which need to be reworked.

## Fifteen

A program for playing the famous Game of Fifteen.

### Features

The Game of Fifteen or 15-puzzle is a sliding puzzle, played on a two dimensional 4x4 board (though other sizes are possible) with one tile missing. The goal is to move one tile at a time until the board is sorted left to right, top to bottom with the missing tile in the bottom right corner.

### Installation & Usage

* Install the cs50 library. For more information see: https://github.com/cs50/libcs50.
* Run ```make```.
* Run ```./fifteen d``` with ```d``` between 3 and 9 determining the size of the board.
* When asked, type the tile to move and press enter until you won the game. You can always abort with CTRL + C.
* If you can't solve the puzzle and need a cheat, you can redirect the available solutions for 3x3 and 4x4: ```./fifteen 3 < 3x3.txt``` and ```./fifteen 4 < 4x4.txt```.

### Learning Goal

Dividing a large problem into subproblems. Implement one function at a time until the entire problem is solved.

## Find

A program that finds a number among numbers or (in a metaphorical way) a needle in a haystack.

### Features

The program is purely for learning purposes and doesn't solve a particular problem. The program consists of a pseudorandom-number generator and a search function. The number generator uses the function srand48 and uses seconds after Epoch as the seed, if not manually specified. Then the output of srand48 is used as a seed for drand48 to output the numbers for the final haystack. The search function is implemented as tail-recursive binary search with O(log n). Before the search, the hay must be sorted. The sort is implemented as selection sort with O(n^2).

### Installation & Usage

* Run ```make```

1) Search Function
* Run ```./find number```, with ```number``` being the needle you want to find in the haystack (maximum number is 65536).
* Provide numbers for the haystack until you are satisfied and quit with CTRL + D (EOF).

2) Number generator + Search Function
* Run the number generator and pipe the result into the search function: ```generate n [s] | ./find number``` with the amount ```n``` numbers to generate and an optional seed ```s``` (in case you want to prevent random generation).
* Alternatively redirect the number generator's output into a text file and then into the search function (in order to see the actual numbers in the text file): ```generate n [s] | ./find number``` and ```./find number < numbers.txt```.

### Learning Goal

Learn more about makefiles, header files, encapsulation, computational complexity, sorting algorithms, binary search and recursion.

## Music

A program that converts musical notes to frequencies and synthesizes songs.

### Theory

Notes are identified by letters (A through G), accidentals (# and b) and octaves. When the notes are played on an instrument (e.g. piano) sound waves with specific frequencies are generated, the higher the frequency the higher the pitch of the sound you hear. Specific notes correspond to specific sound waves, e.g. the note A4 has a frequency of 440 Hz. The frequencies of one octave’s notes differ from those of adjacent octaves' notes by a factor of two, i.e. A3 is 220 Hz while A5's frequency is 880 Hz. This general rule makes it possible to translate every note into its corresponding frequency.

To ultimately synthesize a song, it is also important to know the duration of a note as well as the duration of rests in a song. These are typically expressed in eights of a note.

With this system you can write down for instance the birthday song:\
D4@1/8
D4@1/8
E4@1/4
D4@1/4
G4@1/4
F#4@1/2
D4@1/8
D4@1/8
E4@1/4
D4@1/4
A4@1/4
G4@1/2
D4@1/8
D4@1/8
D5@1/4
B4@1/4
G4@1/4
F#4@1/4
E4@1/4
C5@1/8
C5@1/8
B4@1/4
G4@1/4
A4@1/4
G4@1/2

### Features

The program takes songs written down in notes and translates them into their corresponding frequencies. After that a WAV file is synthesized with wavfile, a simple sound library by Douglas Thain (more information: https://www3.nd.edu/~dthain/courses/cse20211/fall2013/wavfile/).

### Installation & Usage

* Install the cs50 library. For more information see: https://github.com/cs50/libcs50.
* Run ```make```.
* Run ```./synthesize song.wav``` to synthesize a wav file named song.wav, where you have to manually enter the notes until you press CLTR + D (EOF).
* Run ```./synthesize song.wav < songs/song.txt``` to synthesize a song from a prewritten textfile (e.g. songs/jeopardy.txt).
* Open the file in any with ```open song.wav``` or with any other media player to listen to the newly generated song.

### Learning Goal

Understand among other things the use of exit codes, string concatenation and the use of libraries.

## Recover

A program that recovers JPEGs from a forensic image.

### Theory

Deleted photos on a memory card are not really "deleted" until the memory card is overwritten with new data. This fact makes it possible to recover them. In order to do so a forensic image of the memory card can be created and then searched for a specific 4-byte JPEG signature, which is three specific bytes 0xff 0xd8 0xff plus one from the specific range 0xe0 to 0xef.

Digital cameras store photos back-to-back on memory cards. The cards' file system is often FAT with "blocks" of 512 bytes of data. Because of this the JPEGs signatures will always start with a new block. Thanks to this fact the recovery program can be written much more efficiently by reading chunks of 512 bytes into the buffer and checking only the first four bytes of the chunk before moving on.

Further assumptions:
* If a "block" of 512 bytes was not filled completely by the end of the jpeg file, the slack space in the block consists of only zeros.

### Features

The program reads a forensic image (stored contents bit by bit) of a memory card in blocks into the buffer and checks for JPEG signatures. Every time it finds a signature, the data is saved to a new jpeg file before the search continues. At the end of the search, the user should find all recovered jpegs numerically sorted in the program's folder.

### Installation & Usage

* Run ```make```.
* ```./recover card.raw``` with card.raw being the forensic image to recover.

### Learning Goal

Learn about call stacks, File I/O, pointers, dynamic memory allocation and the hexadecimal system.

## Speller

A program that spell-checks text-files

### Features

The program can spell-check a file after loading a dictionary of words from disk into memory. It then outputs a report of misspelled words as well as how long it took the program to execute and how much memory was in the process.

### Installation & Usage

For C:
* Run ```make```.
* Run ```./speller [dictionary] text``` with the optional argument dictionary in case you want to use your own one (dictionaries/large is standard) and text (e.g. texts/shakespeare.txt) that you want to check for misspellings.

For Python:
* Run ```python3 speller.py [dictionary] text``` with the optional argument dictionary in case you want to use your own one (dictionaries/large is standard) and text (e.g. texts/shakespeare.txt) that you want to check for misspellings.

### Learning Goal

Uncover C structs, custom types definition, data structures, arrays, linked lists, hash tables, tries and some differences between C and Python language.

## Similarities

A program that compares similarities across two files.

### Theory

Determining if two files are identical is just a matter of comparing exactly every character one by one. But determining similarity is non-trivial, because similarity is a matter of definition. Is it that two files have lines in common? Or that the files have sentences in common? Or is it that the files have only substrings in common?

### Features

The program can be used to compare two files line by line, sentence by sentence or substring by substring. It outputs the identical sections according to the type of similarity selected. Furthermore, the program can be run within a web environment where the identical sections are highlighted side by side.

### Installation & Usage

1) In terminal:
* Install the Natural Language Toolkit (NLTK) library, more information here https://www.nltk.org/install.html.
* Run ```./compare --lines FILE1 FILE2```, to compare two files FILE1 and FILE2 line by line.
* Run ```./compare --sentences FILE1 FILE2```, to compare two files FILE1 and FILE2 sentence by sentence.
* Run ```./compare --substrings n FILE1 FILE2```, to compare two files FILE1 and FILE2 substring by substring with length n.

2) With webserver:
* Install the Natural Language Toolkit (NLTK) library, more information here https://www.nltk.org/install.html.
* Install Flask, a Python Microframework, more information under: http://flask.pocoo.org/.
* Start flask server with ```FLASK_APP=application.py flask run```.
* Open http://localhost:5000/ to see the website.
* Upload two files via the form, select the file comparison algorithm and press compare.

### Learning Goal

Getting familiar with Internet primer, IP, TCP, HTTP, HTML, CSS, Bootstrap, Flask, Jinja, language processing, requirements and dependencies.
