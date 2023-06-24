/*
 * Plane.h
 *
 *
 */

#ifndef PLANE_H_
#define PLANE_H_

#include "core/Shape.h"
#include "core/RayHitStructs.h"
#include <vector>

namespace rt{

class Plane: public Shape{
public:
    Plane(Vec3f v0,Vec3f v1,Vec3f v2,Vec3f v3);
    ~Plane(){};

	Vec2f uv(Vec3f normal,Vec3f point);

	Hit Plane::intersect(Ray ray){

		Hit hit;
		hit.epsilon = 0.00005;
		//-----------to be implemented -------------

		auto u = ray.origin + (ray.direction);

		
		// ACB triangle normal
		hit.normal = ((v2-v0).crossProduct(v1-v0)).normalize();

		auto nr = (hit.normal).dotProduct(ray.direction);
		if (nr==0){
			return hit;
		} else if (nr>0){
			hit.normal = -hit.normal;  // switch to the normal that is on the same side as the ray origin
		}

		//auto t = ((hit.normal).dotProduct(v0-ray.origin))/((hit.normal).dotProduct(ray.direction));
		auto t = (-((-hit.normal).dotProduct(v0))-(hit.normal).dotProduct(ray.origin))/((hit.normal).dotProduct(ray.direction));
		auto rt = ray.origin + (ray.direction)*t;
		hit.point = ray.direction*t + (ray.origin);

		auto one = sgn((hit.normal).dotProduct((hit.point-v0).crossProduct(v1-v0)));
		auto two = sgn((hit.normal).dotProduct((hit.point-v1).crossProduct(v2-v1)));
		auto three = sgn((hit.normal).dotProduct((hit.point-v2).crossProduct(v3-v2)));
		auto four = sgn((hit.normal).dotProduct((hit.point-v3).crossProduct(v0-v3)));

		if (one==two && one==three && one==four) {
			hit.hasHit = OUTSIDE;
			hit.distance = (ray.origin-hit.point).length();
			hit.material = this->getMaterial();
			hit.uv = this->uv(hit.normal,hit.point);
		}

		return hit;
	}

	Vec3f closestPointOnPlane(Vec3f point){
		auto normal = ((v2-v0).crossProduct(v1-v0)).normalize();
		auto d = (normal.x*this->v0.x + normal.y*this->v0.y + normal.z*this->v0.z);
		auto distance = (normal.x*point.x + normal.y*point.y + normal.z*point.z - d) 
							/ (std::sqrtf(normal.x*normal.x + normal.y*normal.y + normal.z*normal.z));
		auto x = (normal.x * d) / (std::sqrtf(normal.x*normal.x + normal.y*normal.y + normal.z*normal.z));
		auto y = (normal.y * d) / (std::sqrtf(normal.x*normal.x + normal.y*normal.y + normal.z*normal.z));
		auto z = (normal.z * d) / (std::sqrtf(normal.x*normal.x + normal.y*normal.y + normal.z*normal.z));

		auto nearestPoint = Vec3f(x,y,z);

		auto one = sgn(normal.dotProduct((nearestPoint-v0).crossProduct(v1-v0)));
		auto two = sgn(normal.dotProduct((nearestPoint-v1).crossProduct(v2-v1)));
		auto three = sgn(normal.dotProduct((nearestPoint-v2).crossProduct(v3-v2)));
		auto four = sgn(normal.dotProduct((nearestPoint-v3).crossProduct(v0-v3)));

		if (!(one==two && one==three && one==four)) {
			/std::vector<Vec3f> v {v0,v1,v2,v3};
			
			auto comp = [&](const Vec3f & p1, const Vec3f & p2){ return (nearestPoint-p1).length() < (nearestPoint-p2).length();};
			std::sort(v.begin(), v.end(), comp);

			auto projOnto = (v.at(0) - v.at(1)).normalize();
			nearestPoint = nearestPoint.dotProduct(projOnto);

			if (((v.at(0) - nearestPoint).length()+(v.at(1) - nearestPoint).length()) - ((v.at(0) - v.at(1)).length()) >= 0.0005f){
				if ((point-v.at(0)).length()<(point-v.at(1)).length()){
					return v.at(0);
				} else {
					return v.at(1);
				}
			}
		}

		return nearestPoint;
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

	Vec3f getV3() const {
        return v3;
    }
private:
    Vec3f v0;
    Vec3f v1;
    Vec3f v2;
    Vec3f v3;

	Vec3f objectCenter {Vec3f(0,0,0)};
	Vec3f maxBound {Vec3f(0,0,0)};
	Vec3f minBound {Vec3f(0,0,0)};

	int sgn(double x) {
		if (x > 0) return 1;
		if (x < 0) return -1;
		return 0;
	}
};



} //namespace rt




#endif /* PLANE_H_ */
