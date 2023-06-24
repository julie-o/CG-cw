/*
 * LightSource.h
 *
 */

#ifndef LIGHTSOURCE_H_
#define LIGHTSOURCE_H_

#include <vector>
#include "rapidjson/document.h"
#include "math/geometry.h"
#include "core/RayHitStructs.h"
#include "core/Shape.h"
#include "shapes/Plane.h"
using namespace rapidjson;

namespace rt{

class LightSource{
public:
    //
	// Constructors
	//
    LightSource(std::string type, Vec3f position, Vec3f is, Vec3f id):type(type), position(position), is(is), id(id){};
    LightSource(std::string type, Plane* plane, int samples, std::string method, Vec3f is, Vec3f id):type(type), plane(plane), samples(samples), method(method), is(is), id(id){};
    
    //
	// Factory function : returns lightsource instance dynamically based on camera specifications
	//
    static LightSource* createLightSource(Value& lightSpecs);
    
    //
	// Destructor
	//
    virtual ~LightSource(){};
    
    //
	// Method for returning the total strength of the shadow produced by this light
	//
    virtual double isShadow(std::vector<Shape*> shapes, Vec3f p)=0;
    
    //
	// Method for returning the strength of the shadow produced by a point light. Can be used
    // either for point lights directly, or by area lights for computing a single sample.
	//
    double pointShadow(std::vector<Shape*> shapes, Vec3f p, Vec3f lightPosition);

    //
	// Getters and Setters
	//
    Vec3f getID() const {
        return id;
    }
    Vec3f getIS() const {
        return is;
    }
    Vec3f getIA() const {
        return ia;
    }
    Vec3f getPosition() const {
        return position;
    }

    Plane* getPlane() const {
        return plane;
    }

    Vec3f getV0() const {
        return (*plane).getV0();
    }

    Vec3f getV1() const {
        return (*plane).getV1();
    }

    Vec3f getV2() const {
        return (*plane).getV2();
    }

    Vec3f getV3() const {
        return (*plane).getV3();
    }

    int getSamples() const {
        return samples;
    }
    std::string getType() const {
        return type;
    }
    std::string getMethod() const {
        return method;
    }

    //
	// Method for returning the closest point on an AreaLight to the input point
	//
    Vec3f closestPointOnPlane(Vec3f point) const {
        return (*plane).closestPointOnPlane(point);
    }
private:
    std::string type;
    std::string method;
    Vec3f position;
    
    Plane* plane;

    int samples;
    Vec3f ia{Vec3f(0,0,0)};
    Vec3f id{Vec3f(0.5,0.5,0.5)};
    Vec3f is{Vec3f(0.5,0.5,0.5)};
};

} //namespace rt



#endif /* LIGHTSOURCE_H_ */
