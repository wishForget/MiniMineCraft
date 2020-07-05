#include "Ray.h"



Ray::Ray(glm::vec3 startPoint, glm::vec3 dir, float stepDis, int stepNum)
{
	this->startPoint = startPoint;
	this->dir = dir*stepDis;
	this->stepNum = stepNum;
	this->curRes = this->startPoint;
	//this->stepDis = stepDis;
}

Ray::Ray(glm::vec3 startPoint, glm::vec3 dir, float stepDis)
{
	this->startPoint = startPoint;
	this->dir = dir*stepDis;
	this->curRes = this->startPoint;
	//this->stepDis = stepDis;
}


Ray::~Ray()
{
}

glm::vec3 Ray::next()
{
	glm::vec3 res = this->curRes;
	this->curRes += this->dir;
	return res;
}

bool Ray::hasNext()
{
	if (this->curStep > this->stepNum) {
		return false;
	}
	return true;
}
