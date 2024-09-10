#ifndef __MOVEDATA_H__
#define __MOVEDATA_H__

#include "chesspiece.h"
#include <iostream>

typedef struct {
    int piece;
    int color;
    std::string position;
    bool hasMoved;
    bool isEnPassant;
} piece;

class movedata {
  public:
    int color;
    std::string move;
    int size;
    piece *oldpieces[3];
    piece *newpieces[3];
    int index;
    piece *captured;
    ~movedata();
};

#endif
