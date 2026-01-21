// coord.h
#pragma once
#include <cmath>

namespace cg {
    template<typename T>
    struct Coord {
        T x, y;
        
        Coord() : x(0), y(0) {}
        Coord(T x, T y) : x(x), y(y) {}
        
        Coord operator+(const Coord& o) const { return {x + o.x, y + o.y}; }
        Coord operator-(const Coord& o) const { return {x - o.x, y - o.y}; }
        Coord operator*(T s) const { return {x * s, y * s}; }
        Coord operator/(T s) const { return {x / s, y / s}; }
        
        bool operator==(const Coord& o) const { return x == o.x && y == o.y; }
        bool operator!=(const Coord& o) const { return !(*this == o); }
        
        T dot(const Coord& o) const { return x * o.x + y * o.y; }
        T cross(const Coord& o) const { return x * o.y - y * o.x; }
        T length_sq() const { return x * x + y * y; }
        double length() const { return std::sqrt(static_cast<double>(length_sq())); }
    };

    template<typename T>
    using Point = Coord<T>;
}