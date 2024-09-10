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
    chessboard *getboard() const;
    void startgame();
    int doturn(int color, ::movedata *data);
    int starttest(std::vector<std::string> moves);
    std::vector<chesspiece *> parse(int color, std::string move,
                                    std::string &parsed_move);
};
#endif
