#include "SkyDome.h"
#include <glm/glm.hpp>
#include <glm/vec4.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

SkyDome::SkyDome(
	const string& Directory,
	const string& PosXFilename,
	const string& NegXFilename,
	const string& PosYFilename,
	const string& NegYFilename,
	const string& PosZFilename,
	const string& NegZFilename,
	const string& SkyDomeVSName,
	const string& SkyDomeFSName)
{
	this->Directory = Directory;
	this->PosXFilename = PosXFilename;
	this->NegXFilename = NegXFilename;
	this->PosYFilename = PosYFilename;
	this->NegYFilename = NegYFilename;
	this->PosZFilename = PosZFilename;
	this->NegZFilename = NegZFilename;
	this->SkyDomeVSName = SkyDomeVSName;
	this->SkyDomeFSName = SkyDomeFSName;
	m_pCubemapTex = new CubemapTexture(Directory,
		PosXFilename,
		NegXFilename,
		PosYFilename,
		NegYFilename,
		PosZFilename,
		NegZFilename);
	m_pCubemapTex->Load();
	mShader = new Shader(SkyDomeVSName.c_str(), SkyDomeFSName.c_str());
}


SkyDome::~SkyDome()
{
	SAFE_DELETE(m_pCubemapTex);
	SAFE_DELETE(m_pMesh);
}

bool SkyDome::init() {
	mShader->use();
	mShader->setInt("gCubemapTexture", 0);
	m_pMesh = new Mesh();
	return m_pMesh->LoadMesh("./resources/skyDome/SkyDome.FBX");
}

void SkyDome::StateChange(glm::vec3 worldPos, glm::vec3 scale, glm::mat4 projection, glm::mat4 view) {
	mShader->use();
	glm::mat4 model = glm::mat4(1.0f);
	model = glm::translate(model, worldPos);
	model = glm::scale(model, scale);
	mShader->setMat4("projection", projection);
	mShader->setMat4("view", view);
	mShader->setMat4("model", model);
}

void SkyDome::Render() {
	glDepthFunc(GL_LEQUAL);
	mShader->use();
	m_pCubemapTex->Bind(GL_TEXTURE0);
	m_pMesh->Render();
	glDepthFunc(GL_LESS);
}
