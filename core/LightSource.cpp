/*
 * LightSource.cpp
 *
 */
#include <iostream>
#include "LightSource.h"
#include "math/geometry.h"

#include "lights/PointLight.h"
#include "lights/AreaLight.h"
#include "core/RayTracer.h"

namespace rt{
    /**
     * Factory function that returns a lightsource subclass based on lightsource specifications
     *
     * @param lightSpecs lightsource specifications json object
     * @return lightsource subclass instance
     *
     */
    LightSource* LightSource::createLightSource(Value& lightSpecs){
        if (!lightSpecs.HasMember("type")){
            std::cerr<<"Light type not specified"<<std::endl;
            exit(-1);
        }

        std::string lightType=lightSpecs["type"].GetString();

        if (lightType.compare("pointlight")==0){
            Vec3f position = Vec3f(lightSpecs["position"][0].GetFloat(),lightSpecs["position"][1].GetFloat(),lightSpecs["position"][2].GetFloat());
            Vec3f is = Vec3f(lightSpecs["is"][0].GetFloat(),lightSpecs["is"][1].GetFloat(),lightSpecs["is"][2].GetFloat());		
            Vec3f id = Vec3f(lightSpecs["id"][0].GetFloat(),lightSpecs["id"][1].GetFloat(),lightSpecs["id"][2].GetFloat());
            return new PointLight("pointlight",position,is,id);
        }else if (lightType.compare("arealight")==0){
            Vec3f v0 = Vec3f(lightSpecs["v0"][0].GetFloat(),lightSpecs["v0"][1].GetFloat(),lightSpecs["v0"][2].GetFloat());
            Vec3f v1 = Vec3f(lightSpecs["v1"][0].GetFloat(),lightSpecs["v1"][1].GetFloat(),lightSpecs["v1"][2].GetFloat());
            Vec3f v2 = Vec3f(lightSpecs["v2"][0].GetFloat(),lightSpecs["v2"][1].GetFloat(),lightSpecs["v2"][2].GetFloat());
            Vec3f v3 = Vec3f(lightSpecs["v3"][0].GetFloat(),lightSpecs["v3"][1].GetFloat(),lightSpecs["v3"][2].GetFloat());            
            Vec3f is = Vec3f(lightSpecs["is"][0].GetFloat(),lightSpecs["is"][1].GetFloat(),lightSpecs["is"][2].GetFloat());		
            Vec3f id = Vec3f(lightSpecs["id"][0].GetFloat(),lightSpecs["id"][1].GetFloat(),lightSpecs["id"][2].GetFloat());
            return new AreaLight("arealight", new Plane(v0,v1,v2,v3), lightSpecs["samples"].GetInt(),lightSpecs["method"].GetString(),is,id);
        } else {
            std::cerr<<"Invalid light source type"<<std::endl;
            exit(-1);
        }
        return 0;

    }

    /**
     * Method for returning the strength of the shadow produced by a point light. Can be used
     * either for point lights directly, or by area lights for computing a single sample.
     * 
     * @param shapes all shapes in the scene
     * @param p hit point to be checked for shadows
     * @param lightPosition position of the light
     * @return 0 if the hit point is shadowed, 1 if it is not
    */
    double LightSource::pointShadow(std::vector<Shape*> shapes, Vec3f p, Vec3f lightPosition){
        Vec3f l = lightPosition - p;
        double d = l.length();

        Ray sray;
        sray.raytype = SHADOW;
        sray.direction = l.normalize();
        sray.origin = p;

        for (Shape* S : shapes) {
            Hit shit = (*S).intersect(sray);
            double d2 = (lightPosition - shit.point).length();
            if ((shit.hasHit==OUTSIDE) && ((d2+shit.epsilon)<d) && !(shit.material->getKT()>0)) {
                return 0;
            }
        }
        return 1;
    }

} //namespace rt

