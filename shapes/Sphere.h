/*
 * Sphere.h
 *
 *
 */

#ifndef SPHERE_H_
#define SPHERE_H_

#include "math/geometry.h"
#include "core/RayHitStructs.h"
#include "core/Shape.h"
#include "core/Material.h"

namespace rt{

class Sphere:public Shape{

public:

	//
	// Constructors
	//
	Sphere(Vec3f center, float radius){
		this->center = center;
		this->radius = radius;

		this->maxBound = boundingBoxMax();
    	this->minBound = boundingBoxMin();
	}

	~Sphere(){};

	Vec2f uv(Vec3f normal,Vec3f point);

	//
	// Functions that need to be implemented, since Sphere is a subclass of Shape
	//
	Hit intersect(Ray ray);
	Vec3f boundingBoxMax();
    Vec3f boundingBoxMin();

	Vec3f getObjectCenter() const {
		return center;
	}

	Vec3f getMaxBound() const {
		return maxBound;
	}
	Vec3f getMinBound() const {
		return minBound;
	}

private:
	Vec3f center;
	float radius;

	Vec3f maxBound;
	Vec3f minBound;

	bool getHit(Ray ray,Hit& hit){
		Vec3f oc = ray.origin - center;
		auto a = (ray.direction).dotProduct(ray.direction);
		auto b = 2.0 * oc.dotProduct(ray.direction);
		auto c = oc.dotProduct(oc) - radius * radius;

		auto discr = b*b - 4*a*c;

		if (discr >= 0){
			auto d1 = (-b - sqrtf(discr))/(2*a);
			auto d2 = (-b + sqrtf(discr))/(2*a);
			if (d2 > hit.epsilon & d1 < hit.epsilon) {
				hit.hasHit = INSIDE;
				hit.distance = d2;
			    hit.point = ray.origin + d2*ray.direction;
				Vec3f temp = (hit.point - center);
    			hit.normal =  Vec3f(temp.x/radius,temp.y/radius,temp.z/radius).normalize();
			} else {
				hit.hasHit = OUTSIDE;
				hit.distance = d1;
				hit.point = ray.origin + d1*ray.direction;
				Vec3f temp = (hit.point - center);
    			hit.normal =  Vec3f(temp.x/radius,temp.y/radius,temp.z/radius).normalize();
			}
			return true;
		} else {
			hit.hasHit = NO_HIT;
			return false;
		}
	}

};



} //namespace rt




#endif /* SPHERE_H_ */
