#pragma once
#include "Vector.h"
#include "Segment.h"

template<size_t dim, typename coord_t>
struct Line
{
	using Point_t = Point<dim, coord_t>;
    Line(Point_t p1, Point_t p2) : p1(p1), p2(p2) {}
    constexpr void formula(){
        static_assert(dim==2, "The dimension should be 2!");

        A=p1[0]-p2[0];
        B=p1[1]-p2[1];
        C=Vector<dim, coord_t>::orientation(p1, p2);
    }

    bool is_parallel_to(const Line& other){
        static_assert(dim==2, "The dimension should be 2!");
        return (Vector<dim, coord_t>::orientation(p2-p1, other.p2-other.p1) == 0);
    }

    bool contains(Point_t p){
        return (Vector<dim, coord_t>::orientation(p2-p1, p) == 0);
    }

	Point_t p1;
	Point_t p2;

    coord_t A;
    coord_t B;
    coord_t C;


};

template<size_t dim, typename coord_t>
bool intersection(const Line<dim, coord_t>& l1, const Line<dim, coord_t>& l2){
    return l1.is_parallel_to(l2);
}

template<size_t dim, typename coord_t>
bool intersection(const Line<dim, coord_t>& l, const Segment<dim, coord_t>& s){
    return (Vector<dim, coord_t>::orientation(l.p1, s.p1)*Vector<dim, coord_t>::orientation(l.p1, s.p2) <= 0);
}



template<size_t dim, typename coord_t>
using Line = Line<dim, coord_t>;
