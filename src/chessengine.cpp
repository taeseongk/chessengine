#include "../include/chessengine.h"

chessengine::chessengine() {
    game = new chessgame();
    board = game->getboard();
    root = 0;
}

chessengine::~chessengine() {
    for (int i = 0; i < root; i++) {
        delete gamelist[i];
    }
    while (movepath.size()) {
        ::movedata *data = movepath.top();
        movepath.pop();
        delete data;
    }
    delete game;
}

chessgame *chessengine::getgame() const {
    return game;
}

chessboard *chessengine::getboard() const {
    return board;
}

void chessengine::startgame() {
    while (1) {
        ::movedata *wdata = new ::movedata;
        if (game->doturn(0, wdata)) {
            delete wdata;
            std::cout << "Black wins!\n";
            return;
        }
        gamelist[root++] = wdata;
        ::movedata *bdata = new ::movedata;
        if (game->doturn(1, bdata)) {
            delete bdata;
            std::cout << "White wins!\n";
            return;
        }
        gamelist[root++] = bdata;
    }
}

int chessengine::starttest(std::vector<std::string> moves) {
    int color = 0;
    for (int i = 0; i < moves.size(); i++) {
        std::string move = moves[i];
        board->genmoves(color);
        if (move == "1-0" || move == "0-1" || move == "1/2-1/2") {
            break;
        } else {
            std::vector<chesspiece *> pieces;
            std::string m;
            pieces = game->parse(color, move, m);
            for (int k = pieces.size() - 1; k >= 0; k--) {
                if (!board->isvalid(pieces[k], m)) {
                    pieces.erase(pieces.begin() + k);
                }
            }
            assert(pieces.size() == 1);
            ::movedata *data = new ::movedata;
            board->makemove(pieces[0], m, data);
            gamelist[root++] = data;
            color = !color ? 1 : 0;
        }
    }
    std::cout << "Successful!" << std::endl;
    return 0;
}

void chessengine::makemove(chesspiece *piece, std::string move) {
    ::movedata *data = new ::movedata;
    board->makemove(piece, move, data);
    movepath.push(data);
}

void chessengine::unmakemove() {
    if (!movepath.size()) {
        return;
    }
    ::movedata *data = movepath.top();
    movepath.pop();
    int c = data->color;
    int size = data->size;
    for (int i = 0; i < size; i++) {
        piece *oldpiece = data->oldpieces[i];
        piece *newpiece = data->newpieces[i];
        board->setpiece(c, new chesspiece(), newpiece->position);
        chesspiece *p =
            board->findpiece(c, newpiece->piece, newpiece->position);
        board->changepiece(p, oldpiece);
        board->setpiece(c, p, p->getposition());
    }
    int index = data->index;
    if (index != -1) {
        chesspiece *p = board->getpieces(!c)[index];
        board->changepiece(p, data->captured);
        board->setpiece(!c, p, p->getposition());
    }
    delete data;
}
