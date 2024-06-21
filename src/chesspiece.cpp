#include "../include/chesspiece.h"

chesspiece::chesspiece() {
    piece = -1;
    color = -1;
    unicode = " ";
}

chesspiece::chesspiece(int p, int c) {
    piece = p;
    color = c;
    if (!color) {
        switch (piece) {
        case 0:
            unicode = "\u2659";
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

void chesspiece::setPos(int x, int y) {
    posX = x;
    posY = y;
}

int chesspiece::getPosX() const {
    return posX;
}

int chesspiece::getPosY() const {
    return posY;
}

std::string chesspiece::getUnicode() const {
    return unicode;
}
