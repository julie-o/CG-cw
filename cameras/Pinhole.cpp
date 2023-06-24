/*
 * Pinhole.cpp
 *
 *
 */
#include <iostream>

#include "Pinhole.h"
#include "math/geometry.h"
#include "core/RayTracer.h"


namespace rt{

	//
	// Constructor
	//
	Pinhole::Pinhole(int height, int width, int fov, Vec3f position, Vec3f lookat, Vec3f up):Camera(height, width, fov, position, lookat, up){}


	/**
	 * Prints camera data
	 * this function implements the abstract function of the base Camera class
	 */
	void Pinhole::printCamera(){
		printf("I am a pinhole camera! \n");
		printf("width: %dpx, height: %dpx, fov:%d \n", width, height, fov);
	}

	/**
	 * Method for intialising a ray from the camera 
	 * 
	 * @param type ray type
	 * @param x_coord pixel x coordinate in final image
	 * @param y_coord pixel y coordinate in final image
	 * 
	 * @return returns a ray
	*/
	Ray Pinhole::initRay(RayType type, double x_coord, double y_coord){
		auto x = x_coord / (this->width-1);
		auto y = y_coord / (this->height-1);

		const auto aspect_ratio = this->height/this->width;
		
		auto w = (this->position - this->lookat).normalize();
		auto u = (this->up.crossProduct(w)).normalize();
		auto v = w.crossProduct(u);

		auto viewport_height = 2 * tan((this->fov*pi/180.0)/2);
		auto viewport_width = aspect_ratio * viewport_height;

		auto horizontal = viewport_width * u;
		auto vertical = viewport_height * v;

		Ray ray;
		ray.raytype = type;
		ray.origin = this->position;
		
		// this should have vertical*0.5 as well? 
		auto corner = ray.origin - horizontal*0.5 - w;

		ray.direction = corner + x*horizontal + y*vertical - ray.origin;

		return ray;
	}

} //namespace rt

