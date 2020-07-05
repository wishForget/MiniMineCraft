#include "MyScene.h"


MyScene::MyScene(string scenePath, string vsPath, string fsPath)
{
	this->scenePath = scenePath;
	this->vsPath = vsPath;
	this->fsPath = fsPath;
	scale = glm::vec3(0.1f, 0.1f, 0.1f);
	glm::mat4 _scaleMat = glm::mat4(1.0f);
	glm::mat4 _rotateMat = glm::mat4(1.0f);
	glm::mat4 _transMat = glm::mat4(1.0f);
	_scaleMat = glm::scale(_scaleMat, scale);
	_transMat = glm::translate(_transMat, glm::vec3(0.0f, 0.0f, 0.0f));
	model = _scaleMat*_rotateMat*_transMat;
	modelWithoutScale = _rotateMat*_transMat;
	mShader = new Shader(vsPath.c_str(), fsPath.c_str());
}


MyScene::~MyScene()
{
	SAFE_DELETE(mScene);
	SAFE_DELETE(mShader);
}

bool MyScene::init() {
	mShader->use();
	mShader->setMat4("model", model);
	mShader->setInt("material.diffuse", 0);
	mShader->setInt("material.specular", 1);

	mShader->setVec3("light.ambient", 0.2f, 0.2f, 0.2f);
	mShader->setVec3("light.diffuse", 0.5f, 0.5f, 0.5f);
	mShader->setVec3("light.specular", 1.0f, 1.0f, 1.0f);

	mShader->setFloat("material.shininess", 64.0f);

	mScene = new Mesh();
	try {
		mScene->LoadMesh(scenePath);
	}
	catch (...) {
		return false;
	}
	return true;
}

void MyScene::StateChange(
	glm::mat4 projection,
	glm::mat4 view,
	glm::vec3 lightPos,
	glm::vec3 cameraPos) {
	this->projection = projection;
	this->view = view;
	this->lightPos = lightPos;
	this->cameraPos = cameraPos;
}

void MyScene::Render() {
	mShader->use();

	mShader->setVec3("light.position", lightPos);
	mShader->setVec3("viewPos", cameraPos);
	mShader->setMat4("projection", projection);
	mShader->setMat4("view", view);

	mScene->Render();
}

Shader* MyScene::GetShader() {
	return this->mShader;
}
