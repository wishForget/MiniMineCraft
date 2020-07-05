#include "BlockData.h"
#include "BlockUtil.h"
#include <iostream>
using namespace std;


BlockData::BlockData()
{
	
}


BlockData::~BlockData()
{
}

void BlockData::setTexImgLoc(std::vector<Point2> texImgLoc)
{
	this->texImgLoc = texImgLoc;
}

void BlockData::setLoc(Point3* point)
{
	loc = point;
}

Point3 * BlockData::getLoc()
{
	return this->loc;
}


