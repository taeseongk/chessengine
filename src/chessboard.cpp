#include "../include/chessboard.h"

chessboard::chessboard() {
    std::string wpositions[16] = {"a2", "b2", "c2", "d2", "e2", "f2",
                                  "g2", "h2", "a1", "b1", "c1", "d1",
                                  "e1", "f1", "g1", "h1"};
    int worder[16] = {0, 0, 0, 0, 0, 0, 0, 0, 1, 2, 3, 4, 5, 3, 2, 1};
    for (int i = 0; i < 16; i++) {
        chesspiece *piece = new chesspiece(worder[i], 0, wpositions[i]);
        int x = -1;
        int y = -1;
        postoint(0, wpositions[i], x, y);
        wboard[x][y] = piece;
        postoint(1, wpositions[i], x, y);
        bboard[x][y] = piece;
        wpieces.push_back(piece);
    }

    std::string bpositions[16] = {"a7", "b7", "c7", "d7", "e7", "f7",
                                  "g7", "h7", "a8", "b8", "c8", "d8",
                                  "e8", "f8", "g8", "h8"};
    int border[16] = {0, 0, 0, 0, 0, 0, 0, 0, 1, 2, 3, 4, 5, 3, 2, 1};
    for (int i = 0; i < 16; i++) {
        chesspiece *piece = new chesspiece(border[i], 1, bpositions[i]);
        int x = -1;
        int y = -1;
        postoint(0, bpositions[i], x, y);
        wboard[x][y] = piece;
        postoint(1, bpositions[i], x, y);
        bboard[x][y] = piece;
        bpieces.push_back(piece);
    }

    for (int i = 2; i <= 5; i++) {
        for (int j = 0; j < 8; j++) {
            wboard[i][j] = new chesspiece();
            bboard[i][j] = new chesspiece();
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

void chessboard::postoint(int color, std::string pos, int &x, int &y) {
    if (!color) {
        x = 8 - (pos[1] - '0');
        y = pos[0] - 'a';
    } else {
        x = ((int)pos[1] - '0') - 1;
        y = 'h' - pos[0];
    }
    return;
}

void chessboard::calcmove(int color) {
    std::vector<chesspiece *> *pieces = !color ? &wpieces : &bpieces;
    for (int i = 0; i < pieces->size(); i++) {}
}

void chessboard::addmoves(chesspiece *piece) {
    /*
        int x = -1;
        int y = -1;
        int c = piece->getColor();
        int p = piece->getPiece();
        postoint(c, ) if (!c) {
            switch (p) {
            case 0:
                if (!piece->getHasMoved()) {
                    if (board[][]) {}
                } else {
                }
                break;
            case 1:
                break;
            case 2:
                break;
            case 3:
                break;
            case 4:
                break;
            case 5:
                break;
            default:
                break;
            }
        }
                 */
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
                    std::cout << wboard[8 - i][(j - 3) / 6]->getUnicode();
                } else {
                    std::cout << bboard[8 - i][(j - 3) / 6]->getUnicode();
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
