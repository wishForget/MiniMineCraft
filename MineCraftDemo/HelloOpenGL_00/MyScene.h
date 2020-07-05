#pragma once
#include <iostream>
#include <string>
#include <learnopengl/shader.h>
#include "mesh.h"
#include <glm/glm.hpp>
#include <glm/vec4.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <btBulletCollisionCommon.h>
#include <btBulletDynamicsCommon.h>
using namespace std;
class MyScene
{
public:
	MyScene(string scenePath, string vsPath, string fsPath);
	~MyScene();
	bool init();
	void StateChange(
		glm::mat4 projection,
		glm::mat4 view,
		glm::vec3 lightPos,
		glm::vec3 cameraPos);
	void Render();
	Shader* GetShader();
private:
	Shader* mShader = nullptr;
	Mesh* mScene = nullptr;
	glm::vec3 scale;
	glm::mat4 projection;
	glm::mat4 view;
	glm::mat4 model;
	glm::mat4 modelWithoutScale;
	glm::vec3 lightPos;
	glm::vec3 cameraPos;
	string scenePath;
	string vsPath;
	string fsPath;

};

