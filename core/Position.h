#ifndef MICROSOCIETY_POSITION_H
#define MICROSOCIETY_POSITION_H

class Position {
private:
    int x;
    int y;

public:
    Position(int x = 0, int y = 0)
        : x(x), y(y) {}

    int getX() const {
        return x;
    }

    int getY() const {
        return y;
    }

    void setX(int newX) {
        x = newX;
    }

    void setY(int newY) {
        y = newY;
    }

    void moveBy(int dx, int dy) {
        x += dx;
        y += dy;
    }
};

#endif //MICROSOCIETY_POSITION_H