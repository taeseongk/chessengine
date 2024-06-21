#ifndef __CHESS_BOARD_H__
#define __CHESS_BOARD_H__

#include "chesspiece.h"
#include <iostream>

class chessboard {
  private:
    std::vector<chesspiece *> wpieces;
    std::vector<chesspiece *> bpieces;
    chesspiece *wboard[8][8];
    chesspiece *bboard[8][8];

  public:
    chessboard();
    ~chessboard();
    void postoint(int color, std::string pos, int &x, int &y);
    std::string inttopos(int x, int y);
    void calcmove(int color);
    void addmoves(chesspiece *piece);
    void print(int color);
};

#endif
