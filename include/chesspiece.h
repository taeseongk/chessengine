#ifndef __CHESS_PIECE_H__
#define __CHESS_PIECE_H__

#include <string>
#include <vector>

class chesspiece {
  private:
    int piece;
    int color;
    std::string unicode;
    std::string position;
    bool hasMoved;
    bool isEnPassant;
    std::vector<std::string> moves;

  public:
    chesspiece();
    chesspiece(int p, int c, std::string pos);
    int getColor() const;
    int getPiece() const;
    std::string getPosition() const;
    void setPos(std::string pos);
    std::string getUnicode() const;
    bool getHasMoved() const;
    void setEnPassant();
};
#endif
