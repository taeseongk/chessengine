#include "../include/chessgame.h"
#include "../include/parser.h"

int main() {
    parser p = parser("./tests/pgnfiles/9.pgn");
    int i = 1;
    while (1) {
        chessgame game = chessgame();
        int check = p.parse();
        if (check) {
            break;
        }
        std::cout << "Game " << i++ << ": ";
        game.starttest(p.getmoves());
    }
}
