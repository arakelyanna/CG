#pragma once
#include "polygon.h"

namespace cg {
    template<typename T>
    Polygon<T>::Polygon(const std::vector<Point<T>>& verts) : vertices(verts) {}

    template<typename T>
    size_t Polygon<T>::size() const {
        return vertices.size();
    }

    template<typename T>
    bool Polygon<T>::is_convex() const {
        if (vertices.size() < 3) return false;
        
        bool has_positive = false, has_negative = false;
        size_t n = vertices.size();
        
        for (size_t i = 0; i < n; ++i) {
            const auto& p1 = vertices[i];
            const auto& p2 = vertices[(i + 1) % n];
            const auto& p3 = vertices[(i + 2) % n];
            
            Vector<T> v1(p1, p2);
            Vector<T> v2(p2, p3);
            T cross = v1.cross(v2);
            
            if (cross > 0) has_positive = true;
            if (cross < 0) has_negative = true;
            if (has_positive && has_negative) return false;
        }
        return true;
    }

    template<typename T>
    void Polygon<T>::translate(const Vector<T>& v) {
        for (auto& p : vertices) {
            p.x += v.x;
            p.y += v.y;
        }
    }

    template<typename T>
    void Polygon<T>::scale(T factor, const Point<T>& center) {
        for (auto& p : vertices) {
            p.x = center.x + (p.x - center.x) * factor;
            p.y = center.y + (p.y - center.y) * factor;
        }
    }

    template<typename T>
    void Polygon<T>::rotate(double angle, const Point<T>& center) {
        double cos_a = std::cos(angle);
        double sin_a = std::sin(angle);
        
        for (auto& p : vertices) {
            T dx = p.x - center.x;
            T dy = p.y - center.y;
            p.x = center.x + static_cast<T>(dx * cos_a - dy * sin_a);
            p.y = center.y + static_cast<T>(dx * sin_a + dy * cos_a);
        }
    }

    template<typename T>
    bool Polygon<T>::contains(const Point<T>& pt) const {
        if (vertices.size() < 3) return false;
        
        int winding = 0;
        size_t n = vertices.size();
        
        for (size_t i = 0; i < n; ++i) {
            const auto& v1 = vertices[i];
            const auto& v2 = vertices[(i + 1) % n];
            
            if (v1.y <= pt.y) {
                if (v2.y > pt.y) {
                    Vector<T> edge(v1, v2);
                    Vector<T> to_pt(v1, pt);
                    if (edge.cross(to_pt) > 0) {
                        ++winding;
                    }
                }
            } else {
                if (v2.y <= pt.y) {
                    Vector<T> edge(v1, v2);
                    Vector<T> to_pt(v1, pt);
                    if (edge.cross(to_pt) < 0) {
                        --winding;
                    }
                }
            }
        }
        
        return winding != 0;
    }

    template<typename T>
    std::vector<std::vector<Point<T>>> Polygon<T>::triangulate() const {
        if (vertices.size() < 3) return {};
        if (vertices.size() == 3) return {vertices};
        
        std::vector<std::vector<Point<T>>> triangles;
        
        // Helper: Check if point is inside circumcircle of triangle
        auto in_circumcircle = [](const Point<T>& p, const Point<T>& a, 
                                const Point<T>& b, const Point<T>& c) -> bool {
            T ax = a.x - p.x, ay = a.y - p.y;
            T bx = b.x - p.x, by = b.y - p.y;
            T cx = c.x - p.x, cy = c.y - p.y;
            
            T det = (ax * ax + ay * ay) * (bx * cy - cx * by) -
                    (bx * bx + by * by) * (ax * cy - cx * ay) +
                    (cx * cx + cy * cy) * (ax * by - bx * ay);
            
            return det > 0;
        };
        
        // Helper: Check if two triangles share an edge
        auto share_edge = [](const std::vector<Point<T>>& t1, 
                            const std::vector<Point<T>>& t2) -> bool {
            int shared = 0;
            for (const auto& p1 : t1) {
                for (const auto& p2 : t2) {
                    if (p1 == p2) shared++;
                }
            }
            return shared == 2;
        };
        
        // Find bounding box
        T minX = vertices[0].x, maxX = vertices[0].x;
        T minY = vertices[0].y, maxY = vertices[0].y;
        
        for (const auto& v : vertices) {
            minX = std::min(minX, v.x);
            maxX = std::max(maxX, v.x);
            minY = std::min(minY, v.y);
            maxY = std::max(maxY, v.y);
        }
        
        T dx = maxX - minX;
        T dy = maxY - minY;
        T dmax = std::max(dx, dy);
        T midx = (minX + maxX) / static_cast<T>(2);
        T midy = (minY + maxY) / static_cast<T>(2);
        
        // Create super-triangle
        Point<T> p1(midx - 20 * dmax, midy - dmax);
        Point<T> p2(midx, midy + 20 * dmax);
        Point<T> p3(midx + 20 * dmax, midy - dmax);
        
        triangles.push_back({p1, p2, p3});
        
        // Add each point one at a time
        for (const auto& point : vertices) {
            std::vector<std::vector<Point<T>>> bad_triangles;
            
            // Find all triangles whose circumcircle contains the point
            for (const auto& tri : triangles) {
                if (in_circumcircle(point, tri[0], tri[1], tri[2])) {
                    bad_triangles.push_back(tri);
                }
            }
            
            // Find the boundary of the polygonal hole
            std::vector<std::pair<Point<T>, Point<T>>> polygon;
            
            for (const auto& tri : bad_triangles) {
                for (int i = 0; i < 3; ++i) {
                    Point<T> a = tri[i];
                    Point<T> b = tri[(i + 1) % 3];
                    
                    bool is_shared = false;
                    for (const auto& other : bad_triangles) {
                        if (tri[0] == other[0] && tri[1] == other[1] && tri[2] == other[2]) 
                            continue;
                        
                        if (share_edge({a, b}, other)) {
                            is_shared = true;
                            break;
                        }
                    }
                    
                    if (!is_shared) {
                        polygon.push_back({a, b});
                    }
                }
            }
            
            // Remove bad triangles
            triangles.erase(
                std::remove_if(triangles.begin(), triangles.end(),
                    [&bad_triangles](const std::vector<Point<T>>& tri) {
                        for (const auto& bad : bad_triangles) {
                            if (tri[0] == bad[0] && tri[1] == bad[1] && tri[2] == bad[2])
                                return true;
                        }
                        return false;
                    }),
                triangles.end()
            );
            
            // Re-triangulate the polygonal hole
            for (const auto& edge : polygon) {
                triangles.push_back({edge.first, edge.second, point});
            }
        }
        
        // Remove triangles that contain vertices from super-triangle
        triangles.erase(
            std::remove_if(triangles.begin(), triangles.end(),
                [&p1, &p2, &p3](const std::vector<Point<T>>& tri) {
                    for (const auto& p : tri) {
                        if (p == p1 || p == p2 || p == p3) return true;
                    }
                    return false;
                }),
            triangles.end()
        );
        
        return triangles;
    }

    template<typename T>
    double Polygon<T>::area() const {
        if (vertices.size() < 3) return 0;
        
        double sum = 0;
        size_t n = vertices.size();
        
        for (size_t i = 0; i < n; ++i) {
            size_t j = (i + 1) % n;
            sum += static_cast<double>(vertices[i].x * vertices[j].y);
            sum -= static_cast<double>(vertices[j].x * vertices[i].y);
        }
        
        return std::abs(sum) / 2.0;
    }
}