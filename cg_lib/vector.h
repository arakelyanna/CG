// vector.h
#pragma once
#include "point.h"
#include <cmath>

namespace cg {
    template<typename T>
    struct Vector {
        T x, y;
        
        Vector() : x(0), y(0) {}
        Vector(T x, T y) : x(x), y(y) {}
        Vector(const Coord<T>& from, const Coord<T>& to) : x(to.x - from.x), y(to.y - from.y) {}
        
        Vector operator+(const Vector& o) const { return {x + o.x, y + o.y}; }
        Vector operator-(const Vector& o) const { return {x - o.x, y - o.y}; }
        Vector operator*(T s) const { return {x * s, y * s}; }
        Vector operator/(T s) const { return {x / s, y / s}; }
        Vector operator-() const { return {-x, -y}; }
        
        T dot(const Vector& o) const { return x * o.x + y * o.y; }
        T cross(const Vector& o) const { return x * o.y - y * o.x; }
        
        T length_sq() const { return x * x + y * y; }
        double length() const { return std::sqrt(static_cast<double>(length_sq())); }
        
        Vector normalize() const {
            double len = length();
            return {static_cast<T>(x / len), static_cast<T>(y / len)};
        }
        
        Vector perpendicular() const { return {-y, x}; }
        
        // Returns orientation: positive = counter-clockwise, negative = clockwise, 0 = collinear
        T orientation(const Vector& o) const { return cross(o); }
        
        double angle() const { return std::atan2(static_cast<double>(y), static_cast<double>(x)); }
        
        double angle_with(const Vector& o) const {
            return std::acos(dot(o) / (length() * o.length()));
        }
        
        Vector project_onto(const Vector& o) const {
            return o * (dot(o) / o.dot(o));
        }
    };
}