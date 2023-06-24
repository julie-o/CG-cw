/*
 * Plane.cpp
 *
 *
 */
#include "Plane.h"


namespace rt{

	Plane::Plane(Vec3f v0,Vec3f v1,Vec3f v2,Vec3f v3){
		this->v0 = v0;
		this->v1 = v1;
		this->v2 = v2;
		this->v3 = v3;

		this->maxBound = boundingBoxMax();
    	this->minBound = boundingBoxMin();
		this->objectCenter = (this->maxBound+this->minBound)*0.5;
	}


	Vec2f Plane::uv(Vec3f normal,Vec3f point){
		auto one = sgn((normal).dotProduct((point-v0).crossProduct(v1-v0)));
		auto two = sgn((normal).dotProduct((point-v1).crossProduct(v2-v1)));
		auto three = sgn((normal).dotProduct((point-v2).crossProduct(v0-v2)));

		Vec3f a = v2;
		Vec3f b = v1;
		Vec3f c = v0;

		if (!(one==two && one==three)) {
			// If the point is not in this triangle, it must be in the other half triangle
			// (as we have already checked in intersect that it is in ONE of them)
			// replace v1 and mirror

			// this implementation assumes points in a plane are defined in order (i.e. v0 oppoiste v2,
			// v1 opposite v3), however there is no restriction on shape or direction defined
			a = v0;
			b = v3;
			c = v2;
		}

		
		Vec3f ab = b - a;
		Vec3f ac = c - a;
		Vec3f ap = point - a;

		float d00 = ab.dotProduct(ab);
		float d01 = ab.dotProduct(ac);
		float d11 = ac.dotProduct(ac);
		float d20 = ap.dotProduct(ab);
		float d21 = ap.dotProduct(ac);
		
		float denom = d00 * d11 - d01 * d01;
		
		auto x = (d11 * d20 - d01 * d21) / denom;
		auto y = (d00 * d21 - d01 * d20) / denom;
		auto z = 1 - x - y;
	
		auto u = x*0 + y*1 + z*0;
		auto v = x*1 + y*1 + z*0;

		return Vec2f(u,v);
	}

	Vec3f Plane::boundingBoxMax(){
		auto x = std::max({this->v0.x,this->v1.x,this->v2.x,this->v3.x});
		auto y = std::max({this->v0.y,this->v1.y,this->v2.y,this->v3.y});
		auto z = std::max({this->v0.z,this->v1.z,this->v2.z,this->v3.z});
		return Vec3f(x,y,z);
	}

	Vec3f Plane::boundingBoxMin(){
		auto x = std::min({this->v0.x,this->v1.x,this->v2.x,this->v3.x});
		auto y = std::min({this->v0.y,this->v1.y,this->v2.y,this->v3.y});
		auto z = std::min({this->v0.z,this->v1.z,this->v2.z,this->v3.z});
		return Vec3f(x,y,z);
	}
} //namespace rt
