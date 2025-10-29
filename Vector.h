#pragma once
#include <array>
#include <type_traits>
#include <cassert>
#include <cmath>
#include <stdexcept>
#include "Coord.h"

template<size_t dim, typename coord_t>
class Vector {
private:
	static_assert(std::is_arithmetic_v<coord_t>, "AAAAAA! not arithmetic");

	using coord_type = Coord_t<coord_t>;
public:
	Vector();
	const Vector& operator=(const Vector& other);
	Vector(std::initializer_list<coord_t> lst);
	Vector& operator=(Vector&& other) noexcept;
	Vector(const Vector&) = default;
	Vector(Vector&&) noexcept = default;
	Vector(const Vector& p1, const Vector& p2);

	bool operator==(const Vector& other) const;
	bool operator !=(const Vector& other) const;
	
	coord_type& operator[](size_t i);
	const coord_type& operator[](size_t i) const;
	coord_type& get(size_t i);

	auto begin();
	auto end();
	auto cbegin();
	auto cend();
	auto rbegin();
	auto rend();
	
	auto length();
	
	static auto dot_product(const Vector& vec1, const Vector& vec2);
	static Vector cross_product(const Vector& vec1, const Vector& vec2);
	static coord_type orientation(const Vector& vec1, const Vector& vec2);
	
	~Vector() = default;

	const Vector operator+(const Vector& other) const;
	const Vector operator-(const Vector& other) const;

private:

	std::array<coord_type, dim> coords = { coord_type(0) };
};


template<size_t dim, typename coord_t>
using Point = Vector<dim, Coord_t<coord_t>>;

#include "Vector.tpp"