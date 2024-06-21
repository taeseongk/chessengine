SRC = src
INC = include
OBJ = obj

CC = g++
CFLAGS = -std=c++20
EXECUTABLES = test 

chesspiece.o: $(SRC)/chesspiece.cpp $(INC)/chesspiece.h
	$(CC) $(CFLAGS) -c $<

chessboard.o: $(SRC)/chessboard.cpp $(INC)/chessboard.h
	$(CC) $(CFLAGS) -c $<

test: test.cpp chessboard.o chesspiece.o
	$(CC) $(CFLAGS) -o $@ $< *.o

clean:
	rm -f *.o $(EXECUTABLES)
