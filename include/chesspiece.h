#ifndef __CHESS_PIECE_H__
#define __CHESS_PIECE_H__

#include <string>

class chesspiece {
  private:
    int piece;
    int color;
    std::string unicode;
    int posX;
    int posY;

  public:
    chesspiece();
    chesspiece(int piece, int color);
    int getPosX() const;
    int getPosY() const;
    void setPos(int x, int y);
    std::string getUnicode() const;
};
#endif
