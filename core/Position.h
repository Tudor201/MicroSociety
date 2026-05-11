#ifndef MICROSOCIETY_POSITION_H
#define MICROSOCIETY_POSITION_H

struct Position {
    int x;
    int y;

    Position(int x = 0, int y = 0)
        : x(x), y(y) {}
};

#endif //MICROSOCIETY_POSITION_H