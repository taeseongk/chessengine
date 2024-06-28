#ifndef __CHESSGAME_H__
#define __CHESSGAME_H__

#include "chessboard.h"
#include "parser.h"
#include <cassert>

class chessgame {
  private:
    chessboard *board;

  public:
    chessgame();
    ~chessgame();
    void startgame();
    void doturn(int color);
    int starttest(std::vector<std::vector<std::string>> games);
    std::vector<chesspiece *> parse(int color, std::string move,
                                    std::string &parsed_move);
};
#endif
