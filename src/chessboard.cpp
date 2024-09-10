#include "../include/chessboard.h"

chessboard::chessboard() {
    wboard = new chesspiece **[8];
    bboard = new chesspiece **[8];
    for (int i = 0; i < 8; i++) {
        wboard[i] = new chesspiece *[8];
        bboard[i] = new chesspiece *[8];
    }
    for (int i = 0; i < 8; i++) {
        for (int j = 0; j < 8; j++) {
            wboard[i][j] = bboard[i][j] = nullptr;
        }
    }
    std::string wpositions[16] = {"a2", "b2", "c2", "d2", "e2", "f2",
                                  "g2", "h2", "a1", "b1", "c1", "d1",
                                  "e1", "f1", "g1", "h1"};
    int worder[16] = {0, 0, 0, 0, 0, 0, 0, 0, 1, 2, 3, 4, 5, 3, 2, 1};
    for (int i = 0; i < 16; i++) {
        chesspiece *piece = new chesspiece(worder[i], 0, wpositions[i]);
        setpiece(0, piece, wpositions[i]);
        wpieces.push_back(piece);
    }
    std::string bpositions[16] = {"a7", "b7", "c7", "d7", "e7", "f7",
                                  "g7", "h7", "a8", "b8", "c8", "d8",
                                  "e8", "f8", "g8", "h8"};
    int border[16] = {0, 0, 0, 0, 0, 0, 0, 0, 1, 2, 3, 4, 5, 3, 2, 1};
    for (int i = 0; i < 16; i++) {
        chesspiece *piece = new chesspiece(border[i], 1, bpositions[i]);
        setpiece(1, piece, bpositions[i]);
        bpieces.push_back(piece);
    }
    std::string emptypositions[32] = {
        "a3", "b3", "c3", "d3", "e3", "f3", "g3", "h3", "a4", "b4", "c4",
        "d4", "e4", "f4", "g4", "h4", "a5", "b5", "c5", "d5", "e5", "f5",
        "g5", "h5", "a6", "b6", "c6", "d6", "e6", "f6", "g6", "h6"};
    for (int i = 0; i < 32; i++) {
        setpiece(0, new chesspiece(), emptypositions[i]);
    }
}

chessboard::~chessboard() {
    for (int i = 0; i < 8; i++) {
        for (int j = 0; j < 8; j++) {
            wboard[i][j] = nullptr;
            delete wboard[i][j];
        }
    }
    for (int i = 0; i < 8; i++) {
        for (int j = 0; j < 8; j++) {
            if (bboard[i][j] && bboard[i][j]->getpiece() == -1) {
                delete bboard[i][j];
            }
        }
    }
    for (int i = 0; i < 8; i++) {
        delete wboard[i];
        delete bboard[i];
    }
    delete wboard;
    delete bboard;
    for (int i = 0; i < wpieces.size(); i++) {
        if (wpieces[i]) {
            delete wpieces[i];
        }
    }
    for (int i = 0; i < bpieces.size(); i++) {
        if (bpieces[i]) {
            delete bpieces[i];
        }
    }
}

chesspiece ***chessboard::getboard(int color) const {
    return !color ? wboard : bboard;
}

std::vector<chesspiece *> chessboard::getpieces(int color) const {
    return !color ? wpieces : bpieces;
}

