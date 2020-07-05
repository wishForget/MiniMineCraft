#pragma once
#include "Chunk.h"
#include "BlockGenerator.h"
static class LandCoverGenerator
{
public:
	static void waterGenerator(Chunk* chunk);  //基座生成
	static void landCoverGenerator(Chunk* chunk);  //覆盖生成
	static void plandGenerator(Chunk* chunk);  //植被生成
	static void buildGenerator(Chunk* chunk); //建筑生成
	static void singleGenerator(Chunk* chunk, Point3 point);  //生成单个方块
	static BlockGenerator* gen;
};

