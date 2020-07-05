#pragma once
#include <vector>
#include "Point.h"

class BlockData
{
	/*包括block中的顶点坐标、纹理坐标、纹理图片坐标以及其它属性*/
public:
	BlockData();
	~BlockData();
	
	bool collidable = false;  //是否允许碰撞
	bool opaque = true;  //是否不透明
	void setTexImgLoc(std::vector<Point2> texImgLoc);
	void setLoc(Point3* point);
	Point3* getLoc();
private:
	std::vector<Point2> texImgLoc;
	Point3* loc = new Point3();  //block坐标(x, y, z)(中心点)
};

