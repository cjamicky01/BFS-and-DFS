# homework01 makefile
CC=g++
#CC=g++ -fprofile-arcs -ftest-coverage

homework01: graph.o main.o 
	$(CC) graph.o main.o  -o homework01

graph.o: graph.h graph.cpp
	$(CC) -c graph.cpp

main.o: graph.h main.cpp
	$(CC) -c main.cpp

clean:
	rm *.o *.gcov *.gcda *.gcno  homework03



