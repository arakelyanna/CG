#pragma once
#include "point.h"
#include "vector.h"

namespace cg {
    template<typename T, size_t n>
    struct Segment {
        static_assert(std::is_arithmetic_v<T>, "Coord type is not arithmetic type.");
        
        Point<T, n> a, b;
        
        Segment() = default;
        Segment(const Point<T, n>& a, const Point<T, n>& b) : a(a), b(b) {}
        
        Vector<T, n> to_vector() const { 
            return (b - a); 
        }
        
        Point<T, n> midpoint() const {
            Point<T, n> result;
            for (size_t i = 0; i < n; ++i) {
                result[i] = (a[i] + b[i]) / static_cast<T>(2);
            }
            return result;
        }

        double length() const { 
            return to_vector().length(); 
        }
        
        bool operator==(const Segment& other) const {
            return a == other.a && b == other.b;
        }
        
        bool operator!=(const Segment& other) const {
            return !(*this == other);
        }
    };
}