C11FLAG=-std=c++11

all: main

clean:
	rm matrix.o nn.o main

main: main.o nn.o matrix.o 
	g++ -o main main.o nn.o matrix.o

main.o: nn.o main.cc nn.h matrix.h
	g++ -c main.cc $(C11FLAG) 

nn.o: nn.cc nn.h matrix.h
	g++ -c nn.cc $(C11FLAG) 

matrix.o: matrix.cc matrix.h
	g++ -c matrix.cc $(C11FLAG)


