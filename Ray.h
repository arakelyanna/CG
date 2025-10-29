#pragma once
#include <array>
#include <type_traits>
#include <cassert>
#include <cmath>
#include <stdexcept>
#include "Vector.h"
#include "Segment.h"
#include "Line.h"



template<size_t dim, typename coord_t>
struct Ray
{
	using Point_t = Point<dim, coord_t>;
	
	Ray(const Point_t& start, const Point_t& dir) : start(start), dir(dir) {}
	
	Point_t start;
	Point_t dir;
	constexpr void formula(){
        static_assert(dim==2, "The dimension should be 2!");

        A=start[0]-dir[0];
        B=start[1]-dir[1];
        C=Vector<dim, coord_t>::orientation(start, dir);

    }

    bool is_parallel_to(const Line<dim, coord_t>& other){
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

