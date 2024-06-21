#include "../include/chesspiece.h"

chesspiece::chesspiece() {
    piece = -1;
    color = -1;
    unicode = " ";
}

chesspiece::chesspiece(int p, int c, std::string pos) {
    piece = p;
    color = c;
    position = pos;
    if (!color) {
        switch (piece) {
        case 0:
            unicode = "\u2659";
            hasMoved = false;
            isEnPassant = false;
            break;
        case 1:
            unicode = "\u2656";
            break;
        case 2:
            unicode = "\u2658";
            break;
        case 3:
            unicode = "\u2657";
            break;
        case 4:
            unicode = "\u2655";
            break;
        case 5:
            unicode = "\u2654";
            break;
        default:
            unicode = " ";
            break;
        }
    } else {
        switch (piece) {
        case 0:
            unicode = "\u265f";
            hasMoved = false;
            break;
        case 1:
            unicode = "\u265c";
            break;
        case 2:
            unicode = "\u265e";
            break;
        case 3:
            unicode = "\u265d";
            break;
        case 4:
            unicode = "\u265b";
            break;
        case 5:
            unicode = "\u265a";
            break;
        default:
            unicode = " ";
            break;
        }
    }
}

int chesspiece::getcolor() const {
    return color;
}

int chesspiece::getpiece() const {
    return piece;
}

std::string chesspiece::getposition() const {
    return position;
}

void chesspiece::setpos(std::string pos) {
    position = pos;
}

std::string chesspiece::getunicode() const {
    return unicode;
}

bool chesspiece::gethasmoved() const {
    return hasMoved;
}

void chesspiece::setenpassant() {
    isEnPassant = true;
}

void chesspiece::addmove(std::string move) {
    moves.push_back(move);
}

std::vector<std::string> chesspiece::getmoves() const {
    return moves;
}
