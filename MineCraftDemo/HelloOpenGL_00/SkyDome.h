#pragma once
#include <learnopengl/shader.h>
#include <string.h>
#include <iostream>
#include "mesh.h"
#include "CubemapTexture.h"
using namespace std;

class SkyDome
{
public:
	SkyDome(
		const string& Directory,
		const string& PosXFilename,
		const string& NegXFilename,
		const string& PosYFilename,
		const string& NegYFilename,
		const string& PosZFilename,
		const string& NegZFilename,
		const string& SkyDomeVSName,
		const string& SkyDomeFSName);
	~SkyDome();
	bool init();
	void StateChange(glm::vec3 worldPos, glm::vec3 scale, glm::mat4 projection, glm::mat4 view);
	void Render();
private:
	//string skyDomeVS;
	//string skyDomeFS;
	Shader* mShader = nullptr;
	CubemapTexture* m_pCubemapTex = nullptr;
	Mesh* m_pMesh = nullptr;
	string Directory;
	string PosXFilename;
	string NegXFilename;
	string PosYFilename;
	string NegYFilename;
	string PosZFilename;
	string NegZFilename;
	string SkyDomeVSName;
	string SkyDomeFSName;
};

