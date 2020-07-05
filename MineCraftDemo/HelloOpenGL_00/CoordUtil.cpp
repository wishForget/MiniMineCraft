#include "CoordUtil.h"
#include "WorldInfo.h"
#include <cmath>

CoordUtil::CoordUtil()
{
}


CoordUtil::~CoordUtil()
{
}

void CoordUtil::world2Chunk(Point3 point, int &x, int &y, int &z)
{
	x = floor(point.x / WorldInfo::chunkSize);
	y = 0;
	z = floor(point.z / WorldInfo::chunkSize);
}

void CoordUtil::world2Block(Point3 point, int & x, int & y, int & z)
{
}
