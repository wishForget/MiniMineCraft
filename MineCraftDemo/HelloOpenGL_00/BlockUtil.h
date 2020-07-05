#pragma once
#include "Point.h"
#include "Square.h"
#include <vector>
#include <iostream>
#include <string>
using namespace std;
class Block;
class Chunk;
static class BlockUtil
{
public:
	BlockUtil();
	~BlockUtil();
	static void imgCoord2textureCoord(std::vector<Point2> points, float texLoc[]);
	//static void imgCoord2textureCoord2(std::vector<Point2> points, float texLoc[24]);

	static void setVisible(Chunk* chunk, Block* block);
	static void setVisible(Chunk *chunk, string id);
	static void setVisible(Chunk *chunk);
	static bool ifVisible(Chunk* chunk, Block* block);
	static void addBlockInLandCoverGen(Chunk* chunk, Block* block);
	//static void setVisible(World* world, Block* block);
	//static void setVisible(World* world, string id);
	static string IDBuilder(int x, int y, int z) {
		return to_string(x) + "&" + to_string(y) + "&" + to_string(z);
	};
	static bool ifRender(Chunk* chunk);
	static void ScreenToWorld(double x, double y, double z, double modelview[16], double projection[16], int viewport[4], double &_x, double &_y, double &_z);
private:
	static bool inScreen(Point2 point);
};

