#pragma once
#include "Ray.h"
#include "HitRecord.h"
class IHittable
{
public:
	virtual ~IHittable() = default;
	virtual bool Hit(const Ray& pRay, double pRayTMin, double pRayTMax, HitRecord& pRecord) const = 0;
};