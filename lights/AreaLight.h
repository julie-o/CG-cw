/*
 * AreaLight.h
 *
 *
 */

#ifndef AREALIGHT_H_
#define AREALIGHT_H_

#include "core/LightSource.h"
#include "core/Shape.h"
#include "shapes/Plane.h"
#include "math/geometry.h"
#include <vector>

namespace rt{

class AreaLight:public LightSource{
public:
    AreaLight(std::string type, Plane* plane, int samples, std::string method, Vec3f is, Vec3f id)
            :LightSource(type, plane, samples, method, is, id){};
    ~AreaLight(){};
    double isShadow(std::vector<Shape*> shapes, Vec3f p);
};



} //namespace rt




#endif /* AREALIGHT_H_ */
