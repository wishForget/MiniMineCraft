#include "Section.h"



Section::Section()
{
	//this->blockArray = new blockArray()
}


Section::~Section()
{
}

void Section::render()
{
	for (int x = 0; x < 16; x++) {
		for (int z = 0; z < 16; z++) {
			for (int y = 0; y < 16; y++) {
				if (this->blockArray[x][y][z] != nullptr) {
					this->blockArray[x][y][z]->render();
				}
			}
		}
	}
}

bool Section::erase(int x, int y, int z)
{
	this->blockArray[x][y][z] = nullptr;
	return true;
}

bool Section::showBlock(int x, int y, int z)
{
	if (this->blockArray[x][y][z] != nullptr) {
		this->blockArray[x][y][z]->setVisible(true);
		return true;
	}
	return false;
}
