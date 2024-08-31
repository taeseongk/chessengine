#include "../include/chessgame.h"

chessgame::chessgame() {
    board = new chessboard();
}

chessgame::~chessgame() {
    delete board;
}

void chessgame::startgame() {
    while (1) {
        doturn(0);
        doturn(1);
    }
}

void chessgame::doturn(int color) {
    system("clear");
    board->print(color);
    board->genmoves(color);
    board->showmoves(color);

    std::string move;
    std::string m;
    chesspiece *p;
    std::vector<chesspiece *> pieces;
    do {
        std::cin >> move;
        pieces = parse(color, move, m);
        for (int i = pieces.size() - 1; i >= 0; i--) {
            p = pieces[i];
            if (!board->isvalid(p, m)) {
                pieces.erase(pieces.begin() + i);
            }
        }
    } while (pieces.size() != 1);
    board->makemove(pieces[0], m, true);
}

int chessgame::starttest(std::vector<std::string> moves) {
    int color = 0;
    for (int i = 0; i < moves.size(); i++) {
        std::string move = moves[i];
        // board->print(color);
        board->genmoves(color);
        // board->showmoves(color);
        // std::cout << "Move: " << move << "\n";
        // std::cout << "\n";
        /*
        int yo;
        std::cin >> yo;
        */
        if (move == "1-0" || move == "0-1" || move == "1/2-1/2") {
            break;
        } else {
            std::vector<chesspiece *> pieces;
            std::string m;
            pieces = parse(color, move, m);
            for (int k = pieces.size() - 1; k >= 0; k--) {
                if (!board->isvalid(pieces[k], m)) {
                    pieces.erase(pieces.begin() + k);
                }
            }
            assert(pieces.size() == 1);
            board->makemove(pieces[0], m, true);
            color = !color ? 1 : 0;
        }
    }
    std::cout << "Successful!" << std::endl;
    return 0;
}

std::vector<chesspiece *> chessgame::parse(int color, std::string move,
                                           std::string &parsed_move) {
    std::vector<chesspiece *> pieces = board->getpieces(color);
    std::vector<chesspiece *> res;
    std::unordered_map<char, int> m = {
        {'K', 5}, {'Q', 4}, {'R', 1}, {'B', 3}, {'N', 2}};
    move.erase(std::remove(move.begin(), move.end(), 'x'), move.end());
    move.erase(std::remove(move.begin(), move.end(), '+'), move.end());
    move.erase(std::remove(move.begin(), move.end(), '#'), move.end());
    int len = move.length();
    char p = move[0];
    if (p == 'K' || p == 'Q' || p == 'R' || p == 'B' || p == 'N') {
        for (int i = 0; i < pieces.size(); i++) {
            if (len == 3 && pieces[i]->getpiece() == m[p]) {
                res.push_back(pieces[i]);
            } else if (len == 4 && isdigit(move[1]) &&
                       pieces[i]->getpiece() == m[p] &&
                       pieces[i]->getposition()[1] == move[1]) {
                res.push_back(pieces[i]);
            } else if (len == 4 && isalpha(move[1]) &&
                       pieces[i]->getpiece() == m[p] &&
                       pieces[i]->getposition()[0] == move[1]) {
                res.push_back(pieces[i]);
            } else if (len == 5 && pieces[i]->getpiece() == m[p] &&
                       pieces[i]->getposition() == move.substr(1, 2)) {
                res.push_back(pieces[i]);
            }
        }
        parsed_move = move.substr(len - 2, 2);
    } else if (p == 'a' || p == 'b' || p == 'c' || p == 'd' || p == 'e' ||
               p == 'f' || p == 'g' || p == 'h') {
        for (int i = 0; i < pieces.size(); i++) {
            if (pieces[i]->getpiece() == 0 &&
                pieces[i]->getposition()[0] == p) {
                res.push_back(pieces[i]);
            }
        }
        parsed_move = len % 2 ? move.substr(1, len - 1) : move;
    } else if (move == "O-O" || move == "O-O-O") {
        for (int i = 0; i < pieces.size(); i++) {
            if (pieces[i]->getpiece() == 5) {
                res.push_back(pieces[i]);
            }
        }
        parsed_move = move;
    }
    return res;
}
