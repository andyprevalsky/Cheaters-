plagiarismCatcher: plagiarismCatcher.o 
	g++ -o plagiarismCatcher plagiarismCatcher.o 

plagiarismCatcher.o: plagiarismCatcher.cpp hash.h
	g++ -c plagiarismCatcher.cpp
