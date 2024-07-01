#include "../include/parser.h"

parser::parser() {
    str = "";
}

parser::parser(std::string pgn) {
    std::ifstream file(pgn);
    std::stringstream buffer;
    buffer << file.rdbuf();
    str = buffer.str();
}

int parser::parse() {
    moves.clear();
    int i = 0;
    int len = str.length();
    int l = 0;
    for (; i < str.length(); i++) {
        if (i > 0 && str[i - 1] != '\"') {
            if ((i + 2 < len && str.substr(i, 3) == "1-0") ||
                (i + 2 < len && str.substr(i, 3) == "0-1")) {
                l = 3;
                break;
            } else if ((i + 6 < len && str.substr(i, 7) == "1/2-1/2")) {
                l = 7;
                break;
            }
        }
    }
    std::string s = str.substr(0, i + l);
    str.erase(0, i + l + 1);
    std::istringstream stream(s);
    std::ostringstream result;
    std::string line;
    std::regex info_pattern(R"(\[.*\]\s*)");
    while (std::getline(stream, line)) {
        if (!std::regex_match(line, info_pattern)) {
            result << line << "\n";
        }
    }
    s = result.str();
    std::regex move_pattern(
        R"(([KQRBN][1-8a-hx][\w\+\=#]*)|([a-h][1-8x][\w\+\=#]*)|(O-O-O|O-O)|(1-0|0-1|1\/2-1\/2))");
    std::sregex_iterator iter(s.begin(), s.end(), move_pattern);
    std::sregex_iterator end;
    for (; iter != end; ++iter) {
        moves.push_back(iter->str());
    }
    return l != 0 ? 0 : 1;
}

std::vector<std::string> parser::getmoves() const {
    return moves;
}
