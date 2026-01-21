#pragma once
#include "../point.h"
#include "../vector.h"
#include <vector>
#include <algorithm>
#include <cmath>

namespace cg {
    template<typename T>
    struct Polygon {
        std::vector<Point<T>> vertices;
        
        Polygon() = default;
        Polygon(const std::vector<Point<T>>& verts);
        
        size_t size() const;
        bool is_convex() const;
        void translate(const Vector<T>& v);
        void scale(T factor, const Point<T>& center = {0, 0});
        void rotate(double angle, const Point<T>& center = {0, 0});
        bool contains(const Point<T>& pt) const;
        std::vector<std::vector<Point<T>>> triangulate() const;
        double area() const;
    };

}

#include "polygon.tpp"