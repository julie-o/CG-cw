/*
 * AreaLight.cpp
 *
 *
 */
#include "AreaLight.h"
#include <vector>

namespace rt{

    double AreaLight::isShadow(std::vector<Shape*> shapes, Vec3f p){
        int total {0};
        auto a = this->getV1() - this->getV0();
        auto b = this->getV2() - this->getV0();
        auto c = this->getV3() - this->getV0();
        std::vector<Vec3f> corners {a,b,c};
        auto comp = [&](const Vec3f & p1, const Vec3f & p2){ return p1.length() < p2.length();};
		std::sort(corners.begin(), corners.end(), comp);
        Vec3f u = corners.at(0);
        Vec3f v = corners.at(1);

        if (this->getMethod().compare("random")==0) {
            for (int i = 0; i < this->getSamples(); ++i){
                auto shiftU = (rand()/(double)(RAND_MAX));
                auto shiftV = (rand()/(double)(RAND_MAX));
                auto uCoord = u * shiftU;
                auto vCoord = v * shiftV;
                auto sampleCoord = this->getV0() + uCoord + vCoord;
                total = total + this->pointShadow(shapes,p,sampleCoord);
            }

            return ((double) total)/this->getSamples();
        } else if (this->getMethod().compare("jittered")==0) {
            auto uPixelSize = u.length() / this->getSamples();
            auto vPixelSize = v.length() / this->getSamples();

            for (int i = 0; i < this->getSamples(); ++i){
                for (int j = 0; j < this->getSamples(); ++j){
                    auto shiftU = i*uPixelSize + uPixelSize*((rand()/(double)(RAND_MAX)));
                    auto shiftV = j*vPixelSize + vPixelSize*((rand()/(double)(RAND_MAX)));
                    
                    auto uCoord = u * shiftU;
                    auto vCoord = v * shiftV;
                    auto sampleCoord = this->getV0() + uCoord + vCoord;
                    total = total + this->pointShadow(shapes,p,sampleCoord);
                }
            }
            return ((double) total)/(this->getSamples()*this->getSamples());
        } else {
            std::cerr<<"No sampling method specified for AreaLight."<<std::endl;
            exit(-1);
        }
    }
} //namespace rt
