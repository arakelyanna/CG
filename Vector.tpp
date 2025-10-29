#pragma once
#include "Vector.h"


template<size_t dim, typename coord_t>
Vector<dim, coord_t>::Vector() = default;

template<size_t dim, typename coord_t>
const Vector<dim, coord_t>& Vector<dim, coord_t>::operator=(const Vector& other) {
	Vector tmp(other);
	std::swap(*this, tmp);
	// for (size_t i = 0; i < dim; i++)
	// {
	// 	coords[i] = other.coords[i];
	// }

	return *this;
}

template<size_t dim, typename coord_t>
Vector<dim, coord_t>::Vector(std::initializer_list<coord_t> lst){
	assert(lst.size() == dim);
	size_t i = 0;
	for (const auto c : lst)
	{
		coords[i++] = c;
	}
}

template<size_t dim, typename coord_t>
Vector<dim, coord_t>& Vector<dim, coord_t>::operator=(Vector&& other) noexcept {
	if (this == &other)
		return *this;
	for (size_t i = 0; i < dim; ++i) {
		coords[i] = std::move(other.coords[i]);
	}
	return *this;
}

template<size_t dim, typename coord_t>
bool Vector<dim, coord_t>::operator==(const Vector& other) const {
	return coords == other.coords;
}

template<size_t dim, typename coord_t>
bool Vector<dim, coord_t>::operator !=(const Vector& other) const {
	return !(*this == other);
}

template<size_t dim, typename coord_t>
typename Vector<dim, coord_t>::coord_type& Vector<dim, coord_t>::operator[](size_t i) {
	assert(i < dim);
	return coords[i];
}

template<size_t dim, typename coord_t>
const typename Vector<dim, coord_t>::coord_type& Vector<dim, coord_t>::operator[](size_t i) const {
	assert(i < dim);
	return coords[i];
}

template<size_t dim, typename coord_t>
typename Vector<dim, coord_t>::coord_type& Vector<dim, coord_t>::get(size_t i) {
	if (i >= dim)
		throw std::out_of_range("out of range");
	return operator[](i);
}

template<size_t dim, typename coord_t>
auto Vector<dim, coord_t>::begin() {
	return coords.begin();
}

template<size_t dim, typename coord_t>
auto Vector<dim, coord_t>::end() {
	return coords.end();
}

template<size_t dim, typename coord_t>
auto Vector<dim, coord_t>::cbegin() {
	return coords.cbegin();
}

template<size_t dim, typename coord_t>
auto Vector<dim, coord_t>::cend() {
	return coords.cend();
}

template<size_t dim, typename coord_t>
auto Vector<dim, coord_t>::rbegin() {
	return coords.rbegin();
}

template<size_t dim, typename coord_t>
auto Vector<dim, coord_t>::rend() {
	return coords.rend();
}

template<size_t dim, typename coord_t>
auto Vector<dim, coord_t>::length()
{
	return std::sqrt(dot_product(*this, *this));
}

template<size_t dim, typename coord_t>
auto Vector<dim, coord_t>::dot_product(const Vector& vec1, const Vector& vec2) {
	decltype(vec1.coords[0] * vec2.coords[0]) res = 0;
	for (size_t i = 0; i < dim; i++)
	{
		res += vec1.coords[i] * vec2.coords[i];
	}
	return res; 
}

template<size_t dim, typename coord_t>
Vector<dim, coord_t> Vector<dim, coord_t>::cross_product(const Vector& vec1, const Vector& vec2) {
	static_assert(dim == 3, "hm, stupid");

	return {
		vec1[1] * vec2[2] - vec1[2] * vec2[1],
		vec1[2] * vec2[0] - vec1[0] * vec2[2],
		vec1[0] * vec2[1] - vec1[1] * vec2[0]
	};
}

template<size_t dim, typename coord_t>
typename Vector<dim, coord_t>::coord_type Vector<dim, coord_t>::orientation(const Vector& vec1, const Vector& vec2) {
	static_assert(dim == 2, "hm, stupid");
	coord_type z = vec1[0] * vec2[1] - vec1[1] * vec2[0];

	assert(z == cross_product(
		Vector<3, coord_t>(vec1[0], vec1[1], 0),
		Vector<3, coord_t>(vec2[0], vec2[1], 0))[2]
	);
	return z;
}

template<size_t dim, typename coord_t>
const Vector<dim, coord_t> Vector<dim, coord_t>::operator+(const Vector& other) const {
	Vector res;
	for (size_t i = 0; i < dim; i++)
	{
		res[i] = coords[i] + other.coords[i];
	}

	return res;
}

template<size_t dim, typename coord_t>
const Vector<dim, coord_t> Vector<dim, coord_t>::operator-(const Vector& other) const {
	Vector res;
	for (size_t i = 0; i < dim; i++)
	{
		res[i] = coords[i] - other.coords[i];
	}

	return res;
}

template<size_t dim, typename coord_t>
Vector<dim, coord_t>::Vector(const Vector& p1, const Vector& p2) {
	*this = p2 - p1;
}

