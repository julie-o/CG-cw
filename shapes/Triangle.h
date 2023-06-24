/*
 * Triangle.h
 *
 *
 */

#ifndef TRIANGLE_H_
#define TRIANGLE_H_

#include "math/geometry.h"
#include "core/RayHitStructs.h"
#include "core/Shape.h"
#include "core/Material.h"

namespace rt{

class Triangle: public Shape{
public:
    Triangle(Vec3f v0,Vec3f v1,Vec3f v2);
    ~Triangle(){};

	Vec2f uv(Vec3f normal,Vec3f point);

	Hit Triangle::intersect(Ray ray){

		Hit hit;
		hit.epsilon = 0.00005;
		
		// ACB triangle normal
		hit.normal = (((v2-v0).crossProduct(v1-v0)).normalize());

		auto nr = (hit.normal).dotProduct(ray.direction);
		if (nr==0){
			return hit;
		} else if (nr>0){
			hit.normal = -hit.normal;  // switch to the normal that is on the same side as the ray origin
		}

		auto t = (-((-hit.normal).dotProduct(v0))-(hit.normal).dotProduct(ray.origin)) / ((hit.normal).dotProduct(ray.direction));
		auto rt = ray.origin + (ray.direction)*t;
		hit.point = ray.direction*t + (ray.origin);

		auto one = sgn((hit.normal).dotProduct((hit.point-v0).crossProduct(v1-v0)));
		auto two = sgn((hit.normal).dotProduct((hit.point-v1).crossProduct(v2-v1)));
		auto three = sgn((hit.normal).dotProduct((hit.point-v2).crossProduct(v0-v2)));

		if (one==two && one==three) {
			hit.hasHit = OUTSIDE;
			hit.distance = (ray.origin-hit.point).length();
			hit.material = this->getMaterial();
			hit.uv = this->uv(hit.normal,hit.point);
		}

		return hit;

	}
	Vec3f boundingBoxMax();
    Vec3f boundingBoxMin();
	
	Vec3f getObjectCenter() const {
		return objectCenter;
	}
	Vec3f getMaxBound() const {
		return maxBound;
	}
	Vec3f getMinBound() const {
		return minBound;
	}

	Vec3f getV0() const {
		return v0;
	}

	Vec3f getV1() const {
		return v1;
	}

	Vec3f getV2() const {
		return v2;
	}

private:
    Vec3f v0;
    Vec3f v1;
    Vec3f v2;

	Vec3f objectCenter;
	Vec3f maxBound;
	Vec3f minBound;
	
	int sgn(double x) {
		if (x > 0) return 1;
		if (x < 0) return -1;
		return 0;
	}
};



} //namespace rt




#endif /* TRIANGLE_H_ */
