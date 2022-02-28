output: caso1.o
	g++ caso1.o -o main 
caso1.o: caso1.cpp
	g++ -c caso1.cpp

clean:
	rm *.o main
