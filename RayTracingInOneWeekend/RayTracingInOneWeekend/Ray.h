#pragma once
#include "glm/glm.hpp"


class Ray
{
public:
	Ray(const glm::vec3& pOrigin, const glm::vec3& pDir) : mOrigin(pOrigin), mDirection(pDir) {}

	glm::vec3 GetOrigin() const { return mOrigin; }
	glm::vec3 GetDirection() const { return mDirection; }
	glm::vec3 At(float t) const { return mOrigin + t * mDirection; }

private:
	glm::vec3 mOrigin;
	glm::vec3 mDirection;
};

