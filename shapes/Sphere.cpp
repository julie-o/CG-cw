/*
 * Sphere.cpp
 *
 *
 */
#include "Sphere.h"
#include "core/RayTracer.h"


namespace rt{


	/**
	 * Computes whether a ray hit the specific instance of a sphere shape and returns the hit data
	 *
	 * @param ray cast ray to check for intersection with shape
	 *
	 * @return hit struct containing intersection information
	 *
	 */
	Hit Sphere::intersect(Ray ray){

		Hit hit;

		bool isHit = getHit(ray,hit);

		if (isHit){
			hit.material = this->getMaterial();

			auto r = hit.point - ((hit.point - ray.origin).dotProduct(ray.direction))*ray.direction;

			hit.uv = this->uv(hit.normal,hit.point);
		}
		
		return hit;
	}


	Vec2f Sphere::uv(Vec3f normal, Vec3f point){

		// assumes poles are aligned on the y axis
		auto u = 0.5 + (atan2((-normal).z, (-normal).x) / (2.0f * pi));
		auto v = 0.5 + (asin((-normal).y) / pi);

		return Vec2f(u,v);
	}

	Vec3f Sphere::boundingBoxMax(){
		return this->center+this->radius;
	}

	Vec3f Sphere::boundingBoxMin(){
		return this->center-this->radius;
	}
} //namespace rt


