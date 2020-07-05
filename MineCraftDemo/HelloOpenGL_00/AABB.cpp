#include "AABB.h"
#include <iostream>
using namespace std;

AABB::AABB(glm::vec3 _min, glm::vec3 _max)
{
	this->_min = _min;
	this->_max = _max;
}

AABB::AABB(glm::vec3 _min, glm::vec3 _max, glm::mat4 modelTrans)
{
	glm::vec4 trans = modelTrans*glm::vec4(_min, 1.0);
	this->_min = glm::vec3(trans.x, trans.y, trans.z);

	glm::vec4 trans1 = modelTrans*glm::vec4(_max, 1.0);
	this->_max = glm::vec3(trans1.x, trans1.y, trans1.z);

}


AABB::~AABB()
{
}

bool AABB::intersects(const AABB& aabb)
{
	return ((_min.x >= aabb._min.x && _min.x <= aabb._max.x) || (aabb._min.x >= _min.x && aabb._min.x <= _max.x)) &&
		((_min.y >= aabb._min.y && _min.y <= aabb._max.y) || (aabb._min.y >= _min.y && aabb._min.y <= _max.y)) &&
		((_min.z >= aabb._min.z && _min.z <= aabb._max.z) || (aabb._min.z >= _min.z && aabb._min.z <= _max.z));

}

bool AABB::containPoint(const glm::vec3 point)
{
	if (point.x < _min.x) return false;
	if (point.y < _min.y) return false;
	if (point.z < _min.z) return false;
	if (point.x > _max.x) return false;
	if (point.y > _max.y) return false;
	if (point.z > _max.z) return false;
	return true;
}

glm::vec3 AABB::getMin(){
	return this->_min;
}


glm::vec3 AABB::getMax() {
	return this->_max;
}