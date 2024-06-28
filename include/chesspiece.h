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
    int getcolor() const;
    int getpiece() const;
    void setpiece(int p);
    std::string getposition() const;
    void setposition(std::string pos);
    std::string getunicode() const;
    void setunicode(int p, int c);
    bool gethasmoved() const;
    void sethasmoved();
    void setenpassant(bool value);
    bool getenpassant() const;
    void addmove(std::string move);
    void delmove(std::string move);
    std::vector<std::string> getmoves() const;
    void clearmoves();
};
#endif
