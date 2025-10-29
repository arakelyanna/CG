#pragma once
#include "Vector.h"
#include "Segment.h"
#include <vector>
#include <type_traits>
#include <initializer_list>


template <size_t dim, typename coord_t>
class Polygon {
public:
	using Point_t = Point<dim, coord_t>;
	using Segment_t = Segment<dim, coord_t>;
	
	template <typename Iterator>
	Polygon();
	
	Polygon(std::initializer_list<Point_t> init);
	
	const Point_t& operator[](std::size_t i) const;
	const Segment_t& getSegment(std::size_t) const;

	double getArea() const;
	Segment_t getNorm(const Segment_t& s) const;

private:
	std::vector<Point_t> m_points;
};

#include "Polygon.tpp"