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
    hasMoved = false;
    switch (p) {
    case 0:
        unicode = !c ? "\u2659" : "\u265f";
        isEnPassant = false;
        break;
    case 1:
        unicode = !c ? "\u2656" : "\u265c";
        break;
    case 2:
        unicode = !c ? "\u2658" : "\u265e";
        break;
    case 3:
        unicode = !c ? "\u2657" : "\u265d";
        break;
    case 4:
        unicode = !c ? "\u2655" : "\u265b";
        break;
    case 5:
        unicode = !c ? "\u2654" : "\u265a";
        break;
    default:
        unicode = " ";
        break;
    }
}

int chesspiece::getcolor() const {
    return color;
}

int chesspiece::getpiece() const {
    return piece;
}

void chesspiece::setpiece(int p) {
    piece = p;
}

std::string chesspiece::getposition() const {
    return position;
}

void chesspiece::setposition(std::string pos) {
    position = pos;
}

std::string chesspiece::getunicode() const {
    return unicode;
}

void chesspiece::setunicode(int p, int c) {
    switch (p) {
    case 0:
        unicode = !c ? "\u2659" : "\u265f";
        break;
    case 1:
        unicode = !c ? "\u2656" : "\u265c";
        break;
    case 2:
        unicode = !c ? "\u2658" : "\u265e";
        break;
    case 3:
        unicode = !c ? "\u2657" : "\u265d";
        break;
    case 4:
        unicode = !c ? "\u2655" : "\u265b";
        break;
    case 5:
        unicode = !c ? "\u2654" : "\u265a";
        break;
    default:
        unicode = " ";
        break;
    }
}

bool chesspiece::gethasmoved() const {
    return hasMoved;
}

void chesspiece::sethasmoved() {
    hasMoved = true;
}

void chesspiece::setenpassant(bool value) {
    isEnPassant = value;
}

bool chesspiece::getenpassant() const {
    return isEnPassant;
}

void chesspiece::addmove(std::string move) {
    moves.push_back(move);
}

void chesspiece::delmove(std::string move) {
    for (int i = 0; i < this->moves.size(); i++) {
        if (this->moves[i] == move) {
            this->moves.erase(this->moves.begin() + i);
        }
    }
}

std::vector<std::string> chesspiece::getmoves() const {
    return moves;
}

void chesspiece::clearmoves() {
    moves.clear();
}
