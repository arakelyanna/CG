// intersection.h
#pragma once
#include "vector.h"
#include "line.h"
#include "segment.h"
#include "ray.h"
#include <optional>
#include <cmath>
#include <vector>

namespace cg {

    template<typename T>
    std::optional<Point<T>> intersect(const Line<T>& l1, const Line<T>& l2) {
        T det = l1.dir.cross(l2.dir);
        
        if (det == 0) return std::nullopt; // Parallel or coincident
        
        Vector<T> w(l1.p, l2.p);
        T t = w.cross(l2.dir) / det;
        
        return l1.point_at(t);
    }

    template<typename T>
    std::optional<Point<T>> intersect(const Segment<T>& s1, const Segment<T>& s2) {
        Vector<T> d1 = s1.to_vector();
        Vector<T> d2 = s2.to_vector();
        Vector<T> w(s1.a, s2.a);
        
        T det = d1.cross(d2);
        if (det == 0) return std::nullopt;
        
        T t1 = w.cross(d2) / det;
        T t2 = w.cross(d1) / det;
        
        if (t1 >= 0 && t1 <= 1 && t2 >= 0 && t2 <= 1) {
            return Point<T>{s1.a.x + d1.x * t1, s1.a.y + d1.y * t1};
        }
        
        return std::nullopt;
    }

    template<typename T>
    std::optional<Point<T>> intersect(const Line<T>& line, const Ray<T>& ray) {
        T det = line.dir.cross(ray.dir);
        if (det == 0) return std::nullopt;
        
        Vector<T> w(line.p, ray.origin);
        T t_ray = w.cross(line.dir) / det;
        
        if (t_ray < 0) return std::nullopt;
        
        return ray.point_at(t_ray);
    }

    template<typename T>
    std::optional<Point<T>> intersect(const Ray<T>& ray, const Line<T>& line) {
        return intersect(line, ray);
    }

    template<typename T>
    std::optional<Point<T>> intersect(const Vector<T>& v1, const Vector<T>& v2, 
                                    const Point<T>& p1 = {0, 0}, 
                                    const Point<T>& p2 = {0, 0}) {
        T det = v1.cross(v2);
        if (det == 0) return std::nullopt;
        
        Vector<T> w(p1, p2);
        T t = w.cross(v2) / det;
        
        return Point<T>{p1.x + v1.x * t, p1.y + v1.y * t};
    }

    // Convex hull using Graham scan
    template<typename T>
    std::vector<Point<T>> convex_hull(std::vector<Point<T>> points) {
        if (points.size() < 3) return points;
        
        // Find lowest point (and leftmost if tie)
        auto min_it = std::min_element(points.begin(), points.end(),
            [](const Point<T>& a, const Point<T>& b) {
                return a.y < b.y || (a.y == b.y && a.x < b.x);
            });
        
        Point<T> pivot = *min_it;
        
        // Sort by polar angle
        std::sort(points.begin(), points.end(),
            [&pivot](const Point<T>& a, const Point<T>& b) {
                if (a == pivot) return true;
                if (b == pivot) return false;
                
                Vector<T> va(pivot, a);
                Vector<T> vb(pivot, b);
                T cross = va.cross(vb);
                
                if (cross == 0) {
                    return va.length_sq() < vb.length_sq();
                }
                return cross > 0;
            });
        
        std::vector<Point<T>> hull;
        for (const auto& p : points) {
            while (hull.size() >= 2) {
                Vector<T> v1(hull[hull.size() - 2], hull[hull.size() - 1]);
                Vector<T> v2(hull[hull.size() - 1], p);
                if (v1.cross(v2) <= 0) {
                    hull.pop_back();
                } else {
                    break;
                }
            }
            hull.push_back(p);
        }
        
        return hull;
    };

} 