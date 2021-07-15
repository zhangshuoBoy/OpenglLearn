#pragma once
#include <glm/glm.hpp>
//#include <glm/gtc/matrix_transform.hpp>
#include<glm/gtx/rotate_vector.hpp>
class LightSpot
{
public:
	LightSpot(glm::vec3 _position, glm::vec3 _angle, glm::vec3 _color = glm::vec3(1.0f, 1.0f, 1.0f));
	glm::vec3 position;
	glm::vec3 angles;
	glm::vec3 direction = glm::vec3(0, 0, 1.0f);
	glm::vec3 color;
	void UpdateDirection();

	float cosPhyInner = 0.9f;
	float cosPhyOutter = 0.85f;
	float constant;
	float linear;
	float quadratic;
};

