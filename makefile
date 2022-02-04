CFLAGS = -std=c++11 -Wall

huffman: main.o treenode.o
	g++ main.o treenode.o -o huffman $(CFLAGS)

main.o:	main.cpp treenode.h
	g++ -c main.cpp $(CFLAGS)

treenode.o: treenode.cpp treenode.h
	g++ -c treenode.cpp $(CFLAGS)

clean:
	rm *.o huffman
