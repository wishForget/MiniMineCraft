#include "BlockUtil.h"
#include "Chunk.h"
#include "Control.h"
#include "WorldInfo.h"
#include "LandCoverGenerator.h"
#include <cmath>


BlockUtil::BlockUtil()
{
}


BlockUtil::~BlockUtil()
{
}

void BlockUtil::imgCoord2textureCoord(std::vector<Point2> points, float texLoc[])
{
	// point为右下角点，前后左右上下
	float x, y;
	float singBlockPx = 16.0 / 256.0;
	std::vector<Square> block;
	float offset = 0.02;
	for (unsigned int i = 0; i < points.size(); i++) {
		x = points[i].x;
		y = points[i].y;
		Square sq;
		//右下 右上 左上 左下
		sq.points.push_back(Point2(singBlockPx*(x + offset), singBlockPx*(y - offset)));
		sq.points.push_back(Point2(singBlockPx*(x + offset), singBlockPx*(y - 1 + 2 * offset)));
		sq.points.push_back(Point2(singBlockPx*(x + 1 - 2 * offset), singBlockPx*(y - 1 + 2 * offset)));
		sq.points.push_back(Point2(singBlockPx*(x + 1 - 2 * offset), singBlockPx*(y - offset)));
		block.push_back(sq);
	}
	int k = 0;
	for (unsigned int i = 0; i < block.size(); i++) {
		Square sq = block[i];
		texLoc[k++] = sq.points[0].x;
		texLoc[k++] = sq.points[0].y;
		texLoc[k++] = sq.points[1].x;
		texLoc[k++] = sq.points[1].y;
		texLoc[k++] = sq.points[2].x;
		texLoc[k++] = sq.points[2].y;

		texLoc[k++] = sq.points[0].x;
		texLoc[k++] = sq.points[0].y;
		texLoc[k++] = sq.points[2].x;
		texLoc[k++] = sq.points[2].y;
		texLoc[k++] = sq.points[3].x;
		texLoc[k++] = sq.points[3].y;
	}
}

void BlockUtil::setVisible(Chunk * chunk, Block * block)
{
	//当方块block被破坏后，设置相临方块的可见性
	Block* curBlock = block;
	bool visible = false;
	Point3* loc = curBlock->getBlockData()->getLoc();
	int x = loc->x, y = loc->y, z = loc->z;
	string ids[] = { IDBuilder(x + 1, y, z), IDBuilder(x - 1, y, z), 
					 IDBuilder(x, y + 1, z), IDBuilder(x, y - 1, z), 
					 IDBuilder(x, y, z + 1), IDBuilder(x, y, z - 1) };
	
	for (int i = 0; i < 6; i++) {
		//string curID = ids[i];
		chunk->showBlock(ids[i]);
		//只要有一个相临块不存在，即可见（暂时用着，后续再改进
		//if (0 == chunk->getBlockMap().count(curID)) {
		//	visible = true;
		//	break;
		//}
	}
	//curBlock->setVisible(visible);
}

void BlockUtil::setVisible(Chunk * chunk, string id)
{
	Block* curBlock;
	unordered_map<string, Block*>::iterator blockFinder;
	blockFinder = chunk->getBlockMap().find(id);
	cout << "查找原方块" << endl;
	curBlock = blockFinder->second;
	blockFinder != chunk->getBlockMap().end();
	if (blockFinder != chunk->getBlockMap().end()) {
		cout << "原方块存在" << endl;
		bool visible = false;
		curBlock = blockFinder->second;
		Point3* loc = curBlock->getBlockData()->getLoc();
		int x = loc->x, y = loc->y, z = loc->z;
		string ids[] = {IDBuilder(x + 1, y, z), IDBuilder(x - 1, y, z), IDBuilder(x, y + 1, z), 
			IDBuilder(x, y - 1, z), IDBuilder(x, y, z + 1), IDBuilder(x, y, z - 1)};
		for (int i = 0; i < sizeof(ids)/sizeof(ids[0]); i++) {
			string curID = ids[i];
			//只要有一个相临块不存在，即可见（暂时用着，后续再改进
			if (0 != chunk->getBlockMap().count(curID)) {
				visible = true;
				break;
			}
		}
		curBlock->setVisible(visible);
	}
	else {
		cout << id << " 不存在！" << endl;
	}
}

void BlockUtil::setVisible(Chunk * chunk)
{

}

