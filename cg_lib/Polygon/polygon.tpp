#pragma once
#include "polygon.h"
#include "../functions.h"

namespace cg {
    template<typename T, size_t n>
    Polygon<T, n>::Polygon(const std::vector<Point<T, n>>& verts) : vertices(verts) {
        static_assert(n == 2, "Polygon only supports 2D points");
        update_bbox();
    }

    template<typename T, size_t n>
    Polygon<T, n>::Polygon(const std::initializer_list<Point<T, n>>& verts) 
        : vertices(verts) {
        static_assert(n == 2, "Polygon only supports 2D points");
        update_bbox();
    }

    template<typename T, size_t n>
    size_t Polygon<T, n>::size() const {
        return vertices.size();
    }

    template<typename T, size_t n>
    void Polygon<T, n>::add_vertex(const Point<T, n>& pt) {
        static_assert(n == 2, "add_vertex() only supports 2D polygons");
        
        vertices.push_back(pt);
        bbox.expand(pt);
    }

    template<typename T, size_t n>
    void Polygon<T, n>::remove_vertex(size_t index) {
        static_assert(n == 2, "remove_vertex() only supports 2D polygons");
        
        assert(index < vertices.size());
        assert(vertices.size() > 3);  
        
        vertices.erase(vertices.begin() + index);
        update_bbox();
    }

    template<typename T, size_t n>
    void Polygon<T, n>::insert_vertex(size_t index, const Point<T, n>& pt) {
        static_assert(n == 2, "insert_vertex() only supports 2D polygons");
        
        assert(index <= vertices.size());
        
        vertices.insert(vertices.begin() + index, pt);
        update_bbox();
    }

    template<typename T, size_t n>
    bool Polygon<T, n>::is_convex() const {
        static_assert(n == 2, "is_convex() only supports 2D polygons");
        
        if (vertices.size() < 3) return false;
        
        bool has_positive = false, has_negative = false;
        size_t num_verts = vertices.size();
        
        for (size_t i = 0; i < num_verts; ++i) {
            const auto& p1 = vertices[i];
            const auto& p2 = vertices[(i + 1) % num_verts];
            const auto& p3 = vertices[(i + 2) % num_verts];
            
            Vector<T, n> v1 = p2 - p1;
            Vector<T, n> v2 = p3 - p2;
            T cross = v1.orientation(v2);
            
            if (cross > 0) has_positive = true;
            else if (cross < 0) has_negative = true;
            if (has_positive && has_negative) return false;
        }
        return true;
    }

    template<typename T, size_t n>
    void Polygon<T, n>::translate(const Vector<T, n>& v) {
        static_assert(n == 2, "translate() only supports 2D polygons");
        
        for (auto& p : vertices) {
            p = p + v;
        }
        update_bbox();
    }

    template<typename T, size_t n>
    bool Polygon<T, n>::contains(const Point<T, n>& pt) const {
        static_assert(n == 2, "contains() only supports 2D polygons");
        
        if (vertices.size() < 3) return false;
        
        int intersection_count = 0;
        size_t num_verts = vertices.size();
        
        Ray<T, n> ray(pt, Vector<T, n>{static_cast<T>(1), static_cast<T>(0)});
        
        for (size_t i = 0; i < num_verts; ++i) {
            Segment<T, n> edge(vertices[i], vertices[(i + 1) % num_verts]);
            
            if (intersect(ray, edge)) {
                ++intersection_count;
            }
        }
        
        return intersection_count % 2 == 1;
    }

    template<typename T, size_t n>
    std::vector<Polygon<T, n>> Polygon<T, n>::triangulate_convex_hull() const {
        static_assert(n == 2, "triangulate() only supports 2D polygons");
        
        std::vector<Polygon<T, n>> triangles;
        if (vertices.size() == 3) {
            triangles.push_back(*this);
            return triangles;
        }
        assert(is_convex());

        size_t count = vertices.size();
        
        for (size_t i = 1; i + 1 < count; ++i) {
            triangles.push_back(Polygon<T, n>({vertices[0], 
                                               vertices[i],
                                               vertices[i + 1]}));
        }
        
        return triangles;
    }
    
    template<typename T, size_t n>
    std::vector<Polygon<T, n>> Polygon<T, n>::triangulate() const {
        std::vector<Polygon<T, n>> triangles;
        if (vertices.size() < 3) return triangles;
        if (vertices.size() == 3) {
            triangles.push_back(*this);
            return triangles;
        }
        if (is_convex()) return triangulate_convex_hull();
        
        std::vector<Point<T, n>> remaining = vertices;
        
        while (remaining.size() > 3) {
            size_t r_size = remaining.size();
            bool found_ear = false;
            
            for (size_t i = 0; i < r_size; ++i) {
                size_t prev = (i + r_size - 1) % r_size;
                size_t next = (i + 1) % r_size;
                
                Vector<T, n> v1 = remaining[i] - remaining[prev];
                Vector<T, n> v2 = remaining[next] - remaining[i];
                
                if (v1.orientation(v2) > 0) {
                    triangles.push_back(Polygon<T, n>({remaining[prev], 
                                                       remaining[i], 
                                                       remaining[next]}));
                    remaining.erase(remaining.begin() + i);
                    found_ear = true;
                    break;
                }
            }
            
            if (!found_ear) break;
        }
        
        if (remaining.size() == 3) {
            triangles.push_back(Polygon<T, n>(remaining));
        }
        
        return triangles;
    }

    template<typename T, size_t n>
    double Polygon<T, n>::area() const {
        static_assert(n == 2, "area() only supports 2D polygons");
        
        if (vertices.size() < 3) return 0;
        
        double sum = 0;
        size_t num_verts = vertices.size();
        
        for (size_t i = 0; i < num_verts; ++i) {
            size_t j = (i + 1) % num_verts;
            sum += static_cast<double>(vertices[i][0] * vertices[j][1]);
            sum -= static_cast<double>(vertices[j][0] * vertices[i][1]);
        }
        
        return std::abs(sum) / 2.0;
    }

    template<typename T, size_t n>
    bool Polygon<T, n>::operator==(const Polygon& other) const {
        static_assert(n == 2, "operator==() only supports 2D polygons");
        
        if (vertices.size() != other.vertices.size()) return false;
        
        for (size_t i = 0; i < vertices.size(); ++i) {
            if (vertices[i] != other.vertices[i]) return false;
        }
        return true;
    }

    template<typename T, size_t n>
    bool Polygon<T, n>::operator!=(const Polygon& other) const {
        return !(*this == other);
    }
}