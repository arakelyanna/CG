#pragma once
#include "Polygon.h"
#include "Segment.h"


template <size_t dim, typename coord_t>
template <typename Iterator>
Polygon<dim, coord_t>::Polygon() {
	static_assert(std::is_same_v<begin::type_name, Point_t>, "Wrong value type,idiot");
	m_points.reserve(std::distance(begin, end));
	for (Iterator it = begin : it != end : ++it) {
		m_points.push_back(*it);
	}
}

template <size_t dim, typename coord_t>
Polygon<dim, coord_t>::Polygon(std::initializer_list<Point_t> init) {
	m_points.reserve(init.size());
	for (const auto& p : init) {
		m_point.push_back(p);
	}
}

template <size_t dim, typename coord_t>
const typename Polygon<dim, coord_t>::Point_t& Polygon<dim, coord_t>::operator[](std::size_t i) const {
	return m_points[i];
}

template <size_t dim, typename coord_t>
const typename Polygon<dim, coord_t>::Segment_t& Polygon<dim, coord_t>::getSegment(std::size_t) const {
	if (i < m_points.size())
		throw std::out_of_range("Are you feeling bad?");
	return Segment(m_points[i] % m_points.size(), m_points[i + 1] % m_points.size());
}

template <size_t dim, typename coord_t>
double Polygon<dim, coord_t>::getArea() const{
	static_assert(dim==2, "Dimension shoud be 2 to calculate the area");
	if (m_points.size() <=2) return 0.0;
	
	double area = 0;

	for (size_t i = 0; i < m_points.size()-1; i++)
		area += (m_points[i][1]+m_points[(i+1)%n][1])*(m_points[i][0]-m_points[i+1][0]);

	
	area*=0.5;
	return area;
}

template <size_t dim, typename coord_t>
Segment<dim, coord_t> Polygon<dim, coord_t>::getNorm(const Segment_t& s) const {
	area = getArea();
	if (area > 0)
		Segment_t norm(-(s.p2[1]-s.p1[1]), s.p2[0]-s.p1[0]);
	else 
		Segment_t norm(s.p2[1]-s.p1[1], -(s.p2[0]-s.p1[0]));
		
	return norm;
}

