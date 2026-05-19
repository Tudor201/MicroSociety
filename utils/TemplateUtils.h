#ifndef MICROSOCIETY_TEMPLATEUTILS_H
#define MICROSOCIETY_TEMPLATEUTILS_H
#include <stdexcept>
#include <vector>

template <typename T>
T findMax(const std::vector<T>& values) {
    if (values.empty()) {
        throw std::invalid_argument("Cannot find maximum of empty vector.");
    }

    T maximum = values[0];

    for (const T& value : values) {
        if (value > maximum) {
            maximum = value;
        }
    }

    return maximum;
}

template <typename T, typename Predicate>
int countMatching(const std::vector<T>& values, Predicate predicate) {
    int count = 0;

    for (const T& value : values) {
        if (predicate(value)) {
            count++;
        }
    }

    return count;
}
#endif //MICROSOCIETY_TEMPLATEUTILS_H