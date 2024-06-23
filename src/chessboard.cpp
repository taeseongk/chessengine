#include "../include/chessboard.h"

chessboard::chessboard() {
    wboard = new chesspiece **[8];
    bboard = new chesspiece **[8];

    for (int i = 0; i < 8; i++) {
        wboard[i] = new chesspiece *[8];
        bboard[i] = new chesspiece *[8];
    }

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
    for (int i = 0; i < 8; i++) {
        for (int j = 0; j < 8; j++) {
            delete wboard[i][j];
        }
        delete[] wboard[i];
        delete[] bboard[i];
    }
    delete[] wboard;
    delete[] bboard;
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

std::string chessboard::inttopos(int color, int x, int y) {
    std::string move = "";
    if (!color) {
        std::string array = "abcdefgh";
        move += array[y];
        move += 8 - x + '0';
    } else {
        std::string array = "hgfedcba";
        move += array[y];
        move += x + 1 + '0';
    }
    return move;
}

void chessboard::calcmoves(int color) {
    std::vector<chesspiece *> pieces = !color ? wpieces : bpieces;
    for (int i = 0; i < pieces.size(); i++) {
        pieces[i]->clearmoves();
        addmoves(pieces[i]);
        checkmoves(pieces[i]);
    }
}

void chessboard::addmoves(chesspiece *piece) {
    int p = piece->getpiece();
    int c = piece->getcolor();
    chesspiece ***board = !c ? wboard : bboard;
    int x;
    int y;
    std::vector<std::pair<int, int>> dir;
    postoint(c, piece->getposition(), x, y);
    switch (p) {
    case 0:
        if (!piece->gethasmoved() && board[x - 1][y]->getpiece() == -1 &&
            board[x - 2][y]->getpiece() == -1) {
            piece->addmove(inttopos(c, x - 2, y));
        }
        if (board[x - 1][y]->getpiece() == -1) {
            piece->addmove(inttopos(c, x - 1, y));
        }
        if (y - 1 >= 0 && board[x - 1][y - 1]->getcolor() == 1 - c) {
            piece->addmove(inttopos(c, x - 1, y - 1));
        }
        if (y + 1 < 8 && board[x - 1][y + 1]->getcolor() == 1 - c) {
            piece->addmove(inttopos(c, x - 1, y + 1));
        }
        break;
    case 1:
        dir = {{-1, 0}, {1, 0}, {0, -1}, {0, 1}};
        break;
    case 2:
        dir = {{-2, -1}, {-2, 1}, {-1, 2},  {1, 2},
               {2, 1},   {2, -1}, {-1, -2}, {1, -2}};
        for (int i = 0; i < dir.size(); i++) {
            int dirX = dir[i].first;
            int dirY = dir[i].second;
            if (x + dirX >= 0 && x + dirX < 8 && y + dirY >= 0 &&
                y + dirY < 8 && board[x + dirX][y + dirY]->getcolor() != c) {
                piece->addmove(inttopos(c, x + dirX, y + dirY));
            }
        }
        break;
    case 3:
        dir = {{-1, -1}, {-1, 1}, {1, 1}, {1, -1}};
        break;
    case 4:
        dir = {{-1, -1}, {-1, 1}, {1, 1},  {1, -1},
               {-1, 0},  {1, 0},  {0, -1}, {0, 1}};
        break;
    case 5:
        dir = {{-1, -1}, {-1, 1}, {1, 1},  {1, -1},
               {-1, 0},  {1, 0},  {0, -1}, {0, 1}};
        for (int i = 0; i < dir.size(); i++) {
            int dirX = dir[i].first;
            int dirY = dir[i].second;
            if (x + dirX >= 0 && x + dirX < 8 && y + dirY >= 0 &&
                y + dirY < 8 && board[x + dirX][y + dirY]->getcolor() != c) {
                piece->addmove(inttopos(c, x + dirX, y + dirY));
            }
        }
        break;
    default:
        break;
    }
    if (p != 0 && p != 2 && p != 5) {
        for (int i = 0; i < dir.size(); i++) {
            int dirX = dir[i].first;
            int dirY = dir[i].second;
            int k = 1;
            while (x + dirX >= 0 && x + dirX < 8 && y + dirY >= 0 &&
                   y + dirY < 8 && board[x + dirX][y + dirY]->getcolor() != c) {
                piece->addmove(inttopos(c, x + dirX, y + dirY));
                if (board[x + dirX][y + dirY]->getcolor() == 1 - c) {
                    break;
                }
                k++;
                dirX = dir[i].first * k;
                dirY = dir[i].second * k;
            }
        }
    }
}

void chessboard::showmoves(int color) {
    std::vector<chesspiece *> pieces = !color ? wpieces : bpieces;
    for (int i = 0; i < pieces.size(); i++) {
        std::cout << pieces[i]->getunicode() << ": ";
        for (int j = 0; j < pieces[i]->getmoves().size(); j++) {
            std::cout << pieces[i]->getmoves()[j] << " ";
        }
        std::cout << std::endl;
    }
}

void chessboard::makemove(chesspiece *piece, std::string move) {
    int p = piece->getpiece();
    int c = piece->getcolor();
    int x;
    int y;
    chesspiece ***board = !c ? wboard : bboard;
    chesspiece ***oboard = !c ? bboard : wboard;
    postoint(c, piece->getposition(), x, y);
    board[x][y] = new chesspiece();
    postoint(1 - c, piece->getposition(), x, y);
    oboard[x][y] = new chesspiece();
    piece->setposition(move);
    postoint(c, move, x, y);
    board[x][y] = piece;
    postoint(1 - c, move, x, y);
    oboard[x][y] = piece;
}

void chessboard::checkmoves(chesspiece *piece) {
    int c = piece->getcolor();
    chesspiece ***board = !c ? wboard : bboard;
    std::vector<std::string> moves = piece->getmoves();
    int size = moves.size();
    for (int i = size - 1; i >= 0; i--) {
        int x;
        int y;
        int newX;
        int newY;
        chesspiece *captured = nullptr;
        postoint(c, piece->getposition(), x, y);
        postoint(c, moves[i], newX, newY);
        board[x][y] = new chesspiece();
        if (board[newX][newY]->getpiece() != -1) {
            captured = board[newX][newY];
        }
        board[newX][newY] = piece;
        piece->setposition(inttopos(c, newX, newY));
        if (ischeck(c)) {
            piece->delmove(moves[i]);
        }
        board[newX][newY] = captured ? captured : new chesspiece();
        board[x][y] = piece;
        piece->setposition(inttopos(c, x, y));
    }
}

bool chessboard::ischeck(int color) {
    std::vector<std::pair<int, int>> dir = {{1, 0}, {-1, 0},  {0, 1},  {0, -1},
                                            {1, 1}, {-1, -1}, {1, -1}, {-1, 1}};
    int x;
    int y;
    chesspiece *king;
    std::vector<chesspiece *> pieces = !color ? wpieces : bpieces;
    chesspiece ***board = !color ? wboard : bboard;
    for (int i = 0; i < pieces.size(); i++) {
        if (pieces[i]->getpiece() == 5) {
            king = pieces[i];
        }
    }
    postoint(color, king->getposition(), x, y);
    for (int i = 0; i < dir.size(); i++) {
        int dirX = dir[i].first;
        int dirY = dir[i].second;
        int k = 1;
        while (x + dirX >= 0 && x + dirX < 8 && y + dirY >= 0 && y + dirY < 8 &&
               board[x + dirX][y + dirY]->getcolor() != color) {
            if (board[x + dirX][y + dirY]->getcolor() == 1 - color) {
                if (board[x + dirX][y + dirY]->getpiece() == 1 && i < 4) {
                    return true;
                } else if (board[x + dirX][y + dirY]->getpiece() == 3 &&
                           i >= 4) {
                    return true;
                } else if (board[x + dirX][y + dirY]->getpiece() == 4) {
                    return true;
                } else if (k == 1 &&
                           board[x + dirX][y + dirY]->getpiece() == 5) {
                    return true;
                }
                break;
            }
            k++;
            dirX = dir[i].first * k;
            dirY = dir[i].second * k;
        }
    }
    dir = {{-2, -1}, {-2, 1}, {-1, 2},  {1, 2},
           {2, 1},   {2, -1}, {-1, -2}, {1, -2}};
    for (int i = 0; i < dir.size(); i++) {
        int dirX = dir[i].first;
        int dirY = dir[i].second;
        if (x + dirX >= 0 && x + dirX < 8 && y + dirY >= 0 && y + dirY < 8 &&
            board[x + dirX][y + dirY]->getcolor() == 1 - color &&
            board[x + dirX][y + dirY]->getpiece() == 2) {
            return true;
        }
    }
    return false;
}

std::vector<chesspiece *> chessboard::getpieces(int color) const {
    return !color ? wpieces : bpieces;
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
                    std::cout << wboard[8 - i][(j - 3) / 6]->getunicode();
                } else {
                    std::cout << bboard[8 - i][(j - 3) / 6]->getunicode();
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
