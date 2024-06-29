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
    board->calcmoves(color);
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
    board->makemove(pieces[0], m);
}

int chessgame::starttest(std::vector<std::vector<std::string>> games) {
    for (int i = 0; i < games.size(); i++) {
        int color = 0;
        std::cout << "Game " << i + 1 << std::endl;
        for (int j = 0; j < games[i].size(); j++) {
            std::string move = games[i][j];
            // board->print(color);
            board->calcmoves(color);
            // board->showmoves(color);
            /*
            std::cout << "Move: " << move << std::endl;
            std::cout << std::endl;
            std::cout << std::endl;
            */
            std::vector<chesspiece *> pieces;
            if (move == "1-0") {
                std::cout << "White wins!" << std::endl;
            } else if (move == "0-1") {
                std::cout << "Black wins!" << std::endl;
            } else if (move == "1/2-1/2") {
                std::cout << "Draw!" << std::endl;
            } else {
                std::string m;
                pieces = parse(color, move, m);
                for (int k = pieces.size() - 1; k >= 0; k--) {
                    if (!board->isvalid(pieces[k], m)) {
                        pieces.erase(pieces.begin() + k);
                    }
                }
                assert(pieces.size() == 1);
                board->makemove(pieces[0], m);
            }
            color = !color ? 1 : 0;
        }
        delete board;
        board = new chessboard();
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
                // std::cout << "Adding: " << pieces[i]->getunicode() << ": "
                //<< pieces[i]->getposition() << std::endl;
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
        // std::cout << "HELLo" << std::endl;
        for (int i = 0; i < pieces.size(); i++) {
            if (pieces[i]->getpiece() == 5) {
                res.push_back(pieces[i]);
            }
        }
        parsed_move = move;
    }
    return res;
}
