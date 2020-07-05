#include "BlockGenerator.h"
#include "SingletonModel.h"

BlockGenerator::BlockGenerator()
{
}


BlockGenerator::~BlockGenerator()
{
}

BlockGenerator * BlockGenerator::getInstance()
{
	return nullptr;
}

Block * BlockGenerator::getBlock(int type, Point3* loc, Shader* shader)
{
	Block* block;
	switch (type)
	{
	case 0: 
		block = getGrassBlock(loc, shader);
		break;
	case 1:
		block = getSoilBlock(loc, shader);
		break;
	case 2:
		block = getSandBlock(loc, shader);
		break;
	case 3:
		block = getGlassBlock(loc, shader);
		break;
	case 4:
		block = getSnowBlock(loc, shader);
		break;
	case 5:
		block = getDandelionBlock(loc, shader);
		break;
	case 6:
		block = getSunflowerBlock(loc, shader);
		break;
	case 7:
		block = getWinterJasmineBlock(loc, shader);
		break;
	case 8:
		block = getTulipBlock(loc, shader);
		break;
	case 9:
		block = getRoseBlock(loc, shader);
		break;
	case 10:
		block = getTallGrassBlock(loc, shader);
		break;
	case 11:
		block = getStoneBlock(loc, shader);
		break;
	case 12:
		block = getWaterBlock(loc, shader);
		break;
	default:
		block = getSoilBlock(loc, shader);
		break;
	}
	return block;
}

Block * BlockGenerator::getGrassBlock(Point3* loc, Shader* shader) {
	Block * grassBlock = new Block();
	BlockData* grassBlockData = new BlockData();
	Model* mModel = SingletonModel::getGrassModel();
	grassBlockData->setLoc(loc);
	grassBlock->init(mModel, grassBlockData, shader);
	grassBlockData->collidable = true;
	grassBlockData->opaque = true;
	return grassBlock;
}

Block * BlockGenerator::getSoilBlock(Point3 * loc, Shader* shader)
{
	Block * grassBlock = new Block();
	BlockData* grassBlockData = new BlockData();
	Model* mModel = SingletonModel::getSoilModel();
	grassBlockData->setLoc(loc);
	grassBlock->init(mModel, grassBlockData, shader);
	grassBlockData->collidable = true;
	grassBlockData->opaque = true;
	return grassBlock;
}

Block * BlockGenerator::getSandBlock(Point3 * loc, Shader * shader)
{
	Block * sandBlock = new Block();
	BlockData* sandBlockData = new BlockData();
	Model* mModel = SingletonModel::getSandModel();
	sandBlockData->setLoc(loc);
	sandBlock->init(mModel, sandBlockData, shader);
	sandBlockData->collidable = true;
	sandBlockData->opaque = true;
	return sandBlock;
}

Block * BlockGenerator::getStoneBlock(Point3 * loc, Shader * shader)
{
	Block * stoneBlock = new Block();
	BlockData* stoneBlockData = new BlockData();
	Model* mModel = SingletonModel::getStoneModel();
	stoneBlockData->setLoc(loc);
	stoneBlock->init(mModel, stoneBlockData, shader);
	stoneBlockData->collidable = true;
	stoneBlockData->opaque = true;
	return stoneBlock;
}

Block * BlockGenerator::getGlassBlock(Point3 * loc, Shader * shader)
{
	Block * glassBlock = new Block();
	BlockData* glassBlockData = new BlockData();
	Model* mModel = SingletonModel::getGlassModel();
	glassBlockData->setLoc(loc);
	glassBlock->init(mModel, glassBlockData, shader);
	glassBlockData->collidable = true;
	glassBlockData->opaque = false;
	return glassBlock;
}

Block * BlockGenerator::getDandelionBlock(Point3 * loc, Shader * shader)
{
	Block * flower1Block = new Block();
	flower1Block->type = 555;
	BlockData* flower1BlockData = new BlockData();
	Model* mModel = SingletonModel::getDandelionModel();
	flower1BlockData->setLoc(loc);
	flower1Block->init(mModel, flower1BlockData, shader);
	flower1BlockData->collidable = true;
	flower1BlockData->opaque = false;
	return flower1Block;
}

Block * BlockGenerator::getSnowBlock(Point3 * loc, Shader * shader)
{
	Block * snowBlock = new Block();
	BlockData* snowBlockData = new BlockData();
	Model* mModel = SingletonModel::getSnowModel();
	snowBlockData->setLoc(loc);
	snowBlock->init(mModel, snowBlockData, shader);
	snowBlockData->collidable = true;
	snowBlockData->opaque = true;
	return snowBlock;
}

Block * BlockGenerator::getSunflowerBlock(Point3 * loc, Shader * shader)
{
	Block * flower1Block = new Block();
	flower1Block->type = 555;
	BlockData* flower1BlockData = new BlockData();
	Model* mModel = SingletonModel::getSunflowerModel();
	flower1BlockData->setLoc(loc);
	flower1Block->init(mModel, flower1BlockData, shader);
	flower1BlockData->collidable = true;
	flower1BlockData->opaque = false;
	return flower1Block;
}

Block * BlockGenerator::getWinterJasmineBlock(Point3 * loc, Shader * shader)
{
	Block * flower1Block = new Block();
	flower1Block->type = 555;
	BlockData* flower1BlockData = new BlockData();
	Model* mModel = SingletonModel::getWinterJasmineModel();
	flower1BlockData->setLoc(loc);
	flower1Block->init(mModel, flower1BlockData, shader);
	flower1BlockData->collidable = true;
	flower1BlockData->opaque = false;
	return flower1Block;
}

Block * BlockGenerator::getTulipBlock(Point3 * loc, Shader * shader)
{
	Block * flower1Block = new Block();
	flower1Block->type = 555;
	BlockData* flower1BlockData = new BlockData();
	Model* mModel = SingletonModel::getTulipModel();
	flower1BlockData->setLoc(loc);
	flower1Block->init(mModel, flower1BlockData, shader);
	flower1BlockData->collidable = true;
	flower1BlockData->opaque = false;
	return flower1Block;
}

Block * BlockGenerator::getRoseBlock(Point3 * loc, Shader * shader)
{
	Block * flower1Block = new Block();
	flower1Block->type = 555;
	BlockData* flower1BlockData = new BlockData();
	Model* mModel = SingletonModel::getRoseModel();
	flower1BlockData->setLoc(loc);
	flower1Block->init(mModel, flower1BlockData, shader);
	flower1BlockData->collidable = true;
	flower1BlockData->opaque = false;
	return flower1Block;
}

Block * BlockGenerator::getTallGrassBlock(Point3 * loc, Shader * shader)
{
	Block * tallGrassBlock = new Block();
	tallGrassBlock->type = 555;
	BlockData* tallGrassBlockData = new BlockData();
	Model* mModel = SingletonModel::getTallGrass();
	tallGrassBlockData->setLoc(loc);
	tallGrassBlock->init(mModel, tallGrassBlockData, shader);
	tallGrassBlockData->collidable = true;
	tallGrassBlockData->opaque = false;
	return tallGrassBlock;
}

Block * BlockGenerator::getWaterBlock(Point3 * loc, Shader * shader)
{
	Block * waterBlock = new Block();
	BlockData* waterBlockData = new BlockData();
	waterBlock->type = 12;
	Model* mModel = SingletonModel::getWaterModel();
	waterBlockData->setLoc(loc);
	waterBlock->init(mModel, waterBlockData, shader);
	waterBlockData->collidable = true;
	waterBlockData->opaque = false;
	return waterBlock;
}
