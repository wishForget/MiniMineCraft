#include "Model.h"
#include "util.h"
#include "WorldInfo.h"

Model::Model()
{
}

Model::Model(int pointNum)
{
	this->pointNum = pointNum;
	this->texture = new BlockTexture();
	this->texture->Load("./resources/texture.png");
}


Model::~Model()
{
	glDeleteVertexArrays(1, &VAO);
	glDeleteBuffers(1, &VBO);
}

void Model::init(float _texPos[])
{
	for (int i = 0; i < this->pointNum*2; i++) {
		if (this->pointNum == 36) {
			this->cubeTexPos[i] = _texPos[i];
		}
		else if (this->pointNum == 12) {
			this->crossTexPos[i] = _texPos[i];
		}
		else if (this->pointNum == 6) {
			this->waterTexPos[i] = _texPos[i];
		}
	}
	glGenBuffers(1, &VBO);
	glBindBuffer(GL_ARRAY_BUFFER, VBO); //sizeof(cubeVerPos) + sizeof(this->cubeTexPos)
	if (WorldInfo::useLight) {
		glBufferData(GL_ARRAY_BUFFER, ((3 + 2 + 3) * this->pointNum * sizeof(float)), NULL, GL_STATIC_DRAW);
	}
	else {
		glBufferData(GL_ARRAY_BUFFER, ((3 + 2) * this->pointNum * sizeof(float)), NULL, GL_STATIC_DRAW);
	}
	if (this->pointNum == 36) {
		glBufferSubData(GL_ARRAY_BUFFER, 0, 3 * this->pointNum * sizeof(float), this->cubeVerPos);
		glBufferSubData(GL_ARRAY_BUFFER, 3 * this->pointNum * sizeof(float), 2 * this->pointNum * sizeof(float), this->cubeTexPos);
		if (WorldInfo::useLight) {
			glBufferSubData(GL_ARRAY_BUFFER, (3 + 2) * this->pointNum * sizeof(float), 3 * this->pointNum * sizeof(float), this->cubeANormal);
		}
	}
	else if (this->pointNum == 12) {
		glBufferSubData(GL_ARRAY_BUFFER, 0, 3 * this->pointNum * sizeof(float), this->crossVerPos);
		glBufferSubData(GL_ARRAY_BUFFER, 3 * this->pointNum * sizeof(float), 2 * this->pointNum * sizeof(float), this->crossTexPos);
		if (WorldInfo::useLight) {
			glBufferSubData(GL_ARRAY_BUFFER, (3 + 2) * this->pointNum * sizeof(float), 3 * this->pointNum * sizeof(float), this->crossVeraborm);
		}
	}
	else if (this->pointNum == 6) {
		glBufferSubData(GL_ARRAY_BUFFER, 0, 3 * this->pointNum * sizeof(float), this->waterVerPos);
		glBufferSubData(GL_ARRAY_BUFFER, 3 * this->pointNum * sizeof(float), 2 * this->pointNum * sizeof(float), this->waterTexPos);
		if (WorldInfo::useLight) {
			glBufferSubData(GL_ARRAY_BUFFER, (3 + 2) * this->pointNum * sizeof(float), 3 * this->pointNum * sizeof(float), this->waterVeraborm);
		}
	}
	//sizeof(this->cubeVerPos)
	glGenVertexArrays(1, &VAO);
	glBindVertexArray(VAO);

	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
	glEnableVertexAttribArray(0);
	glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 2 * sizeof(float), (void *)(3 * this->pointNum * sizeof(float)));
	glEnableVertexAttribArray(1);
	if (WorldInfo::useLight) {
		glVertexAttribPointer(2, 3, GL_FLOAT, GL_TRUE, 3 * sizeof(float), (void *)(((3 + 2) * this->pointNum * sizeof(float))));
		glEnableVertexAttribArray(2);
	}
	//glGenBuffers(1, &EBO);

}

void Model::render()
{
	glBindVertexArray(VAO);
	this->texture->Bind(GL_TEXTURE0);
	glDrawArrays(GL_TRIANGLES, 0, this->pointNum);
	glBindVertexArray(0);
}
