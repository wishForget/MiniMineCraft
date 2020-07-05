#include "SingletonShader.h"
#include "WorldInfo.h"
#include <iostream>
using namespace std;
Shader * SingletonShader::simpleShader = nullptr;
Shader * SingletonShader::skyDomShader = nullptr;
Shader * SingletonShader::transparentShader = nullptr;
Shader * SingletonShader::otherShader = nullptr;
Shader * SingletonShader::lightShader = nullptr;

Shader * SingletonShader::getSimpleShader()
{
	if (!simpleShader) {
		simpleShader = new Shader("./shader/model_without_light.vs", "./shader/model_without_light.fs");
		simpleShader->use();
		simpleShader->setInt("texture1", 0);
	}
	return simpleShader;
}

Shader * SingletonShader::getSkyDomeShader() {
	if (!skyDomShader) {
		skyDomShader = new Shader("./shader/skyDome.vs", "./shader/skyDome.fs");
	}
	return skyDomShader;
}

Shader * SingletonShader::getLightShader()
{
	if (!lightShader) {
		lightShader = new Shader("./shader/model_load_with_light.vs", "./shader/model_load_with_light.fs");
		lightShader->use();
		lightShader->setVec3("light.ambient", WorldInfo::ambient);
		lightShader->setVec3("light.diffuse", WorldInfo::diffuse);
		lightShader->setVec3("light.specular", WorldInfo::specular);
		lightShader->setVec3("Water.color", WorldInfo::waterColor);
		lightShader->setFloat("Water.maxDist", WorldInfo::waterViewMaxDist);
		lightShader->setFloat("Water.waterLevel", WorldInfo::waterLevel);
		//float maxDist;
		//int waterLevel;
		//vec4 color;
	}
	return lightShader;
}

