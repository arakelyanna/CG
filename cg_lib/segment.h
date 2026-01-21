#pragma once
#include "point.h"
#include "vector.h"
#include <cmath>

namespace cg {
    template<typename T>
    struct Segment {
        Point<T> a, b;
        
        Segment() = default;
        Segment(const Point<T>& a, const Point<T>& b) : a(a), b(b) {}
        
        Vector<T> to_vector() const { return {a, b}; }
        
        Point<T> midpoint() const {
            return {(a.x + b.x) / static_cast<T>(2), (a.y + b.y) / static_cast<T>(2)};
        }
        
        T length_sq() const {
            T dx = b.x - a.x;
            T dy = b.y - a.y;
            return dx * dx + dy * dy;
        }
        
        double length() const { return std::sqrt(static_cast<double>(length_sq())); }
    };
}