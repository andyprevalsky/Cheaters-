CHEATERS

Files that are included:
    1. hash.h
    2. plagiarismCatcher.cpp
    3. makefile

To unzip: unzip prog08_ih4548.zip
          unzip prog08_agp952.zip

To make: make

To run: 
        g++ plagiarismCatcher.cpp   
        ./check file.txt (name of text file)
        *note: the command line takes three inputs, respectively: ./object file name, chunk size, common words lower bound

Additional notes:
    -This program catches similar phrases in the specified number of chunks only once per unique chunk. 
     In other words, if one file has the phrase "hello my name is" and another file has the same phrase TWICE, the program only counts it once.
     -