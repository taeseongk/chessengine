#ifndef __PARSER_H__
#define __PARSER_H__

#include "./chessboard.h"
#include <fstream>
#include <regex>
#include <sstream>

class parser {
  private:
    std::string str;
    std::vector<std::string> moves;

  public:
    parser();
    parser(std::string pgn);
    int parse();
    std::vector<std::string> getmoves() const;
};
#endif
