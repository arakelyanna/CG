#pragma once
#include <cmath>
#include <type_traits>



template <typename T>
struct Coord_t {
	static_assert(std::is_arithmetic_v<T>, "AAAAAA! not arithmetic");

	T coord;
	static constexpr T tolerance = 0.0001;

	Coord_t() = default;
	Coord_t(const T& other) : coord(other) { }

	bool operator==(const Coord_t& other) const {
		return std::abs(other.coord - coord) <= tolerance;
	}

	bool operator!=(const Coord_t& other) const {
		return !(*this == other);
	}
	
	operator T&() {
		return coord;
	}

	operator const T& () const {
		return coord;
	}
};

