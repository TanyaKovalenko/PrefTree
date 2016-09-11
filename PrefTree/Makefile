#CC specifies the compiler used to build
CC=g++

#Variable CFLAGS contains flags that are passed to the compiler
CFLAGS=-c -Wall

all: Phone_Tree

Phone_Tree: main.o Base_Node.o Node.o List.o List_Node.o
	$(CC) main.o Base_Node.o Node.o List.o List_Node.o -o Phone_Tree

main.o: main.cpp
	$(CC) $(CFLAGS) main.cpp

Base_Node.o: Base_Node.cpp
	$(CC) $(CFLAGS) Base_Node.cpp

Node.o: Node.cpp
	$(CC) $(CFLAGS) Node.cpp
	
List.o: List.cpp
	$(CC) $(CFLAGS) List.cpp
	
List_Node.o: List_Node.cpp
	$(CC) $(CFLAGS) List_Node.cpp

clean:
	rm -rf *.o Phone_Tree
