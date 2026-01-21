#pragma once
#include "point.h"
#include "vector.h"
#include <type_traits>
#include <cmath>

namespace cg {
    template<typename T, size_t n>
    struct Line {
        static_assert(std::is_arithmetic_v<T>, "Line template parameter must be an arithmetic type");
        
        Point<T, n> p;
        Vector<T, n> dir;

        Line() = default;
        Line(const Point<T, n>& p, const Vector<T, n>& dir) : p(p), dir(dir) {}
        
        static Line from_points(const Point<T, n>& p1, const Point<T, n>& p2) {
            return Line(p1, p2 - p1);
        }
        
        Point<T, n> point_at(T t) const { 
            return p + (dir * t);
        }
        
        Vector<T, n> direction() const {
            return dir;
        }
        
        bool contains(const Point<T, n>& pt) const {
            Vector<T, n> v = pt - p;
            Vector<T, n> normalized_dir = dir.normalize();
            Vector<T, n> projected = normalized_dir * (v.dot_product(normalized_dir));
            return (v - projected).length() <= Coord<T>::tolerance;
        }
        
        bool is_parallel(const Line& other) const {
            T dot_prod = dir.dot_product(other.dir);
            T len_product = dir.length() * other.dir.length();
            return std::abs(std::abs(dot_prod) - len_product) <= Coord<T>::tolerance;
        }
        
        bool operator==(const Line& other) const {
            return p == other.p && dir.normalize().dot_product(other.dir.normalize()) > 0;
        }
    };
}