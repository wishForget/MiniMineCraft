#include "LandCoverGenerator.h"
#include "SingletonShader.h"
#include "BlockUtil.h"
#include "WorldInfo.h"
#include "noise.h"

BlockGenerator* LandCoverGenerator::gen = new BlockGenerator();

void LandCoverGenerator::waterGenerator(Chunk * chunk)
{
	//int waterLevel = 15;
	for (map<vector<int>, float>::iterator iter = chunk->heightMap.begin(); iter != chunk->heightMap.end(); iter++) {
		int h = iter->second, x = iter->first[0], z = iter->first[1];
		if (h < WorldInfo::waterLevel) {
			string id = BlockUtil::IDBuilder(x, h, z);
			Block* waterBlock1;
			//id = BlockUtil::IDBuilder(x, h, z);
			waterBlock1 = gen->getBlock(2, new Point3(x, h, z),
				SingletonShader::getLightShader());
			waterBlock1->setVisible(true);
			(*(chunk->getBlockMapAddress()))[id] = waterBlock1;
			BlockUtil::addBlockInLandCoverGen(chunk, waterBlock1);

			Block* waterBlock;
			id = BlockUtil::IDBuilder(x, WorldInfo::waterLevel, z);
			waterBlock = gen->getBlock(12, new Point3(x, WorldInfo::waterLevel, z),
				SingletonShader::getLightShader());
			waterBlock->setVisible(true);
			(*(chunk->getTransparentBlockMapAddress()))[id] = waterBlock;
		}
	}
}

void LandCoverGenerator::landCoverGenerator(Chunk * chunk)
{
	for (map<vector<int>, float>::iterator iter = chunk->heightMap.begin(); iter != chunk->heightMap.end(); iter++) {
		int y = iter->second, x = iter->first[0], z = iter->first[1];
		Block* block;
		string id;
		if (y < WorldInfo::waterLevel) {
			continue;
		}
		if (WorldInfo::waterLevel <= y && y < 16) {
			//É³×Ó
			id = BlockUtil::IDBuilder(x, y, z);
			block = gen->getBlock(0, new Point3(x, y, z),
				SingletonShader::getLightShader());	
		}
		else if (y <= 24) {
			id = BlockUtil::IDBuilder(x, y, z);
			block = gen->getBlock(0, new Point3(x, y, z),
				SingletonShader::getLightShader());
		}
		else {
			float res = simplex2(rand()%100, rand() % 100, 4, 0.5, 2);
			id = BlockUtil::IDBuilder(x, y, z);
			if (res > 0.7 && res < 0.85) {
				block = gen->getBlock(11, new Point3(x, y, z),
					SingletonShader::getLightShader());
			}
			else {
				block = gen->getBlock(4, new Point3(x, y, z),
					SingletonShader::getLightShader());
			}
		}
		block->setVisible(true);
		//if (block->getBlockData()->opaque) {
		//	(*(chunk->getBlockMapAddress()))[id] = block;
		//}
		//else {
		//	//(*(chunk->getBlockMapAddress()))[id] = block;
		//	(*(chunk->getTransparentBlockMapAddress()))[id] = block;
		//}
		block->getBlockData()->opaque ? (*(chunk->getBlockMapAddress()))[id] = block : (*(chunk->getTransparentBlockMapAddress()))[id] = block;
		BlockUtil::addBlockInLandCoverGen(chunk, block);
	}
}

void LandCoverGenerator::plandGenerator(Chunk * chunk)
{
	for (map<vector<int>, float>::iterator iter = chunk->heightMap.begin(); iter != chunk->heightMap.end(); iter++) {
		int y = iter->second + 1, x = iter->first[0], z = iter->first[1];
		int r = rand() % 10;
		if (r <= 8.5) { // 10%ÓÐÖ²Îï
			continue;
		}
		Block* block;
		string id;
		float res = rand() % 100;
		if (y > 21 || y <= WorldInfo::waterLevel + 1) {
			continue;
		}
		if (res < 10) {
			id = BlockUtil::IDBuilder(x, y, z);
			block = gen->getBlock(6, new Point3(x, y, z),
				SingletonShader::getLightShader());
		}
		else if (res >= 10 && res < 20) {
			id = BlockUtil::IDBuilder(x, y, z);
			block = gen->getBlock(7, new Point3(x, y, z),
				SingletonShader::getLightShader());
		}
		else if (res >= 20 && res < 30) {
			id = BlockUtil::IDBuilder(x, y, z);
			block = gen->getBlock(8, new Point3(x, y, z),
				SingletonShader::getLightShader());
		}
		else if (res >= 30 && res < 40) {
			id = BlockUtil::IDBuilder(x, y, z);
			block = gen->getBlock(9, new Point3(x, y, z),
				SingletonShader::getLightShader());
		}
		else if (res >= 40 && res < 95) {
			id = BlockUtil::IDBuilder(x, y, z);
			block = gen->getBlock(10, new Point3(x, y, z),
				SingletonShader::getLightShader());
		}
		//²£Á§¹þ¹þ¹þ¹þ¹þ¹þ¹þ¹þ
		else {
			id = BlockUtil::IDBuilder(x, y, z);
			block = gen->getBlock(3, new Point3(x, y, z),
				SingletonShader::getLightShader());
		}

		//if (block->getBlockData()->opaque) {
		//	(*(chunk->getBlockMapAddress()))[id] = block;
		//}
		//else {
		//	//(*(chunk->getBlockMapAddress()))[id] = block;
		//	(*(chunk->getTransparentBlockMapAddress()))[id] = block;
		//}
		block->getBlockData()->opaque ? (*(chunk->getBlockMapAddress()))[id] = block : (*(chunk->getTransparentBlockMapAddress()))[id] = block;
	}
}

void LandCoverGenerator::buildGenerator(Chunk * chunk)
{
}

void LandCoverGenerator::singleGenerator(Chunk * chunk, Point3 point)
{
	int x = point.x, y = point.y, z = point.z;
	string id = BlockUtil::IDBuilder(x, y, z);
	Block* block;
	if (y < 9) {
		float res = simplex2(10 * x, 10 * z, 4, 0.5, 2);
		if (res < 0.5) {
			block = gen->getBlock(11, new Point3(x, y, z),
				SingletonShader::getLightShader());
		}
		else {
			block = gen->getBlock(1, new Point3(x, y, z),
				SingletonShader::getLightShader());
		}
	}
	else {
		block = gen->getBlock(1, new Point3(x, y, z),
			SingletonShader::getLightShader());
	}
	block->setVisible(true);
	block->getBlockData()->opaque 
		? (*(chunk->getBlockMapAddress()))[id] = block 
		: (*(chunk->getTransparentBlockMapAddress()))[id] = block;

}
