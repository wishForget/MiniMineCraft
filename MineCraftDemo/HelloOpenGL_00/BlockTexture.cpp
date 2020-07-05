#include "BlockTexture.h"
#include "BlockUtil.h"
#include <stb_image.h>

BlockTexture::BlockTexture()
{

}


BlockTexture::~BlockTexture()
{
	if (m_textureObj != 0) {
		glDeleteTextures(1, &m_textureObj);
	}
}

bool BlockTexture::Load(string imgPath)
{
	glGenTextures(1, &m_textureObj);
	//绑定到立方体纹理
	glBindTexture(GL_TEXTURE_CUBE_MAP, m_textureObj);

	int width, height, nrChannels;
	unsigned char *data = stbi_load(imgPath.c_str(), &width, &height, &nrChannels, 0);
	if (!data)
	{
		cout << "Cubemap texture failed to load at path: " << endl;// << imgPath << std::endl;
		stbi_image_free(data);
		return 0;
	}
	cout << "channel" << nrChannels << endl;
	GLenum format;
	if (nrChannels == 1)
		format = GL_RED;
	else if (nrChannels == 3)
		format = GL_RGB;
	else if (nrChannels == 4)
		format = GL_RGBA;
	for (unsigned int i = 0; i < 6; i++) {
		glTexImage2D(GL_TEXTURE_2D, 0, format, width, height, 0, format, GL_UNSIGNED_BYTE, data);
		glGenerateMipmap(GL_TEXTURE_2D);
	}
	stbi_image_free(data);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST); //GL_LINEAR);
	return true;
}

void BlockTexture::Bind(GLenum TextureUnit)
{
	glActiveTexture(TextureUnit);
	glBindTexture(GL_TEXTURE_2D, m_textureObj);
	//cout << "texture is " << m_textureObj << endl;
}
