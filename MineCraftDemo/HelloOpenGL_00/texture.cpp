#include "texture.h"
#include <iostream>
#include "util.h"
#include <stb_image.h>
using namespace std;

Texture::Texture(GLenum TextureTarget, const std::string& FileName)
{
	m_textureTarget = TextureTarget;
	m_fileName = FileName;
	m_pImage = NULL;
}

bool Texture::Load()
{
	m_pImage = stbi_load(m_fileName.c_str(), &width, &height, &channel, 0);
	cout << "texture " << width << " " << height << " " << endl;
	glGenTextures(1, &m_textureObj);
	glBindTexture(m_textureTarget, m_textureObj);
	glTexImage2D(m_textureTarget, 0, GL_RGBA, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, m_pImage);
	glTexParameterf(m_textureTarget, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameterf(m_textureTarget, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

	return m_pImage ? true : false;
}

void Texture::Bind(GLenum TextureUnit)
{
	glActiveTexture(TextureUnit);
	glBindTexture(m_textureTarget, m_textureObj);
}

