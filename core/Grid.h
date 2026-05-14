#ifndef MICROSOCIETY_GRID_H
#define MICROSOCIETY_GRID_H
#include <vector>
#include <stdexcept>

template <typename T>
class Grid {
private:
    int width;
    int height;
    std::vector<std::vector<T>> cells;

public:
    Grid(int width, int height, const T& defaultValue)
        : width(width),
          height(height),
          cells(height, std::vector<T>(width, defaultValue)) {
        if (width <= 0 || height <= 0) {
            throw std::invalid_argument("Grid dimensions must be positive.");
        }
    }

    bool isInside(int x, int y) const {
        return x >= 0 && x < width && y >= 0 && y < height;
    }

    T& at(int x, int y) {
        if (!isInside(x, y)) {
            throw std::out_of_range("Grid position is outside the map.");
        }

        return cells[y][x];
    }

    const T& at(int x, int y) const {
        if (!isInside(x, y)) {
            throw std::out_of_range("Grid position is outside the map.");
        }

        return cells[y][x];
    }

    int getWidth() const {
        return width;
    }

    int getHeight() const {
        return height;
    }
};

#endif //MICROSOCIETY_GRID_H