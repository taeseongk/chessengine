SRC = src
INC = include
TESTS = tests
OBJ = obj

CC = g++
CFLAGS = -std=c++20
EXECUTABLES = printboard

chesspiece.o: $(SRC)/chesspiece.cpp $(INC)/chesspiece.h
	$(CC) $(CFLAGS) -c $<

chessboard.o: $(SRC)/chessboard.cpp $(INC)/chessboard.h
	$(CC) $(CFLAGS) -c $<

printboard: $(TESTS)/printboard.cpp chessboard.o chesspiece.o
	$(CC) $(CFLAGS) -o $@ $< *.o

clean:
	rm -f *.o $(EXECUTABLES)
