#include "../include/parser.h"
#include "../include/chessgame.h"

int main(int argc, char *argv[]) {
    parser p = parser();
    p.parse("./tests/pgnfiles/2.pgn");
    std::vector<std::vector<std::string>> games = p.getgames();
    std::cout << "Size: " << games.size() << std::endl;
    chessgame game = chessgame();
    game.starttest(games);
}