chesspiece *chessboard::findpiece(int color, int piece, std::string pos) {
    std::vector<chesspiece *> *pieces = !color ? &wpieces : &bpieces;
    for (int i = 0; i < pieces->size(); i++) {
        chesspiece *p = (*pieces)[i];
        if (piece == 5 && p->getpiece() == 5) {
            return p;
        } else if (piece != 5 && p->getposition() == pos) {
            return p;
        }
    }
    return nullptr;
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

void chessboard::genmoves(int color) {
    std::vector<chesspiece *> *pieces = !color ? &wpieces : &bpieces;
    for (int i = 0; i < pieces->size(); i++) {
        chesspiece *piece = (*pieces)[i];
        if (piece->getpiece() == -1) {
            continue;
        }
        piece->clearmoves();
        addmoves(piece);
        checkmoves(piece);
    }
}

void chessboard::addmoves(chesspiece *piece) {
    int p = piece->getpiece(), c = piece->getcolor();
    chesspiece ***board = !c ? wboard : bboard;
    int x, y;
    std::vector<std::pair<int, int>> dir;
    postoint(c, piece->getposition(), x, y);
    switch (p) {
    case 0:
        if (!piece->gethasmoved() && board[x - 1][y]->getpiece() == -1 &&
            board[x - 2][y]->getpiece() == -1) {
            piece->addmove(inttopos(c, x - 2, y));
        }
        if (board[x - 1][y]->getpiece() == -1) {
            if (x - 1 == 0) {
                piece->addmove(inttopos(c, x - 1, y) + "=Q");
                piece->addmove(inttopos(c, x - 1, y) + "=R");
                piece->addmove(inttopos(c, x - 1, y) + "=B");
                piece->addmove(inttopos(c, x - 1, y) + "=N");
            } else {
                piece->addmove(inttopos(c, x - 1, y));
            }
        }
        if (y - 1 >= 0 && board[x - 1][y - 1]->getcolor() == 1 - c) {
            if (x - 1 == 0) {
                piece->addmove(inttopos(c, x - 1, y - 1) + "=Q");
                piece->addmove(inttopos(c, x - 1, y - 1) + "=R");
                piece->addmove(inttopos(c, x - 1, y - 1) + "=B");
                piece->addmove(inttopos(c, x - 1, y - 1) + "=N");
            } else {
                piece->addmove(inttopos(c, x - 1, y - 1));
            }
        }
        if (y + 1 < 8 && board[x - 1][y + 1]->getcolor() == 1 - c) {
            if (x - 1 == 0) {
                piece->addmove(inttopos(c, x - 1, y + 1) + "=Q");
                piece->addmove(inttopos(c, x - 1, y + 1) + "=R");
                piece->addmove(inttopos(c, x - 1, y + 1) + "=B");
                piece->addmove(inttopos(c, x - 1, y + 1) + "=N");
            } else {
                piece->addmove(inttopos(c, x - 1, y + 1));
            }
        }
        if (y - 1 >= 0 && board[x][y - 1]->getcolor() == 1 - c &&
            board[x][y - 1]->getenpassant()) {
            piece->addmove(inttopos(c, x - 1, y - 1));
        }
        if (y + 1 < 8 && board[x][y + 1]->getcolor() == 1 - c &&
            board[x][y + 1]->getenpassant()) {
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
            int dirX = dir[i].first, dirY = dir[i].second;
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
            int dirX = dir[i].first, dirY = dir[i].second;
            if (x + dirX >= 0 && x + dirX < 8 && y + dirY >= 0 &&
                y + dirY < 8 && board[x + dirX][y + dirY]->getcolor() != c) {
                piece->addmove(inttopos(c, x + dirX, y + dirY));
            }
        }
        if (cancastle(c, 0)) {
            piece->addmove("O-O");
        }
        if (cancastle(c, 1)) {
            piece->addmove("O-O-O");
        }
        break;
    default:
        break;
    }
    if (p != 0 && p != 2 && p != 5) {
        for (int i = 0; i < dir.size(); i++) {
            int dirX = dir[i].first, dirY = dir[i].second;
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
    std::vector<chesspiece *> *pieces = !color ? &wpieces : &bpieces;
    for (int i = 0; i < pieces->size(); i++) {
        chesspiece *piece = (*pieces)[i];
        if (piece->getpiece() == -1) {
            continue;
        }
        std::cout << piece->getunicode() << "(" << piece->getposition()
                  << "): ";
        std::vector<std::string> moves = piece->getmoves();
        for (int j = 0; j < moves.size(); j++) {
            std::cout << moves[j] << " ";
        }
        std::cout << std::endl;
    }
}

void chessboard::makemove(chesspiece *piece, std::string move, movedata *data) {
    int p = piece->getpiece(), c = piece->getcolor();
    data->color = c;
    data->move = move;
    data->index = -1;
    data->size = 0;
    setenpassant(c, data);
    if (p == 0) {
        std::string str = move.substr(move.length() - 2, 2);
        if (str.substr(0, 1) == "=") {
            dopawnmove(piece, move.substr(0, 2), data, true);
        }
        if (str == "=Q") {
            dopromotion(piece, 4, move.substr(0, 2), data);
        } else if (str == "=R") {
            dopromotion(piece, 1, move.substr(0, 2), data);
        } else if (str == "=N") {
            dopromotion(piece, 2, move.substr(0, 2), data);
        } else if (str == "=B") {
            dopromotion(piece, 3, move.substr(0, 2), data);
        } else {
            dopawnmove(piece, move.substr(0, 2), data, false);
        }
    } else if (move == "O-O") {
        docastle(c, 0, data);
    } else if (move == "O-O-O") {
        docastle(c, 1, data);
    } else {
        movepiece(piece, move, data, false);
    }
}

void chessboard::checkmoves(chesspiece *piece) {
    int c = piece->getcolor();
    chesspiece ***board = !c ? wboard : bboard;
    std::vector<std::string> moves = piece->getmoves();
    int size = moves.size();
    for (int i = size - 1; i >= 0; i--) {
        std::string move = moves[i];
        if (move == "O-O" || move == "O-O-O") {
            continue;
        } else if (move.length() > 2) {
            move = move.substr(0, 2);
        }
        int x, y;
        int newX, newY;
        bool capture = false, ep = false;
        chesspiece *captured = nullptr;
        postoint(c, piece->getposition(), x, y);
        postoint(c, move, newX, newY);
        setpiece(c, new chesspiece(), piece->getposition());
        if (board[newX][newY]->getpiece() != -1) {
            captured = board[newX][newY];
            capture = true;
        } else if (piece->getpiece() == 0 &&
                   board[x][newY]->getcolor() == 1 - c &&
                   board[x][newY]->getenpassant()) {
            captured = board[x][newY];
            ep = true;
        }
        setpiece(c, piece, move);
        if (ep) {
            setpiece(c, new chesspiece(), inttopos(c, x, newY));
        }
        chesspiece *king = findpiece(c, 5, "");
        if (ischeck(c, king->getposition())) {
            piece->delmove(i);
        }
        if (ep) {
            setpiece(c, new chesspiece(), move);
            setpiece(c, captured, inttopos(c, x, newY));
        } else if (capture) {
            setpiece(c, captured, move);
        } else {
            setpiece(c, new chesspiece(), move);
        }
        setpiece(c, piece, inttopos(c, x, y));
    }
}

void chessboard::movepiece(chesspiece *piece, std::string move, movedata *data,
                           bool ispromo) {
    int c = piece->getcolor();
    chesspiece ***board = !c ? wboard : bboard;
    setpiece(c, new chesspiece(), piece->getposition());
    int j = -1;
    for (int i = 0; i < data->size; i++) {
        if (data->oldpieces[i]->position == piece->getposition()) {
            j = i;
            break;
        }
    }
    if (j == -1) {
        data->oldpieces[data->size++] = makepiece(piece);
    }
    int x, y;
    postoint(c, move, x, y);
    if (board[x][y]->getpiece() != -1) {
        removepiece(c, move, data);
    }
    setpiece(c, piece, move);
    if (piece->getpiece() == 0 && !piece->gethasmoved() &&
        ((!c && move[1] == '4') || (c && move[1] == '5'))) {
        piece->setenpassant(true);
    }
    piece->sethasmoved(true);
    if (j == -1 && !ispromo) {
        data->newpieces[data->size - 1] = makepiece(piece);
    } else if (j != -1 && !ispromo) {
        delete data->newpieces[j];
        data->newpieces[j] = makepiece(piece);
    }
}

void chessboard::setpiece(int color, chesspiece *piece, std::string square) {
    chesspiece ***board = !color ? wboard : bboard;
    chesspiece ***oboard = !color ? bboard : wboard;
    int x, y;
    chesspiece *blank = nullptr;
    postoint(color, square, x, y);
    if (board[x][y] && board[x][y]->getpiece() == -1) {
        blank = board[x][y];
    }
    board[x][y] = piece;
    postoint(1 - color, square, x, y);
    oboard[x][y] = piece;
    piece->setposition(square);
    if (blank) {
        delete blank;
    }
}

void chessboard::changepiece(chesspiece *piece, chesspiece oldpiece) {
    piece->setpiece(oldpiece.getpiece());
    piece->setunicode(oldpiece.getpiece(), oldpiece.getcolor());
    piece->setposition(oldpiece.getposition());
    piece->sethasmoved(oldpiece.gethasmoved());
    piece->setenpassant(oldpiece.getenpassant());
    piece->clearmoves();
}

void chessboard::changepiece(chesspiece *piece, ::piece *oldpiece) {
    piece->setpiece(oldpiece->piece);
    piece->setunicode(oldpiece->piece, oldpiece->color);
    piece->setposition(oldpiece->position);
    piece->sethasmoved(oldpiece->hasMoved);
    piece->setenpassant(oldpiece->isEnPassant);
    piece->clearmoves();
}

::piece *chessboard::makepiece(chesspiece *piece) {
    ::piece *p = new ::piece;
    p->piece = piece->getpiece();
    p->color = piece->getcolor();
    p->position = piece->getposition();
    p->hasMoved = piece->gethasmoved();
    p->isEnPassant = piece->getenpassant();
    return p;
}

bool chessboard::ischeck(int color, std::string pos) {
    std::vector<std::pair<int, int>> dir = {{1, 0}, {-1, 0},  {0, 1},  {0, -1},
                                            {1, 1}, {-1, -1}, {1, -1}, {-1, 1}};
    int x, y;
    chesspiece ***board = !color ? wboard : bboard;
    postoint(color, pos, x, y);
    if ((x - 1 >= 0 && y - 1 >= 0 && board[x - 1][y - 1]->getpiece() == 0 &&
         board[x - 1][y - 1]->getcolor() == 1 - color) ||
        (x - 1 >= 0 && y + 1 < 8 && board[x - 1][y + 1]->getpiece() == 0 &&
         board[x - 1][y + 1]->getcolor() == 1 - color)) {
        return true;
    }
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

bool chessboard::cancastle(int color, int kq) {
    chesspiece ***board = !color ? wboard : bboard;
    std::vector<std::vector<std::string>> rPos = {{"h1", "a1"}, {"h8", "a8"}};
    std::string kPos = !color ? "e1" : "e8";
    chesspiece *rook = findpiece(color, 1, rPos[color][kq]);
    chesspiece *king = findpiece(color, 5, kPos);
    if (!rook || !king || rook->gethasmoved() || king->gethasmoved()) {
        return false;
    }
    std::vector<std::vector<std::string>> sq = {
        {"f1", "g1"}, {"d1", "c1", "b1"}, {"f8", "g8"}, {"d8", "c8", "b8"}};
    std::vector<std::string> sqs = sq[kq + (2 * color)];
    for (int i = 0; i < sqs.size(); i++) {
        int x, y;
        postoint(color, sqs[i], x, y);
        if (i < 2 && ischeck(color, sqs[i])) {
            return false;
        }
        if (board[x][y]->getpiece() != -1) {
            return false;
        }
    }
    return true;
}

void chessboard::docastle(int color, int kq, movedata *data) {
    std::vector<std::vector<std::string>> sq = {
        {"f1", "g1"}, {"d1", "c1", "b1"}, {"f8", "g8"}, {"d8", "c8", "b8"}};
    std::vector<std::string> sqs = sq[kq + (2 * color)];
    std::vector<std::vector<std::string>> rPos = {{"h1", "a1"}, {"h8", "a8"}};
    std::string kPos = !color ? "e1" : "e8";
    chesspiece *rook = findpiece(color, 1, rPos[color][kq]);
    chesspiece *king = findpiece(color, 5, "");
    movepiece(rook, sqs[0], data, false);
    movepiece(king, sqs[1], data, false);
}

void chessboard::dopawnmove(chesspiece *piece, std::string move, movedata *data,
                            bool ispromo) {
    int c = piece->getcolor();
    chesspiece ***board = !c ? wboard : bboard;
    int x, y;
    movepiece(piece, move, data, ispromo);
    postoint(c, move, x, y);
    if (board[x + 1][y]->getcolor() == 1 - c &&
        board[x + 1][y]->getenpassant()) {
        removepiece(c, inttopos(c, x + 1, y), data);
    }
}

void chessboard::dopromotion(chesspiece *piece, int newpiece, std::string move,
                             movedata *data) {
    int c = piece->getcolor();
    changepiece(piece, chesspiece(newpiece, c, move));
    data->newpieces[data->size - 1] = makepiece(piece);
    setpiece(c, piece, move);
}

void chessboard::setenpassant(int color, movedata *data) {
    std::vector<chesspiece *> *pieces = !color ? &wpieces : &bpieces;
    for (int i = 0; i < pieces->size(); i++) {
        chesspiece *piece = (*pieces)[i];
        if (piece->getpiece() == 0 && piece->getenpassant()) {
            data->oldpieces[data->size++] = makepiece(piece);
            piece->setenpassant(false);
            data->newpieces[data->size - 1] = makepiece(piece);
        }
    }
}

void chessboard::removepiece(int color, std::string pos, movedata *data) {
    std::vector<chesspiece *> *opieces = !color ? &bpieces : &wpieces;
    for (int i = 0; i < opieces->size(); i++) {
        chesspiece *piece = (*opieces)[i];
        if (piece->getpiece() != -1 && piece->getposition() == pos) {
            data->index = i;
            data->captured = makepiece(piece);
            setpiece(color, new chesspiece(), pos);
            changepiece(piece, chesspiece());
        }
    }
}

bool chessboard::isvalid(chesspiece *piece, std::string move) {
    std::vector<std::string> moves = piece->getmoves();
    for (int i = 0; i < moves.size(); i++) {
        if (moves[i] == move) {
            return true;
        }
    }
    return false;
}

bool chessboard::ischeckmate(int color) {
    std::vector<chesspiece *> *pieces = !color ? &wpieces : &bpieces;
    for (int i = 0; i < pieces->size(); i++) {
        chesspiece *piece = (*pieces)[i];
        if (piece->getpiece() != -1 && piece->getmoves().size()) {
            return false;
        }
    }
    return true;
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

void chessboard::debug(chesspiece *piece) {
    std::cout << piece->getunicode() << " " << piece->getposition() << "\n";
}
