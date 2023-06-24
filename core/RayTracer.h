/*
 * RayTracer.h
 *
 */
#ifndef RAYTRACER_H_
#define RAYTRACER_H_

#include "math/geometry.h"
#include "core/Camera.h"
#include "core/Scene.h"
#include "lights/AreaLight.h"

namespace rt{


static const double pi = 3.1415926535897932384626433832;

/*
 * Raytracer class declaration
 */
class RayTracer {
public:
	//
	// Constructor
	//
	RayTracer(){};

	//
	// Method for rendering the scene
	//
	static Vec3f* render(Camera* camera, Scene* scene, int nbounces);
	//
	// Method for adjusting the rgb values to be in the 0-255 range instead of 0-1
	//
	static Vec3f* tonemap(Vec3f* pixelbuffer,Camera* camera);
private:
	//
	// Method for tracing a single ray
	//
	static Vec3f trace(Ray ray, Scene* scene, int bounces);
	static Vec3f capAtOne(Vec3f v);
	static double clamp(double d, double min, double max);
};




} //namespace rt



#endif /* RAYTRACER_H_ */

