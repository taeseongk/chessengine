#ifndef __PARSER_H__
#define __PARSER_H__

#include "./chessboard.h"
#include <fstream>
#include <regex>
#include <sstream>

class parser {
  private:
    std::vector<std::vector<std::string>> chessgames;

  public:
    parser();
    void parse(std::string pgn);
    std::vector<std::vector<std::string>> getgames() const;
};
#endif
