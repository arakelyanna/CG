#pragma once
#include <cmath>
#include <type_traits>
#include <ostream>
#include <cassert>

namespace cg {

    template <typename T>
    struct Coord {
        static_assert(std::is_arithmetic_v<T>, "Coord type is not arithmetic.");

        T coord;
        static constexpr T tolerance = 0.0001;

        Coord() : coord(0) {};
        Coord(const T& other) : coord(other) { }

        bool operator==(const Coord& other) const {
            return std::abs(other.coord - coord) <= tolerance;
        }

        bool operator!=(const Coord& other) const {
            return !(*this == other);
        }
        
        // Arithmetic operators
        Coord operator+(const Coord& other) const {
            return Coord(coord + other.coord);
        }
        
        Coord operator-(const Coord& other) const {
            return Coord(coord - other.coord);
        }
        
        Coord operator*(const Coord& other) const {
            return Coord(coord * other.coord);
        }
        
        Coord operator/(const Coord& other) const {
            assert(other.coord != 0);
            return Coord(coord / other.coord);
        }
        
        Coord operator*(T scalar) const {
            return Coord(coord * scalar);
        }
        
        Coord operator/(T scalar) const {
            assert(scalar != 0);
            return Coord(coord / scalar);
        }
        
        operator T&() {
            return coord;
        }

        operator const T& () const {
            return coord;
        }

        friend std::ostream& operator<<(std::ostream& out, const Coord& c) {
            out << c.coord;
            return out;
        }
    };
}
