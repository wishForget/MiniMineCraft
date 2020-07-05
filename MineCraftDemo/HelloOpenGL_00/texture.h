#pragma once
#include <string>
#include <glad/glad.h>
#include <GLFW/glfw3.h>
//#include <stb_image.h>

class Texture
{
public:
	Texture(GLenum TextureTarget, const std::string& FileName);

	bool Load();

	void Bind(GLenum TextureUnit);

private:
	std::string m_fileName;
	GLenum m_textureTarget;
	GLuint m_textureObj;
	int width;
	int height;
	int channel;
	unsigned char * m_pImage;
};

