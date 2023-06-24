/*
 * PointLight.h
 *
 *
 */

#ifndef POINTLIGHT_H_
#define POINTLIGHT_H_

#include "core/LightSource.h"
#include "core/Scene.h"
#include "math/geometry.h"


namespace rt{

class PointLight: public LightSource{
public:
    PointLight(std::string type, Vec3f position, Vec3f is, Vec3f id):LightSource(type,position,is,id){};

    ~PointLight(){};

    double isShadow(std::vector<Shape*> shapes, Vec3f p);
private:
};



} //namespace rt




#endif /* POINTLIGHT_H_ */
