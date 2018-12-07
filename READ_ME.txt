CHEATERS

by: Andy Prevalsky and Iris Ham

Files that are included:
    1. hash.h
    2. plagiarismCatcher.cpp
    3. makefile

To unzip: unzip cheaters_ih4548.zip
          unzip cheaters_agp952.zip

To make: make

To run: 
        ex: ./plagiarismCatcher ./directory name/ # #
        *note: the command line takes four inputs, respectively: ./object file name, path to directory, chunk size, common words lower bound
        *the # stand for positive integers as defined above (the program assumes that only positive integers will be inputed)

How the program works:
    -files are read from the second argument in command line
    -the command line specifies the chunk size and the lower bound of common words as well
    -the program finds all the matching chunks and keeps count of them between two files
    -the output of this program is the number of matches between two files (if they satisfy the lower bound) in order from highest number of matches to lowest


Additional notes:
    -This program catches similar phrases in the specified number of chunks only once per unique chunk. 
     In other words, if one file has the phrase "hello my name is" and another file has the same phrase TWICE, the program only counts it once.
    -the medium and large files don't work because this program
    -medium file takes about 