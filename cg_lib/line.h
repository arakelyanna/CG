#pragma once
#include "point.h"
#include "vector.h"
namespace cg {
    template<typename T>
    struct Line {
        Point<T> p;
        Vector<T> dir;
        
        Line() = default;
        Line(const Point<T>& p, const Vector<T>& dir) : p(p), dir(dir) {}
        
        // Static factory method for creating line from two points
        static Line from_points(const Point<T>& p1, const Point<T>& p2) {
            return Line(p1, Vector<T>(p2.x - p1.x, p2.y - p1.y));
        }
        
        Point<T> point_at(T t) const { return {p.x + dir.x * t, p.y + dir.y * t}; }
        
        T side(const Point<T>& pt) const {
            Vector<T> v(p, pt);
            return dir.cross(v);
        }
        
        bool contains(const Point<T>& pt, T epsilon = 1e-9) const {
            return std::abs(side(pt)) <= epsilon;
        }
        
        bool is_parallel(const Line& other, T epsilon = 1e-9) const {
            return std::abs(dir.cross(other.dir)) <= epsilon;
        }
    };
}