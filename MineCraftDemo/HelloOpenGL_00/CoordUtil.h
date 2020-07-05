#pragma once
#include "Point.h"
class CoordUtil
{
public:
	CoordUtil();
	~CoordUtil();
	static void world2Chunk(Point3 point, int &x, int &y, int &z);
	static void world2Block(Point3 point, int &x, int &y, int &z);
};

