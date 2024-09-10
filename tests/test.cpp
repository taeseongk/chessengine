#include "../include/chessengine.h"
#include "../include/parser.h"

int main() {
    // Test to check chess move generation
    /*
    parser p = parser("./tests/pgnfiles/1.pgn");
    int i = 1;
    while (1) {
        int check = p.parse();
        if (check) {
            break;
        }
        chessengine engine = chessengine();
        std::cout << "Game " << i++ << ": ";
        engine.starttest(p.getmoves());
    }
    */

    // Test to check make/unmakemove() functions
    /*
    chessengine engine = chessengine();
    chessgame *game = engine.getgame();
    chessboard *board = engine.getboard();
    parser p = parser("./tests/pgnfiles/6.pgn");
    p.parse();
    int y;
    int color = 0;
    std::vector<std::string> moves = p.getmoves();
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
            engine.makemove(pieces[0], m);
            color = !color ? 1 : 0;
        }
    }
    for (int i = 0; i < moves.size() - 1; i++) {
        engine.unmakemove();
    }
    */
}
