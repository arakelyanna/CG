#pragma once
#include "Vector.h"

template<size_t dim, typename coord_t>
struct Segment
{
	using Point_t = Point<dim, coord_t>;
	
	Segment(const Point_t& p1, const Point_t& p2);
	
	
	Point_t p1;
	Point_t p2;
	
	coord_t length() const;

	double angle(const Segment& other) const;

};

template<size_t dim, typename coord_t>
bool intersection(const Segment<dim, coord_t>& s1, const Segment<dim, coord_t>& s2);

#include "Segment.tpp"