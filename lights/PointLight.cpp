/*
 * PointLight.cpp
 *
 *
 */
#include "PointLight.h"
#include "core/RayTracer.h"
#include "core/Scene.h"

namespace rt{

    double PointLight::isShadow(std::vector<Shape*> shapes, Vec3f p){
        return this->pointShadow(shapes,p,this->getPosition());
    }
} //namespace rt
