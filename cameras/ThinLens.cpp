/*
 * ThinLens.cpp
 *
 *
 */
#include <iostream>


#include "ThinLens.h"
#include "math/geometry.h"
#include "core/RayTracer.h"


namespace rt{

	//
	// Constructor
	//
	ThinLens::ThinLens(int height, int width, int fov, Vec3f position, Vec3f lookat, Vec3f up, float aperture, int lens, int samples, std::string method)
					:Camera(height, width, fov, position, lookat, up, aperture, lens, samples, method){}

	/**
	 * Prints camera data
	 * this function implements the abstract function of the base Camera class
	 */
	void ThinLens::printCamera(){
		printf("I am a thin lens camera! \n");
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
	Ray ThinLens::initRay(RayType type, double x_coord, double y_coord){
		Vec3f randomSample = randomSampler();

		auto x = x_coord / (this->width-1);
		auto y = y_coord / (this->height-1);

		auto a = x / this->samples;
		auto b = y / this->samples;

		const auto aspect_ratio = this->width/this->height;
		auto focusdistance = (position-lookat).length();
		
		auto w = (this->position - this->lookat).normalize();
		auto u = (this->up.crossProduct(w)).normalize();
		auto v = w.crossProduct(u);

		auto apertureDia = lens/aperture;
		Vec3f ofs = 0.5 * apertureDia * randomSample;
        Vec3f offset = u * ofs.x + v * ofs.y;
	

		auto viewport_height = 2 * tan((this->fov*pi/180.0)/2);
		auto viewport_width = aspect_ratio * viewport_height;

		auto horizontal = focusdistance * viewport_width * u;
		auto vertical = focusdistance * viewport_height * v;

		Ray ray;
		ray.raytype = type;

		ray.origin = this->position + offset;

		auto corner = (this->position - horizontal*0.5 - focusdistance*w);
		ray.direction = corner + x*horizontal + y*vertical - ray.origin;

		return ray;
	}


	// choose a random point in a circle around the pinhole (values range between -1 and 1)
	Vec3f ThinLens::randomSampler() {
		Vec3f p = Vec3f(2, 2, 2);
		while ((p.length()*p.length()) >= 1) {
			auto randomX = (rand()/(double)(RAND_MAX))*2-1;
			auto randomY = (rand()/(double)(RAND_MAX))*2-1;
			p = Vec3f(randomX, randomY,0);
		}
		return p;
	}
} //namespace rt
