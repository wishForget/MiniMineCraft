#include "CubemapTexture.h"
#include <learnopengl/shader_m.h>
#include "util.h"
//#define STB_IMAGE_IMPLEMENTATION
#include <stb_image.h>

static const GLenum types[6] = { GL_TEXTURE_CUBE_MAP_POSITIVE_X,
GL_TEXTURE_CUBE_MAP_NEGATIVE_X,
GL_TEXTURE_CUBE_MAP_POSITIVE_Y,
GL_TEXTURE_CUBE_MAP_NEGATIVE_Y,
GL_TEXTURE_CUBE_MAP_POSITIVE_Z,
GL_TEXTURE_CUBE_MAP_NEGATIVE_Z 
};
 
CubemapTexture::CubemapTexture(
	const string& Directory,
	const string& PosXFilename,
	const string& NegXFilename,
	const string& PosYFilename,
	const string& NegYFilename,
	const string& PosZFilename,
	const string& NegZFilename)
{
	string::const_iterator it = Directory.end();
	it--;
	string BaseDir = (*it == '/') ? Directory : Directory + "/";

	m_fileNames[0] = BaseDir + PosXFilename;
	m_fileNames[1] = BaseDir + NegXFilename;
	m_fileNames[2] = BaseDir + PosYFilename;
	m_fileNames[3] = BaseDir + NegYFilename;
	m_fileNames[4] = BaseDir + PosZFilename;
	m_fileNames[5] = BaseDir + NegZFilename;

	m_textureObj = 0;
}


CubemapTexture::~CubemapTexture()
{
	if (m_textureObj != 0) {
		glDeleteTextures(1, &m_textureObj);
	}
}

bool CubemapTexture::Load() {
	glGenTextures(1, &m_textureObj);
	//绑定到立方体纹理
	glBindTexture(GL_TEXTURE_CUBE_MAP, m_textureObj);
	for (unsigned int i = 0; i < ARRAY_SIZE_IN_ELEMENTS(types); i++) {
		
		unsigned char *img = stbi_load(m_fileNames[i].c_str(), &width, &height, &channel, 0);
		if (img) {
			glTexImage2D(types[i], 0, GL_RGB, width, height, 0,
				GL_RGB, GL_UNSIGNED_BYTE, img);
			glGenerateMipmap(types[i]);
			stbi_image_free(img);
		}
		else {
			cout << "Cubemap texture failed to load at path: " << m_fileNames[i] << endl;
			stbi_image_free(img);
		}
	}
	glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
	glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
	glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_R, GL_CLAMP_TO_EDGE);
	return true;
}

void CubemapTexture::Bind(GLenum TextureUnit) {
	glActiveTexture(TextureUnit);
	glBindTexture(GL_TEXTURE_CUBE_MAP, m_textureObj);
}
