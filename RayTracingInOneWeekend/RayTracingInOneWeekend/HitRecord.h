#pragma once
#include "glm/glm.hpp"

class HitRecord
{
public:
	glm::dvec3 Point;
	glm::dvec3 Normal;
	double T;
};