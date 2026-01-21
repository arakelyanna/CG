#pragma once
#include "vector.h"
#include "line.h"
#include "segment.h"
#include "ray.h"
#include <optional>
#include <cmath>

namespace cg {

    // Line-Line (2D)
    template<typename T>
    std::optional<cg::Point<T, 2>> intersect(const cg::Line<T, 2>& l1, const cg::Line<T, 2>& l2) {
        // Use orientation (2D cross product) instead of cross_product
        T det = l1.dir.orientation(l2.dir);
        
        if (det == 0) return std::nullopt; 
        
        Vector<T, 2> w = l2.p - l1.p;
        T t = w.orientation(l2.dir) / det;
        
        return l1.point_at(t);
    }

    // Segment-Segment (2D)
    template<typename T>
    bool intersection(const Segment<T, 2>& s1, const Segment<T, 2>& s2) {
        Vector<T, 2> v1 = s1.to_vector();
        Vector<T, 2> v2 = s2.to_vector();
        
        Vector<T, 2> s1a_to_s2a = s2.a - s1.a;
        Vector<T, 2> s1a_to_s2b = s2.b - s1.a;
        
        T cross1 = v1.orientation(s1a_to_s2a);
        T cross2 = v1.orientation(s1a_to_s2b);
        
        Vector<T, 2> s2a_to_s1a = s1.a - s2.a;
        Vector<T, 2> s2a_to_s1b = s1.b - s2.a;
        
        T cross3 = v2.orientation(s2a_to_s1a);
        T cross4 = v2.orientation(s2a_to_s1b);
        
        return (cross1 * cross2 <= 0) && (cross3 * cross4 <= 0);
    }
    
    // Line-Ray (2D)
    template<typename T>
    std::optional<cg::Point<T, 2>> intersect(const cg::Line<T, 2>& line, const cg::Ray<T, 2>& ray) {
        // Use orientation (2D cross product) instead of cross_product
        T det = line.dir.orientation(ray.dir);
        if (det == 0) return std::nullopt;
        
        Vector<T, 2> w = ray.origin - line.p;
        T t_ray = w.orientation(line.dir) / det;
        
        if (t_ray < 0) return std::nullopt;
        
        return ray.point_at(t_ray);
    }

    // Ray-Line (2D)
    template<typename T>
    std::optional<cg::Point<T, 2>> intersect(const cg::Ray<T, 2>& ray, const cg::Line<T, 2>& line) {
        return intersect(line, ray);
    }

    // Ray-Segment (2D)
    template<typename T>
    bool intersect(const cg::Ray<T, 2>& ray, const cg::Segment<T, 2>& seg) {
        Line<T, 2> line = Line<T, 2>::from_points(seg.a, seg.b);
        auto intersection = intersect(ray, line);
        
        if (intersection.has_value()) {
            Vector<T, 2> to_pt = intersection.value() - seg.a;
            Vector<T, 2> seg_vec = seg.to_vector();
            T t = to_pt.dot_product(seg_vec) / seg_vec.dot_product(seg_vec);
            
            if (t >= 0 && t <= 1) {
                return true;
            }
        }
        
        return false;
    }

}