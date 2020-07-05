#pragma once
#include <glm/glm.hpp>
#include <glm/vec4.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
class Ray
{
public:
	Ray(glm::vec3 startPoint, glm::vec3 dir, float stepDis, int stepNum);
	Ray(glm::vec3 startPoint, glm::vec3 dir, float stepDis);
	~Ray();
	glm::vec3 next();
	bool hasNext();

private:
	int curStep;
	glm::vec3 startPoint;
	glm::vec3 dir;
	glm::vec3 curRes;
	int stepNum = 100;
};

