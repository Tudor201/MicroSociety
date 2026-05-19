#ifndef MICROSOCIETY_GRID_H
#define MICROSOCIETY_GRID_H
#include "Exceptions.h"
#include <stdexcept>
#include <type_traits>
#include <vector>

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
        static_assert(
            std::is_default_constructible_v<T>,
            "Grid requires default constructible types."
        );

        if (width <= 0 || height <= 0) {
            throw std::invalid_argument("Grid dimensions must be positive.");
        }
    }

    bool isInside(int x, int y) const {
        return x >= 0 && x < width && y >= 0 && y < height;
    }

    T& at(int x, int y) {
        if (!isInside(x, y)) {
            throw WorldException("Grid position is outside the map.");
        }

        return cells[y][x];
    }

    const T& at(int x, int y) const {
        if (!isInside(x, y)) {
            throw WorldException("Grid position is outside the map.");
        }

        return cells[y][x];
    }

    void fill(const T& value) {
        for (auto& row : cells) {
            for (auto& cell : row) {
                cell = value;
            }
        }
    }

    std::vector<T> flatten() const {
        std::vector<T> result;

        for (const auto& row : cells) {
            for (const auto& cell : row) {
                result.push_back(cell);
            }
        }

        return result;
    }

    int getWidth() const {
        return width;
    }

    int getHeight() const {
        return height;
    }
};

#endif //MICROSOCIETY_GRID_H