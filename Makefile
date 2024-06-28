SRC = src
INC = include
OBJ = obj
TESTS = tests
BIN = bin

CC = g++
CFLAGS = -std=c++20

all: $(BIN)

test: $(BIN)/test
	./$(BIN)/test

parser: $(BIN)/parser
	./$(BIN)/parser

chessgame: $(BIN)/chessgame
	./$(BIN)/chessgame

$(OBJ):
	mkdir -p $(OBJ)

$(BIN):
	mkdir -p $(BIN)

$(OBJ)/parser.o: $(SRC)/parser.cpp $(INC)/parser.h | $(OBJ)
	$(CC) $(CFLAGS) -c $< -o $@

$(OBJ)/chessgame.o: $(SRC)/chessgame.cpp $(INC)/chessgame.h $(SRC)/chessboard.cpp $(INC)/chessboard.h | $(OBJ)
	$(CC) $(CFLAGS) -c $< -o $@

$(OBJ)/chessboard.o: $(SRC)/chessboard.cpp $(INC)/chessboard.h | $(OBJ)
	$(CC) $(CFLAGS) -c $< -o $@

$(OBJ)/chesspiece.o: $(SRC)/chesspiece.cpp $(INC)/chesspiece.h | $(OBJ)
	$(CC) $(CFLAGS) -c $< -o $@

$(BIN)/test: $(TESTS)/test.cpp $(OBJ)/parser.o $(OBJ)/chessgame.o $(OBJ)/chessboard.o $(OBJ)/chesspiece.o | $(BIN)
	$(CC) $(CFLAGS) -o $@ $^

$(BIN)/parser: $(TESTS)/parsertest.cpp $(OBJ)/parser.o $(OBJ)/chessgame.o $(OBJ)/chessboard.o $(OBJ)/chesspiece.o | $(BIN)
	$(CC) $(CFLAGS) -o $@ $^

$(BIN)/chessgame: $(TESTS)/gametest.cpp $(OBJ)/chessgame.o $(OBJ)/chessboard.o $(OBJ)/chesspiece.o | $(BIN)
	$(CC) $(CFLAGS) -o $@ $^

clean:
	rm -f $(OBJ)/*.o $(BIN)/*

.PHONY: all clean
