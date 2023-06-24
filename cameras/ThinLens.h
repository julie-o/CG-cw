/*
 * ThinLens.h
 *
 */

#ifndef THINLENS_H_
#define THINLENS_H_

#include "core/Camera.h"
#include "math/geometry.h"
#include "core/RayHitStructs.h"

namespace rt{

class ThinLens:public Camera{
public:

	//
	// Constructors
	//
	ThinLens():Camera(){};
	ThinLens(int height, int width, int fov, Vec3f position, Vec3f lookat, Vec3f up, float aperture, int lens, int samples, std::string method);

	//
	//Destructor
	//
	~ThinLens(){};

	//
	// Method for intialising a ray from the camera 
	//
	Ray initRay(RayType type, double x_coord, double y_coord);

	//
	// print function (implementing abstract function of base class)
	//
	void printCamera();
private:
	Vec3f randomSampler();
};



} //namespace rt




#endif /* THINLENS_H_ */
