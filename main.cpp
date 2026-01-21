#include "cg_lib.h"
#include <iostream>

int main() {
    // Using generic types - int, float, double
    cg::Point<double> p1(0, 0);
    cg::Point<double> p2(3, 4);
    
    cg::Vector<double> v1(1, 0);
    cg::Vector<double> v2(0, 1);
    
    std::cout << "Dot product: " << v1.dot(v2) << "\n";
    std::cout << "Cross product: " << v1.cross(v2) << "\n";
    std::cout << "Vector length: " << cg::Vector<double>(p1, p2).length() << "\n";
    
    // Line intersection
    cg::Line<double> line1(cg::Point<double>(0, 0), cg::Vector<double>(1, 1));
    cg::Line<double> line2(cg::Point<double>(0, 2), cg::Vector<double>(1, -1));
    
    auto intersection = cg::intersect(line1, line2);
    if (intersection) {
        std::cout << "Lines intersect at: (" << intersection->x << ", " 
                  << intersection->y << ")\n";
    }
    
    // Segment intersection
    cg::Segment<double> seg1({0, 0}, {2, 2});
    cg::Segment<double> seg2({0, 2}, {2, 0});
    
    auto seg_int = cg::intersect(seg1, seg2);
    if (seg_int) {
        std::cout << "Segments intersect at: (" << seg_int->x << ", " 
                  << seg_int->y << ")\n";
    }
    
    // Polygon operations
    cg::Polygon<double> poly({
        {0, 0}, {4, 0}, {4, 3}, {0, 3}
    });
    
    std::cout << "Polygon is convex: " << (poly.is_convex() ? "yes" : "no") << "\n";
    std::cout << "Polygon area: " << poly.area() << "\n";
    
    poly.translate({1, 1});
    poly.scale(2.0);
    
    auto triangles = poly.triangulate();
    std::cout << "Number of triangles: " << triangles.size() << "\n";
    
    // Convex hull
    std::vector<cg::Point<int>> points = {{0, 0}, {1, 1}, {2, 0}, {1, 2}, {1, 0}};
    auto hull = cg::convex_hull(points);
    std::cout << "Convex hull has " << hull.size() << " vertices\n";
    
    // Ray-line intersection
    cg::Ray<double> ray({0, 0}, {1, 1});
    cg::Line<double> line3({2, 0}, {0, 1});
    
    auto ray_int = cg::intersect(ray, line3);
    if (ray_int) {
        std::cout << "Ray-line intersect at: (" << ray_int->x << ", " 
                  << ray_int->y << ")\n";
    }
    
    return 0;
}