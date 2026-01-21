#pragma once
#include "coord.h"
#include "vector.h"
#include <array>
#include <type_traits>
#include <iostream>

namespace cg {
    template<typename T, size_t n>
    struct Point {
        static_assert(std::is_arithmetic_v<T>, "Point template parameter must be an arithmetic type");
        
        std::array<Coord<T>, n> coords{};
        Point() = default;
        Point(std::initializer_list<T> coords_list) {
            assert(coords_list.size() <= n);
            size_t i = 0;
            for (const auto& val : coords_list) {
                coords[i++] = val;
            }
        }
        
        bool operator==(const Point& o) const { 
            for (size_t i = 0; i < n; ++i) {
                if (coords[i] != o.coords[i]) return false;
            }
            return true;
        }
        
        bool operator!=(const Point& o) const { 
            return !(*this == o);
        }
        
        Coord<T>& operator[](size_t index) { 
            assert(index < n);
            return coords[index]; 
        }
        
        const Coord<T>& operator[](size_t index) const { 
            assert(index < n);
            return coords[index]; 
        }
        
        Point operator+(const Vector<T, n>& v) const {
            Point result;
            for (size_t i = 0; i < n; ++i) {
                result.coords[i] = coords[i] + v[i];
            }
            return result;
        }

        Vector<T, n> operator-(const Point& other) const {
            Vector<T, n> result;
            for (size_t i = 0; i < n; ++i) {
                result[i] = coords[i] - other.coords[i];
            }
            return result;
        }

        operator Vector<T, n>() const {
            Vector<T, n> result;
            for (size_t i = 0; i < n; ++i) {
                result[i] = coords[i];
            }
            return result;
        }
        
        friend std::ostream& operator<<(std::ostream& out, const Point& p) {
            out << "( ";
            for (size_t i = 0; i < n; ++i) {
                out << p.coords[i];
                if (i < n - 1) out << ", ";
            }
            out << " )";
            return out;
        }
    };
}