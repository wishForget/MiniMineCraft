#include "Block.h"
#include "WorldInfo.h"
#include "Control.h"

Block::Block() {
}

Block::Block(int type, Point3* loc)
{
	this->mBlockData->setLoc(loc);
}


Block::~Block()
{
} 

BlockData * Block::getBlockData()
{
	return this->mBlockData;
}

bool Block::init(Model* mModel, BlockData* blockData, Shader* shader)
{
	this->mModel = mModel;
	this->mBlockData = blockData;
	this->mShader = shader;
	Point3* _loc = this->mBlockData->getLoc();
	glm::vec3 loc = glm::vec3(_loc->x, _loc->y, _loc->z);
	this->model = glm::mat4(1.0f);
	this->model = glm::translate(model, loc);
	return true;
}

void Block::stateChange(glm::mat4 projection, glm::mat4 view, glm::vec3 lightPos, glm::vec3 cameraPos)
{
	this->projection = projection;
	this->view = view;
	this->lightPos = lightPos;
	this->cameraPos = cameraPos;
}

void Block::render()
{
	if (visible) {
		mShader->use();
		mShader->setBool("useLight", WorldInfo::useLight);
		mShader->setBool("useFog", WorldInfo::useFog);
		mShader->setBool("ifTransparency", !this->getBlockData()->opaque);
		mShader->setMat4("model", this->model);
		mShader->setMat4("projection", WorldInfo::projection);
		mShader->setMat4("view", WorldInfo::view);

		if (WorldInfo::useLight) {
			mShader->setVec3("light.position", WorldInfo::lightPos);
			mShader->setVec3("viewPos", Control::camera->Position);
			mShader->setInt("material.diffuse", 0);
			mShader->setInt("material.specular", 1);
			mShader->setFloat("material.shininess", 64.0f);
		}
		if (WorldInfo::useFog) {
			mShader->setVec3("viewPos", Control::camera->Position);
			mShader->setFloat("Fog.minDist", WorldInfo::fogMinDist);
			mShader->setFloat("Fog.maxDist", WorldInfo::fogMaxDist);
			mShader->setVec4("Fog.color", WorldInfo::fogColor);
		}
		this->mModel->render();
	}
}

Shader * Block::getShader()
{
	return this->mShader;
}

string Block::getID()
{
	if (ID == "") {
		Point3* loc = this->getBlockData()->getLoc();
		ID = to_string(loc->x) + to_string(loc->y) + to_string(loc->z);
	}
	return ID;
}

int  Block::getBlockX() {
	Point3* loc = this->getBlockData()->getLoc();
	return int(loc->x);
}

int  Block::getBlockY() {
	Point3* loc = this->getBlockData()->getLoc();
	return int(loc->y);
}

int  Block::getBlockZ() {
	Point3* loc = this->getBlockData()->getLoc();
	return int(loc->z);
}

void Block::setID(string id)
{
	this->ID = id;
}

void Block::setVisible(bool visible)
{
	this->visible = visible;
}

glm::mat4 Block::getTransModel()
{
	/*cout << "-------------------" << endl;
	for (int m = 0; m < 4; m++) {
		cout << model[m][0] << " " << model[m][1] << " " << model[m][2] << " " << model[m][3] << endl;
	}
	cout << "===================" << endl;*/
	return this->model;
}
