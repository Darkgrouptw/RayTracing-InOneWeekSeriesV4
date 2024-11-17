#pragma once
#include "glm/glm.hpp"


class Ray
{
public:
	Ray(const glm::dvec3& pOrigin, const glm::dvec3& pDir) : mOrigin(pOrigin), mDirection(pDir) {}

	glm::dvec3 GetOrigin() const { return mOrigin; }
	glm::dvec3 GetDirection() const { return mDirection; }
	glm::dvec3 At(double t) const { return mOrigin + t * mDirection; }

private:
	glm::dvec3 mOrigin;
	glm::dvec3 mDirection;
};

