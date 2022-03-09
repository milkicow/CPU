CC=g++ 

CFLAGS=-c 


all: asm cpu

asm: assembler_3.0.o ListCircFunctions.o
	$(CC) assembler_3.0.o ListCircFunctions.o -o asm

assembler_3.0.o: assembler_3.0.cpp
	$(CC) $(CFLAGS) assembler_3.0.cpp -o assembler_3.0.o

ListCircFunctions.o: ListCircFunctions.cpp
	$(CC) $(CFLAGS) ListCircFunctions.cpp -o ListCircFunctions.o

cpu: cpu_3.0.o StackFunctions.o
	$(CC) cpu_3.0.o StackFunctions.o -o cpu

cpu_3.0.o: cpu_3.0.cpp 
	$(CC) $(CFLAGS) cpu_3.0.cpp  -o cpu_3.0.o

StackFunctions.o: StackFunctions.cpp
	$(CC) $(CFLAGS) StackFunctions.cpp  -o StackFunctions.o

clean: 
	rm -rf *.o cpu