#include "../include/movedata.h"

movedata::~movedata() {
    for (int i = 0; i < size; i++) {
        delete oldpieces[i];
        delete newpieces[i];
    }
    delete captured;
}
