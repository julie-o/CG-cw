/*
 * RayHitStructs.h
 */

#ifndef CORE_RAYHITSTRUCTS_H_
#define CORE_RAYHITSTRUCTS_H_

#include "math/geometry.h"
#include "core/Material.h"

namespace rt{

// type of ray
enum RayType {PRIMARY, SECONDARY, SHADOW};

// type of hit (whether the ray has hit a shape and if it's inside or outside)
enum HasHit {NO_HIT, INSIDE, OUTSIDE};

/*
 * Ray structure definition
 */
struct Ray{
	RayType raytype;
	Vec3f origin;
	Vec3f direction;
};

/*
 * Hit structure definition
 */
struct Hit{
	// hit point
	Vec3f point;
	// normal to the shape at the hit point  
	Vec3f normal;
	// distance to the hit point from origin of ray that produced the hit
	double distance {std::numeric_limits<double>::infinity()};
	// type of hit
	HasHit hasHit {NO_HIT};

	// material of the shape at the hit point
	Material* material;
	// uv coordinates of the hit on the shape
	Vec2f uv {Vec2f(-1,-1)};

	// parameter for rounding 
	double epsilon {0.00005};
};

}


#endif /* CORE_RAYHITSTRUCTS_H_ */
