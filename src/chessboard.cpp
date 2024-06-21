#include "../include/chessboard.h"

chessboard::chessboard() {
    for (int i = 0; i < 8; i++) {
        chesspiece *wpawn = new chesspiece(0, 0);
        wpawn->setPos(6, i);
        wpieces.push_back(wpawn);
    }
    int wOrder[8] = {1, 2, 3, 4, 5, 3, 2, 1};
    for (int i = 0; i < 8; i++) {
        chesspiece *piece = new chesspiece(wOrder[i], 0);
        piece->setPos(7, i);
        wpieces.push_back(piece);
    }

    for (int i = 0; i < 8; i++) {
        chesspiece *bpawn = new chesspiece(0, 1);
        bpawn->setPos(1, i);
        bpieces.push_back(bpawn);
    }
    int bOrder[8] = {1, 2, 3, 4, 5, 3, 2, 1};
    for (int i = 0; i < 8; i++) {
        chesspiece *piece = new chesspiece(bOrder[i], 1);
        piece->setPos(0, i);
        bpieces.push_back(piece);
    }

    for (int i = 0; i < 8; i++) {
        for (int j = 0; j < 8; j++) {
            if (i == 0) {
                board[0][j] = bpieces[8 + j];
            } else if (i == 1) {
                board[1][j] = bpieces[j];
            } else if (i == 6) {
                board[6][j] = wpieces[j];
            } else if (i == 7) {
                board[7][j] = wpieces[8 + j];
            } else {
                board[i][j] = new chesspiece();
            }
        }
    }
}

chessboard::~chessboard() {
    while (!wpieces.empty()) {
        chesspiece *piece = wpieces.back();
        wpieces.pop_back();
        delete piece;
    }
    while (!bpieces.empty()) {
        chesspiece *piece = bpieces.back();
        bpieces.pop_back();
        delete piece;
    }
}

void chessboard::print(int color) {
    std::string array = !color ? "ABCDEFGH" : "HGFEDCBA";
    int counter = 0;
    std::cout << std::endl;
    std::cout << "  ";
    for (int i = 0; i < 25; i++) {
        std::cout << "# ";
    }
    std::cout << std::endl;
    for (int i = 8; i > 0; i--) {
        if (!color) {
            std::cout << i << " ";
        } else {
            std::cout << 9 - i << " ";
        }
        for (int j = 0; j <= 48; j++) {
            if (j == 0) {
                std::cout << "#";
            } else if (j == 48) {
                std::cout << "#" << std::endl;
            } else if (j % 6 == 0) {
                std::cout << "|";
            } else if ((j - 3) % 6 == 0) {
                if (!color) {
                    std::cout << board[8 - i][(j - 3) / 6]->getUnicode();
                    // std::cout << " ";
                } else {
                    // blackBoard[k][((j - 3) / 6) + 2].printPiece();
                    std::cout << " ";
                }
            } else {
                std::cout << " ";
            }
        }
        if (i != 1) {
            std::cout << "  ";
            for (int j = 0; j <= 48; j++) {
                if (j == 0) {
                    std::cout << "#";
                } else if (j == 48) {
                    std::cout << "#" << std::endl;
                } else if (j % 6 != 0) {
                    std::cout << "-";
                } else {
                    std::cout << " ";
                }
            }
        }
    }
    std::cout << "  ";
    for (int i = 0; i < 25; i++) {
        std::cout << "# ";
    }
    std::cout << std::endl;
    std::cout << "  ";
    for (int i = 0; i <= 48; i++) {
        if ((i - 3) % 6 == 0) {
            std::cout << array[counter];
            counter++;
        } else if (i == 48) {
            std::cout << std::endl;
        } else {
            std::cout << " ";
        }
    }
}
