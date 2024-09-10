#ifndef __CHESS_ENGINE_H__
#define __CHESS_ENGINE_H__

#include "chessgame.h"
#include "movedata.h"

#define MAX_PLY 1024
#define BF 35

class chessengine {
  private:
    chessgame *game;
    chessboard *board;
    int root;
    movedata *gamelist[MAX_PLY];
    std::stack<movedata *> movepath;

  public:
    chessengine();
    ~chessengine();
    chessgame *getgame() const;
    chessboard *getboard() const;
    void startgame();
    int starttest(std::vector<std::string> moves);
    void makemove(chesspiece *piece, std::string move);
    void unmakemove();
};

#endif
