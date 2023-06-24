/*
 * BlinnPhong.h
 *
 *
 */

#ifndef BLINNPHONG_H_
#define BLINNPHONG_H_

#include "core/Material.h"

namespace rt{

class BlinnPhong: public Material{
public:
    //
    // Constructor
    //
    BlinnPhong(Value& materialSpecs):Material(materialSpecs){};
    //
    // Destructor
    //
    ~BlinnPhong(){};

    //
	// Method for shading a specific point
	//
    void shade(Vec3f raydirection, Vec3f hitnormal, Vec3f l, Vec3f* diffuse, Vec3f* specular);

private:
    double clamp(double d, double min, double max);
};

} //namespace rt



#endif /* BLINNPHONG_H_ */
