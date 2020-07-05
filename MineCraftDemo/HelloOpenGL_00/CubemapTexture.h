#pragma once
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <string.h>
#include <iostream>
using namespace std;

class CubemapTexture
{
public:
	CubemapTexture(
		const string& Directory,
		const string& PosXFilename,
		const string& NegXFilename,
		const string& PosYFilename,
		const string& NegYFilename,
		const string& PosZFilename,
		const string& NegZFilename);
	~CubemapTexture();
	bool Load();
	void Bind(GLenum TextureUnit);
private:
	string m_fileNames[6];  // 天空盒六个面的贴图
	GLuint m_textureObj;  // 纹理对象
	int width; //天空盒贴图宽度
	int height; //天空盒贴图高度
	int channel; //天空盒贴图通道数
};

