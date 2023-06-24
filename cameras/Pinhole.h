/*
 * Pinhole.h
 *
 *
 */

#ifndef PINHOLE_H_
#define PINHOLE_H_

#include "core/Camera.h"
#include "math/geometry.h"
#include "core/RayHitStructs.h"

namespace rt{

class Pinhole:public Camera{
public:

	//
	// Constructors
	//
	Pinhole();
	Pinhole(int height, int width, int fov, Vec3f position, Vec3f lookat, Vec3f up);

	//
	//Destructor
	//
	~Pinhole(){};

	//
	// Method for intialising a ray from the camera 
	//
	Ray initRay(RayType type, double x_coord, double y_coord);

	//
	// print function (implementing abstract function of base class)
	//
	void printCamera();
};



} //namespace rt




#endif /* PINHOLE_H_ */
