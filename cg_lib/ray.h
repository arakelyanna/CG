// ray.h
#pragma once
#include "point.h"
#include "vector.h"

namespace cg {
    template<typename T>
    struct Ray {
        Point<T> origin;
        Vector<T> dir;
        
        Ray() = default;
        Ray(const Point<T>& origin, const Vector<T>& dir) : origin(origin), dir(dir) {}
        
        Point<T> point_at(T t) const {
            return {origin.x + dir.x * t, origin.y + dir.y * t};
        }
    };
}