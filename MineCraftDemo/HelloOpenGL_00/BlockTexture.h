#pragma once
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <string.h>
#include <iostream>
#include "BlockData.h"
using namespace std;

class BlockTexture
{
public:
	BlockTexture();
	~BlockTexture();
	bool Load(string imgPath);
	void Bind(GLenum TextureUnit);
private:
	GLuint m_textureObj;  // Œ∆¿Ì∂‘œÛ
	string path;
};

