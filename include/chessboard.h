#ifndef __CHESS_BOARD_H__
#define __CHESS_BOARD_H__

#include "chesspiece.h"
#include <iostream>
#include <vector>

class chessboard {
  private:
    std::vector<chesspiece *> wpieces;
    std::vector<chesspiece *> bpieces;
    chesspiece *board[8][8];

  public:
    chessboard();
    ~chessboard();
    void print(int color);
};

#endif
