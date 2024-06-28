#ifndef __CHESS_BOARD_H__
#define __CHESS_BOARD_H__

#include "chesspiece.h"
#include <iostream>
#include <regex>
#include <unordered_map>
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
    void setpiece(chesspiece *piece, std::string move);
    bool ischeck(int color, std::string pos);
    std::vector<chesspiece *> getpieces(int color) const;
    bool cancastle(int color, int kq);
    void docastle(int color, int kq);
    void dopawnmove(chesspiece *piece, std::string move);
    void setenpassant(int color);
    void dopromotion(chesspiece *piece, int newpiece, std::string move);
    void removepiece(int color, std::string pos);
    bool isvalid(chesspiece *piece, std::string move);
    bool ischeckmate(int color);
    void print(int color);
};

#endif
