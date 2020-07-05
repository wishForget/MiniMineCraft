#pragma once
#include "BlockData.h"
#include "Model.h"
#include <learnopengl/shader.h>
#include <glm/glm.hpp>
#include <glm/vec4.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <iostream>
#include <string>
using namespace std;
class Block
{
public:
	Block();
	Block(int type, Point3* loc);
	~Block();
	
	bool init(Model* model, BlockData* blockData, Shader* shader);
	void render();
	void stateChange(
		glm::mat4 projection,
		glm::mat4 view,
		glm::vec3 lightPos,
		glm::vec3 cameraPos);

	void setModel(Model* model);
	void setBlockData(BlockData* blockData);
	void setShader(Shader *shader);
	Model* getModel();
	BlockData* getBlockData();
	Shader* getShader();
	string getID();
	void setID(string id);
	void setVisible(bool visible);
	//我新加的
	int getBlockX();
	int getBlockY();
	int getBlockZ();

	int type = 0;
	glm::mat4 getTransModel();

private:
	BlockData *mBlockData = nullptr;  //属性数据
	Model* mModel = nullptr;
	Shader* mShader = nullptr;
	string ID = "";
	glm::vec3 scale;
	glm::mat4 projection;
	glm::mat4 view;
	glm::mat4 model;
	glm::vec3 lightPos;
	glm::vec3 cameraPos;
	bool visible = true;
};