bool BlockUtil::ifVisible(Chunk * chunk, Block * block)
{
	Point3* loc = block->getBlockData()->getLoc();
	int x = loc->x, y = loc->y, z = loc->z;
	map<vector<int>, float> heightMap = chunk->heightMap;
	map<vector<int>, float>::iterator finder;
	finder = heightMap.find(vector<int>{x, z});
	if (finder != heightMap.end()) {
		if (chunk->getMinHeight() > y) {
			return false;
		}
		if (y >= finder->second) {
			return true;
		}
	}
	for (int _x = x - 1; _x <= x + 1; _x++) {
		for (int _z = z - 1; _z <= z + 1; _z++) {
			if (_x == x && _z == z) {
				continue;
			}
			finder = heightMap.find(vector<int>{_x, _z});
			if (finder != heightMap.end()) {
				int nearY = finder->second;
				if (nearY < y - 1) {
					return true;
				}
			}
		}
	}
	return false;
}

void BlockUtil::addBlockInLandCoverGen(Chunk * chunk, Block * block)
{
	//在生成地表覆盖阶段设置base的可见性
	Point3* loc = block->getBlockData()->getLoc();
	int x = loc->x, y = loc->y, z = loc->z;
	map<vector<int>, float> heightMap = chunk->heightMap;
	map<vector<int>, float>::iterator finder;
	int nearY = 2553;
	vector<Point3> points = vector<Point3>{Point3(x-1,0, z), Point3(x+1, 0, z), 
		Point3(x, 0, z-1), Point3(x, 0, z+1)};
	//得到四周最低的高度
	for (auto p : points) {
		finder = heightMap.find(vector<int>{(int) p.x, (int) p.z});
		if (finder != heightMap.end()) {
			nearY = min(nearY, (int)finder->second);
		}
	}
	int delta = y - nearY;
	//如果当前方块高度高于周围最低的方块高度两个单位
	unordered_map<string, Block*> hashMap = chunk->getBlockMap();
	unordered_map<string, Block*>::iterator hashFinder;
	if (delta > 1) {
		for (int h = nearY; h < y; h++) {
			LandCoverGenerator::singleGenerator(chunk, Point3(x, h, z));
		}
	}
}

bool BlockUtil::ifRender(Chunk * chunk)
{
	// 判断chunk是否被渲染
	vector<Point3> points;
	Point3 p = *(chunk->getLoc());
	int x = p.x*WorldInfo::chunkSize, z = p.z*WorldInfo::chunkSize;

	bool ifBack = true;//是否在背后
	bool ifInScreen = true; // false; //是否在视野内
	float minDis = 25535, curDis;
	points.push_back(Point3(x, chunk->getMinHeight(), z));
	points.push_back(Point3(x + 1, chunk->getMinHeight(), z));
	points.push_back(Point3(x + 1, chunk->getMinHeight(), z + 1));
	points.push_back(Point3(x, chunk->getMinHeight(), z + 1));

	points.push_back(Point3(x, chunk->getMaxHeight(), z));
	points.push_back(Point3(x + 1, chunk->getMaxHeight(), z));
	points.push_back(Point3(x + 1, chunk->getMaxHeight(), z + 1));
	points.push_back(Point3(x, chunk->getMaxHeight(), z + 1));

	//计算是否有点在窗口内
	//for (int i = 0; i < points.size(); i++) {
	//	glm::vec4 projectRes = WorldInfo::projection*WorldInfo::view*glm::vec4(points[i].x, points[i].y, points[i].z, 1);
	//	//cout << "chunk project res is " << projectRes.x << " " << projectRes.y << endl;
	//	if (BlockUtil::inScreen(Point2(projectRes.x, projectRes.y))) {
	//		ifInScreen = true;
	//		break;
	//	}
	//} 
	//计算距离和是否有点在前方
	for (int i = 0; i < points.size(); i++) {
		curDis = glm::length(glm::vec3(
			Control::camera->Position.x, 0, Control::camera->Position.z) - glm::vec3(points[i].x, 0, points[i].z));
		minDis = minDis > curDis ? curDis : minDis;
		double res = glm::dot(Control::camera->Front, (glm::vec3(points[i].x, 0, points[i].z)- Control::camera->Position));
		if (res > 0) {
			ifBack = false;
			break;
		}
	}
	//如果超出渲染距离或者在背后，则不渲染。
	return (!ifInScreen && (minDis > WorldInfo::renderRadius || (ifBack && minDis > WorldInfo::chunkSize))) ? false : true;
}

void BlockUtil::ScreenToWorld(double x, double y, double z, double modelview[16], double projection[16], int viewport[4], double & _x, double & _y, double & _z)
{
	//float a[16];
	//glm::unProject()
}

bool BlockUtil::inScreen(Point2 point)
{
	if (point.x < 0) return false;
	if (point.y < 0) return false;
	if (point.x > Control::SCR_WIDTH) return false;
	if (point.y > Control::SCR_HEIGHT) return false;
	return true;
}

