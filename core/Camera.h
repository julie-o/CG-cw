/*
 * Camera.h
 *
 */

#ifndef CAMERA_H_
#define CAMERA_H_

#include "rapidjson/document.h"
#include "math/geometry.h"
#include "core/RayHitStructs.h"

using namespace rapidjson;

namespace rt{

class Camera{
public:

	//
	// Constructors
	//
	Camera(){};
	Camera(int height, int width, int fov, Vec3f position, Vec3f lookat, Vec3f up)
		:height(height), width(width), fov(fov), position(position), lookat(lookat), up(up){};
	Camera(int height, int width, int fov, Vec3f position, Vec3f lookat, Vec3f up, float aperture, int lens, int samples, std::string method)
		:height(height), width(width), fov(fov), position(position), lookat(lookat), up(up), aperture(aperture),  lens(lens), samples(samples), method(method){};

	//
	// Destructor
	//
	virtual ~Camera();


	//
	// Factory function : returns camera instance dynamically based on camera specifications
	//
	static Camera* createCamera(Value& cameraSpecs);

	//
	// Method for intialising a ray from the camera 
	//
	virtual Ray initRay(RayType type, double x_coord, double y_coord)=0;

	//
	// print function (to be implemented by the subclasses )
	//
	virtual void printCamera()=0;

	//
	// Getters and Setters
	//
	int getHeight() const {
		return height;
	}

	void setHeight(int height) {
		this->height = height;
	}

	int getWidth() const {
		return width;
	}

	void setWidth(int width) {
		this->width = width;
	}

	int getFOV() const {
		return fov;
	}
	
	Vec3f getPosition() const {
		return position;
	}

	Vec3f getLookat() const {
		return lookat;
	}

	Vec3f getUp() const {
		return up;
	}

	float getAperture() const {
		return aperture;
	}

	int getLens() const {
		return lens;
	}

	int getSamples() const {
		return samples;
	}

	std::string getMethod() const {
		return method;
	}
protected:
	int height;
	int width; 
	int fov;
	Vec3f position;
    Vec3f lookat;
    Vec3f up;

	float aperture {0};
	int samples {1};
	int lens {50};
	std::string method;
};

} //namespace rt



#endif /* CAMERA_H_ */
