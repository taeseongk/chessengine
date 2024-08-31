#ifndef __CHESS_BOARD_H__
#define __CHESS_BOARD_H__

#include "chesspiece.h"
#include <iostream>
#include <regex>
#include <stack>
#include <unordered_map>
#include <utility>

class chessboard {
  private:
    typedef struct {
        int piece;
        int color;
        std::string position;
        bool hasMoved;
        bool isEnPassant;
    } piece;
    typedef struct {
        int color;
        std::string move;
        int size;
        piece *oldpieces[3];
        piece *newpieces[3];
        int index;
        chesspiece captured;
    } movedata;

    std::vector<chesspiece *> wpieces;
    std::vector<chesspiece *> bpieces;
    chesspiece ***wboard;
    chesspiece ***bboard;
    std::stack<movedata *> movepath;

  public:
    chessboard();
    ~chessboard();
    chesspiece *findpiece(int color, int piece, std::string pos);
    void postoint(int color, std::string pos, int &x, int &y);
    std::string inttopos(int color, int x, int y);
    void genmoves(int color);
    void addmoves(chesspiece *piece);
    void showmoves(int color);
    void makemove(chesspiece *piece, std::string move, bool perm);
    void unmakemove();
    void checkmoves(chesspiece *piece);
    void movepiece(chesspiece *piece, std::string move, movedata *data,
                   bool ispromo);
    void setpiece(int color, chesspiece *piece, std::string square);
    void changepiece(chesspiece *piece, chesspiece oldpiece);
    bool ischeck(int color, std::string pos);
    std::vector<chesspiece *> getpieces(int color) const;
    bool cancastle(int color, int kq);
    void docastle(int color, int kq, movedata *data);
    void dopawnmove(chesspiece *piece, std::string move, movedata *data,
                    bool ispromo);
    void dopromotion(chesspiece *piece, int newpiece, std::string move,
                     movedata *data);
    void setenpassant(int color, movedata *data);
    void removepiece(int color, std::string pos, movedata *data);
    bool isvalid(chesspiece *piece, std::string move);
    bool ischeckmate(int color);
    void print(int color);
    void debug(chesspiece *piece);
};

#endif
