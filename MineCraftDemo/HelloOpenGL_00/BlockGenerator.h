#pragma once
#include "Block.h"
#include "Model.h"
#include "BlockData.h"
#include "Point.h"
#include "Square.h"
class BlockGenerator
{
public:
	BlockGenerator();
	~BlockGenerator();
	BlockGenerator* getInstance();
	Block *getBlock(int type, Point3* loc, Shader* shader);

private:
	BlockGenerator* gen = nullptr;
	Block *getGrassBlock(Point3* loc, Shader* shader);
	Block *getSoilBlock(Point3* loc, Shader* shader);
	Block *getSandBlock(Point3* loc, Shader* shader);
	Block* getStoneBlock(Point3 *loc, Shader *shader);
	Block *getGlassBlock(Point3* loc, Shader* shader);
	Block *getDandelionBlock(Point3* loc, Shader* shader);
	Block *getSnowBlock(Point3* loc, Shader* shader);
	Block *getSunflowerBlock(Point3* loc, Shader* shader);
	Block *getWinterJasmineBlock(Point3* loc, Shader* shader);
	Block *getTulipBlock(Point3* loc, Shader* shader);
	Block *getRoseBlock(Point3* loc, Shader* shader);
	Block *getTallGrassBlock(Point3 *loc, Shader* shader);
	Block *getWaterBlock(Point3 *loc, Shader* shader);
};

