#pragma once
#include "glm/glm.hpp"

using namespace glm;

class Ray
{
public:
	Ray(const vec3& pOrigin, const vec3& pDir) : mOrigin(pOrigin), mDirection(pDir) {}

	vec3 GetOrigin() const { return mOrigin; }
	vec3 GetDirection() const { return mDirection; }
	vec3 At(float t) const { return mOrigin + t * mDirection; }

private:
	vec3 mOrigin;
	vec3 mDirection;
};

