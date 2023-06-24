/*
 * BlinnPhong.cpp
 *
 *
 */

#include "BlinnPhong.h"
#include "math/geometry.h"


namespace rt{
    /**
     * Method for applying BlinnPhong shading to a single point
     *
     * @param raydirection direction of the ray to point
     * @param hitnormal normal to the shape that the point is on
     * @param lightvector vector from point to light 
     * @param diffuse pointer for storing diffuse component
     * @param specular pointer for storing specular component
     * 
     * @return the clamped value
     */
    void BlinnPhong::shade(Vec3f raydirection, Vec3f hitnormal, Vec3f l, Vec3f* diffuse, Vec3f* specular){
        Vec3f n = hitnormal.normalize();

		double d = l.dotProduct(n);
		if (d<0.0005){
			d=0;
		}
					
		Vec3f v = -raydirection;
		Vec3f halfangle = (l+v).normalize();
		double blinnTerm = clamp(n.dotProduct(halfangle),0,1);
		blinnTerm = d != 0.0 ? blinnTerm : 0.0;
		blinnTerm = pow(blinnTerm,4*this->getSpecExp());
   
		*diffuse = (this->getDiffuseColor() * d);
        *specular = (this->getSpecularColor() * blinnTerm);
    }

    /**
     * Method for clamping a double between two values
     *
     * @param d the value to clamp
     * @param min minimum that the returned value can be
     * @param max maximum that the returned value can be
     * 
     * @return the clamped value
     */
    double BlinnPhong::clamp(double d, double min, double max) {
        const double t = d < min ? min : d;
        return t > max ? max : t;
    }

} //namespace rt
