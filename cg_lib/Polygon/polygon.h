#pragma once
#include "../point.h"
#include "../vector.h"
#include <vector>
#include <algorithm>
#include <cmath>

namespace cg {
    template<typename T, size_t n>
    struct BoundingBox {
        Point<T, n> min;
        Point<T, n> max;
        
        BoundingBox() = default;
        BoundingBox(const Point<T, n>& min, const Point<T, n>& max) : min(min), max(max) {}
        
        bool contains(const Point<T, n>& pt) const {
            for (size_t i = 0; i < n; ++i) {
                if (pt[i] < min[i] || pt[i] > max[i]) return false;
            }
            return true;
        }
        
        void expand(const Point<T, n>& pt) {
            for (size_t i = 0; i < n; ++i) {
                min[i] = std::min(min[i], pt[i]);
                max[i] = std::max(max[i], pt[i]);
            }
        }
    };
    
    template<typename T, size_t n>
    class Polygon {
        static_assert(std::is_arithmetic_v<T>, "Polygon template parameter must be an arithmetic type");
        
        std::vector<Point<T, n>> vertices;
        
        BoundingBox<T, n> bbox;
        
        void update_bbox() {
            if (vertices.empty()) return;
            
            bbox.min = vertices[0];
            bbox.max = vertices[0];
            
            for (const auto& v : vertices) {
                for (size_t i = 0; i < n; ++i) {
                    bbox.min[i] = std::min(bbox.min[i], v[i]);
                    bbox.max[i] = std::max(bbox.max[i], v[i]);
                }
            }
        }
        
    public:
        Polygon() = default;
        Polygon(const std::vector<Point<T, n>>& verts);
        Polygon(const std::initializer_list<Point<T, n>>& verts);
        
        Polygon(const Polygon& other) = default;
        Polygon(Polygon&& other) noexcept = default;
        Polygon& operator=(const Polygon& other) = default;
        Polygon& operator=(Polygon&& other) noexcept = default;
        ~Polygon() = default;
        
        size_t size() const;
        const BoundingBox<T, n>& get_bbox() const { return bbox; }
        
        void add_vertex(const Point<T, n>& pt);
        void remove_vertex(size_t index);
        void insert_vertex(size_t index, const Point<T, n>& pt);
        
        bool is_convex() const;
        void translate(const Vector<T, n>& v);
        bool contains(const Point<T, n>& pt) const;
        std::vector<Polygon<T, n>> triangulate_convex_hull() const;
        std::vector<Polygon<T, n>> triangulate() const;
        double area() const;
        
        bool operator==(const Polygon& other) const;
        bool operator!=(const Polygon& other) const;
    };
}

#include "polygon.tpp"