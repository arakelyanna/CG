#pragma once
#include "point.h"
#include "vector.h"
#include <type_traits>
#include <cmath>

namespace cg {
    template<typename T, size_t n>
    struct Ray {
        static_assert(std::is_arithmetic_v<T>, "Ray template parameter must be an arithmetic type");
        
        Point<T, n> origin;
        Vector<T, n> dir;
        
        Ray() = default;
        Ray(const Point<T, n>& origin, const Vector<T, n>& dir) : origin(origin), dir(dir) {}
        
        static Ray from_points(const Point<T, n>& p1, const Point<T, n>& p2) {
            return Ray(p1, p2 - p1);
        }
        
        Point<T, n> point_at(T t) const {
            assert(t >= 0);
            return origin + (dir * t);
        }
        
        Vector<T, n> direction() const {
            return dir;
        }
        
        bool contains(const Point<T, n>& pt) const {
            Vector<T, n> v = pt - origin;
            Vector<T, n> normalized_dir = dir.normalize();
            Vector<T, n> projected = normalized_dir * (v.dot_product(normalized_dir));
            
            if ((v - projected).length() > Coord<T>::tolerance) return false;
            
            T t = v.dot_product(normalized_dir);
            return t >= -Coord<T>::tolerance;
        }
        
        bool operator==(const Ray& other) const {
            return origin == other.origin && dir.normalize().dot_product(other.dir.normalize()) > 0;
        }
    };
}