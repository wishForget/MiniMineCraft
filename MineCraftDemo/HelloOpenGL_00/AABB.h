#pragma once
#include <glm/glm.hpp>
#include <glm/vec4.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
class AABB
{
public:
	AABB(glm::vec3 _min, glm::vec3 _max);
	AABB(glm::vec3 _min, glm::vec3 _max, glm::mat4 modelTrans);
	~AABB();
	bool AABB::containPoint(const glm::vec3 point);
	bool AABB::intersects(const AABB& aabb);
	glm::vec3 getMin();
	glm::vec3 getMax();
private:
	glm::vec3 _min;
	glm::vec3 _max;
};

