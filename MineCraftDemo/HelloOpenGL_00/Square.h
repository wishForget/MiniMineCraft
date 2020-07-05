#pragma once
#include <vector>
#include "Point.h"

struct Square {
	std::vector<Point2> points;
};

struct Cube {
	Point3 leftTop;
};