#include "cg_lib.h"
#include <iostream>

int main() {
    // Using generic types - int, float, double
    cg::Point<double, 2> p1({0, 0});
    cg::Point<double, 2> p2({3, 4});
    
    cg::Vector<double, 2> v1({1, 0});
    cg::Vector<double, 2> v2({0, 1});
    
    std::cout << "Vector v1: " << v1 << "\n";
    std::cout << "Vector v2: " << v2 << "\n";
    std::cout << "Dot product: " << v1.dot_product(v2) << "\n";
    
    // Cross product only works for 3D vectors
    cg::Vector<double, 3> v3d_1({1, 0, 0});
    cg::Vector<double, 3> v3d_2({0, 1, 0});
    std::cout << "Cross product (3D): " << v3d_1.cross_product(v3d_2) << "\n";
    
    // Create vector from two points
    cg::Vector<double, 2> v_from_points = p2 - p1;
    std::cout << "Vector from p1 to p2: " << v_from_points << "\n";
    std::cout << "Vector length: " << v_from_points.length() << "\n";
    
    // Line intersection
    cg::Line<double, 2> line1(cg::Point<double, 2>({0, 0}), cg::Vector<double, 2>({1, 1}));
    cg::Line<double, 2> line2(cg::Point<double, 2>({0, 2}), cg::Vector<double, 2>({1, -1}));
    
    auto intersection = cg::intersect(line1, line2);
    if (intersection) {
        std::cout << "Lines intersect at: " << *intersection << "\n";
    }
    
    cg::Segment<double, 2> seg1({0, 0}, {2, 2});
    cg::Segment<double, 2> seg2({0, 2}, {2, 0});
    
    std::cout << "Segments intersect: " << (cg::intersection(seg1, seg2) ? "yes" : "no") << "\n";
    
    cg::Polygon<double, 2> poly({
        {0, 0}, {4, 0}, {4, 3}, {0, 3}
    });
    
    std::cout << "Polygon is convex: " << (poly.is_convex() ? "yes" : "no") << "\n";
    std::cout << "Polygon area: " << poly.area() << "\n";
    
    poly.translate({1, 1});
    
    auto triangles = poly.triangulate();
    std::cout << "Number of triangles: " << triangles.size() << "\n";

    
    cg::Ray<double, 2> ray({0, 0}, {1, 1});
    cg::Line<double, 2> line3({2, 0}, {0, 1});
    
    auto ray_int = cg::intersect(ray, line3);
    if (ray_int) {
        std::cout << "Ray-line intersect at: " << *ray_int << "\n";
    }
    
    return 0;
}