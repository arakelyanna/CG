#pragma once
#include "coord.h"
#include <array>
#include <cmath>
#include <type_traits>
#include <iostream>

namespace cg {
    template<typename T, size_t n>
    class Point; // Forward declaration
    
    template<typename T, size_t n>
    struct Vector {
        static_assert(std::is_arithmetic_v<T>, "Coord type is not arithmetic type.");
        
        std::array<Coord<T>, n> coords{};
        Vector() = default;
        Vector(std::initializer_list<T> coords_list) {
            assert(coords_list.size() <= n);
            size_t i = 0;
            for (const auto& val : coords_list) {
                coords[i++] = val;
            }
        }
        Vector(std::initializer_list<Coord<T>> coords_list) {
            assert(coords_list.size() <= n);
            size_t i = 0;
            for (const auto& val : coords_list) {
                coords[i++] = val;
            }
        }
        
        Coord<T>& operator[](size_t index) { 
            assert(index < n);
            return coords[index]; 
        }
        
        const Coord<T>& operator[](size_t index) const { 
            assert(index < n);
            return coords[index]; 
        }
        
        Vector operator+(const Vector& o) const {
            Vector result;
            for (size_t i = 0; i < n; ++i) {
                result.coords[i] = coords[i] + o.coords[i];
            }
            return result;
        }
        
        Vector operator-(const Vector& o) const {
            Vector result;
            for (size_t i = 0; i < n; ++i) {
                result.coords[i] = coords[i] - o.coords[i];
            }
            return result;
        }
        
        Vector operator*(T scalar) const {
            Vector result;
            for (size_t i = 0; i < n; ++i) {
                result.coords[i] = coords[i] * scalar;
            }
            return result;
        }
        
        Vector operator/(T scalar) const {
            assert(scalar != 0);
            Vector result;
            for (size_t i = 0; i < n; ++i) {
                result.coords[i] = coords[i] / scalar;
            }
            return result;
        }
        
        T operator*(const Vector& o) const { // dot product
            T sum = T{};
            for (size_t i = 0; i < n; ++i) {
                sum = sum + (coords[i] * o.coords[i]);
            }
            return sum;
        }
        
        T dot_product(const Vector& o) const {
            T sum = T{};
            for (size_t i = 0; i < n; ++i) {
                sum = sum + (coords[i] * o.coords[i]);
            }
            return sum;
        }
        
        double length() const {
            return std::sqrt(static_cast<double>(dot_product(*this)));
        }
        
        Vector normalize() const {
            double len = length();
            assert(len != 0);
            return *this / static_cast<T>(len);
        }
        
        Vector cross_product(const Vector& o) const {
            static_assert(n == 3, "Cross product is only defined for 3D vectors");
            Vector result;
            result.coords[0] = coords[1] * o.coords[2] - coords[2] * o.coords[1];
            result.coords[1] = coords[2] * o.coords[0] - coords[0] * o.coords[2];
            result.coords[2] = coords[0] * o.coords[1] - coords[1] * o.coords[0];
            return result;
        }
        
        T orientation(const Vector& o) const {
            static_assert(n == 2, "Orientation is only defined for 2D vectors");
            return coords[0] * o.coords[1] - coords[1] * o.coords[0];
        }
        
        double angle(const Vector& o) const {
            T dot_prod = dot_product(o);
            double len_product = length() * o.length();
            assert(len_product != 0);
            return std::acos(static_cast<double>(dot_prod) / len_product);
        }
        
        friend std::ostream& operator<<(std::ostream& out, const Vector& v) {
            out << "[ ";
            for (size_t i = 0; i < n; ++i) {
                out << v.coords[i];
                if (i < n - 1) out << ", ";
            }
            out << " ]";
            return out;
        }
    };
}