#include "Chunk.h"
#include "noise.h"
#include "Control.h"
#include "BlockGenerator.h"
#include "BlockUtil.h"
#include "SingletonShader.h"
#include "Worldinfo.h"
#include "Control.h"
#include "HeightMapGenerator.h"
#include "LandCoverGenerator.h"
Chunk::Chunk()
{

}

Chunk::Chunk(int _x, int _z)
{
	this->loc = new Point3(_x, 0, _z);
	this->centerLoc = new Point3((_x + 0.5)*WorldInfo::chunkSize, 0, (_z + 0.5)*WorldInfo::chunkSize);
	BlockGenerator* gen = new BlockGenerator();
	HeightMapGenerator::heightMapGenerate(this);
	LandCoverGenerator::waterGenerator(this);
	LandCoverGenerator::landCoverGenerator(this);
	LandCoverGenerator::plandGenerator(this);
	LandCoverGenerator::buildGenerator(this);
}


Chunk::~Chunk()
{
}

void Chunk::render()
{
	map<float, Block*> transBlock;
	unordered_map<string, Block*>::iterator iter;
	for (iter = this->blockMap.begin(); iter != blockMap.end(); iter++) {
		if (!iter->second->getBlockData()->opaque) {
			continue;
		}
		Point3* p = iter->second->getBlockData()->getLoc();
		glm::vec3 cameraPos = Control::camera->Position;
		if (glm::length(glm::vec3(p->x, 0, p->z) - glm::vec3(cameraPos.x, 0, cameraPos.z)) > WorldInfo::renderRadius) {
			continue;
		}
		iter->second->stateChange(WorldInfo::projection, WorldInfo::view, glm::vec3(1.0f), glm::vec3(1.0f));
		iter->second->render();
	}
}

void Chunk::setLoc(int x, int z)
{
	this->loc = new Point3(x, 0, z);
}

Point3 * Chunk::getLoc()
{
	return this->loc;
}

Point3 * Chunk::getCenterLoc()
{
	return this->centerLoc;
}

unordered_map<string, Block*>* Chunk::getBlockMapAddress()
{
	return &(this->blockMap);
}

unordered_map<string, Block*> Chunk::getBlockMap()
{
	return this->blockMap;
}

unordered_map<string, Block*> Chunk::getTransparentBlockMap()
{
	return this->transparentBlockMap;
}

unordered_map<string, Block*>* Chunk::getTransparentBlockMapAddress()
{
	return &(this->transparentBlockMap);
}

Block * Chunk::getBlockAt(Point3 point)
{
	string id = BlockUtil::IDBuilder(point.x, point.y, point.z);
	unordered_map<string, Block*>::iterator blockFinder;
	
	blockFinder = this->blockMap.find(id);
	if (blockFinder != this->blockMap.end()) {
		return blockFinder->second;
	}
	//heightMap.erase
	unordered_map<string, Block*>::iterator transBlockFinder;
	transBlockFinder = this->transparentBlockMap.find(id);
	if (transBlockFinder != this->transparentBlockMap.end()) {
		return transBlockFinder->second;
	}
	return nullptr;
}

Block * Chunk::getTopBlockAt(Point2 point)
{
	
	return nullptr;
}

int Chunk::getHeightAt(Point2 point)
{
	map<vector<int>, float>::iterator heightFinder;
	heightFinder = this->heightMap.find(vector<int>{(int) point.x, (int) point.y});
	if (heightFinder != this->heightMap.end()) {
		return heightFinder->second;
	}
	return -25535;
}

void Chunk::setMinHeight(int height)
{
	this->minHeight = height;
}

void Chunk::setMaxHeight(int height)
{
	this->maxHeight = height;
}

int Chunk::getMinHeight()
{
	return this->minHeight;
}

int Chunk::getMaxHeight()
{
	return this->maxHeight;
}

bool Chunk::erase(string id)
{
	unordered_map<string, Block*>::iterator finder;
	finder = this->blockMap.find(id);
	if (finder != blockMap.end()) {
		Point3* p = finder->second->getBlockData()->getLoc();
		blockMap.erase(id);
		

		cout << "³É¹¦" << endl;
		this->heightMap[vector<int>{(int)p->x, (int)p->z}] -= 1;
		
		return true;
	}
	return false;
}

bool Chunk::showBlock(string id)
{
	unordered_map<string, Block*>::iterator finder;
	finder = this->blockMap.find(id);
	if (finder != this->blockMap.end()) {
		finder->second->setVisible(true);
		return true;
	}
	return false;
}

bool Chunk::hidenBlock(string id)
{
	unordered_map<string, Block*>::iterator finder;
	finder = this->blockMap.find(id);
	if (finder != this->blockMap.end()) {
		finder->second->setVisible(false);
		return true;
	}
	return false;
}

bool Chunk::addBlock(int type, Point3 loc)
{
	return false;
}

