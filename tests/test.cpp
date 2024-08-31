#include "../include/chessgame.h"
#include "../include/parser.h"

int main() {
    parser p = parser("./tests/pgnfiles/4.pgn");
    int i = 1;
    while (1) {
        int check = p.parse();
        if (check) {
            break;
        }
        chessgame game = chessgame();
        std::cout << "Game " << i++ << ": ";
        game.starttest(p.getmoves());
    }
}
