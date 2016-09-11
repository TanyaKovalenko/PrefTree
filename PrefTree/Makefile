all: Phone_Tree

Phone_Tree: main.o Base_Node.o Node.o List.o List_Node.o
	g++ main.cpp Base_Node.cpp Node.cpp List.cpp List_Node.cpp

main.o: main.cpp
	g++ -c main.cpp

Base_Node.o: Base_Node.cpp
	g++ -c Base_Node.cpp

Node.o: Node.cpp
	g++ -c Node.cpp
	
List.o: List.cpp
	g++ -c List.cpp
	
List_Node.o: List_Node.cpp
	g++ -c List_Node.cpp

clean:
	rm -rf *.o Phone_Tree
