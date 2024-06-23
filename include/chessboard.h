#ifndef __CHESS_BOARD_H__
#define __CHESS_BOARD_H__

#include "chesspiece.h"
#include <iostream>
#include <utility>

class chessboard {
  private:
    std::vector<chesspiece *> wpieces;
    std::vector<chesspiece *> bpieces;
    chesspiece ***wboard;
    chesspiece ***bboard;

  public:
    chessboard();
    ~chessboard();
    void postoint(int color, std::string pos, int &x, int &y);
    std::string inttopos(int color, int x, int y);
    void calcmoves(int color);
    void addmoves(chesspiece *piece);
    void showmoves(int color);
    void makemove(chesspiece *piece, std::string move);
    void checkmoves(chesspiece *piece);
    bool ischeck(int color);
    std::vector<chesspiece *> getpieces(int color) const;
    void print(int color);
};

#endif
