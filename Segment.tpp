#pragma once
#include "Segment.h"
#include "Vector.h"


template<size_t dim, typename coord_t>
Segment<dim, coord_t>::Segment(const Point_t& p1, const Point_t& p2) : p1(p1), p2(2) {}

template<size_t dim, typename coord_t>
coord_t Segment<dim, coord_t>::length() const {
	return (p2-p1).length();
}

template<size_t dim, typename coord_t>
double Segment<dim, coord_t>::angle(const Segment& other) const{
	double alpha = Vector<dim, coord_t>::dot_product(Vector(p1, p2), Vector(other.p1, other.p2))/
					length()*other.length();
	return std::acos(alpha);
}

template<size_t dim, typename coord_t>
bool intersection(const Segment<dim, coord_t>& s1, const Segment<dim, coord_t>& s2) {

	auto o11 = Vector<dim, coord_t>::orientation(Vector(s1.p2, s1.p1), Vector(s2.p2, s1.p1));
	auto o12 = Vector<dim, coord_t>::orientation(Vector(s1.p2, s1.p1), Vector(s2.p2, s1.p1));


	auto o21 = Vector<dim, coord_t>::orientation(Vector(s2.p2, s2.p1), Vector(s2.p2, s1.p1));
	auto o22 = Vector<dim, coord_t>::orientation(Vector(s2.p2, s2.p1), Vector(s2.p2, s1.p1));

	return o11 * o12 < 0 && o21 * o22 < 0;
}

