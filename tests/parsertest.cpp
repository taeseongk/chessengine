#include "../include/parser.h"

int main(int argc, char *argv[]) {
    parser p = parser("./tests/pgnfiles/4.pgn");
    /*
    int i = 1;
    while (1) {
        int check = p.parse();

        if (check) {
            break;
        }
        i++;
    }
    */
    p.parse();
    p.parse();
}
