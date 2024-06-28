#include "../include/parser.h"
#include "../include/chessgame.h"

int main() {
    parser p = parser();
    p.parse("./tests/pgnfiles/1.pgn");
    std::vector<std::vector<std::string>> games = p.getgames();
    chessgame game = chessgame();
    game.starttest(games);
}
