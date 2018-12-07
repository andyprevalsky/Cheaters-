plagiarismCatcher: plagiarismCatcher.o 
	g++ -o plagiarismCatcher plagiarismCatcher.o 

plagiarismCatcher.o: plagiarismCatcher.cpp
	g++ -c plagiarismCatcher.cpp
