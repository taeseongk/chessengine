#include "../include/parser.h"

parser::parser() {}

void parser::parse(std::string pgn) {
    std::ifstream file(pgn);
    std::stringstream buffer;
    buffer << file.rdbuf();
    std::string str = buffer.str();
    // std::cout << str << std::endl;
    std::vector<std::string> games;
    std::regex game_pattern(
        R"(((\d+\.\s+)([\w\+\=\-]+\s+)((\{[^\}]+\})\s+)?(([\w\+\=\-]+\s+)((\{[^\}]+\})\s+)?)?)+(1-0|0-1|1\/2-1\/2))");
    std::sregex_iterator iter1(str.begin(), str.end(), game_pattern);
    std::sregex_iterator end;

    for (; iter1 != end; ++iter1) {
        std::cout << iter1->str() << std::endl;
        games.push_back(iter1->str());
    }

    std::regex move_pattern(
        R"(([KQRBN][1-8a-hx][\w\+\=#]*)|([a-h][1-8x][\w\+\=#]*)|(O-O-O|O-O)|(1-0|0-1|1\/2-1\/2))");
    for (int i = 0; i < games.size(); i++) {
        std::sregex_iterator iter2(games[i].begin(), games[i].end(),
                                   move_pattern);
        std::sregex_iterator end;
        std::vector<std::string> game;
        for (; iter2 != end; ++iter2) {
            game.push_back(iter2->str());
        }
        chessgames.push_back(game);
    }
}

std::vector<std::vector<std::string>> parser::getgames() const {
    return chessgames;
}
