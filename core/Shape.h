/*
 * Shape.h
 *
 */

#ifndef SHAPE_H_
#define SHAPE_H_

#include "core/RayHitStructs.h"
#include "core/Material.h"
#include "math/geometry.h"

namespace rt{

class Shape{
public:

	//
	// Constructors
	//
	Shape(){};

	//
	// Factory function that returns Shape subclass based on shape specifications
	//
	static Shape* createShape(Value& shapeSpecs);

	//
	// Destructor
	//
	virtual ~Shape(){};

	//
	// Method for checking ray-shape intersection
	//
	virtual Hit intersect(Ray)=0;
	//
	// Method for checking ray-shape intersection
	//
	virtual Vec3f boundingBoxMax()=0;
    //
	// Method for checking ray-shape intersection
	//
	virtual Vec3f boundingBoxMin()=0;

	//
	// Getters
	//
	virtual Vec3f getObjectCenter() const = 0;
	virtual Vec3f getMaxBound() const = 0;
	virtual Vec3f getMinBound() const = 0;

	Material* getMaterial() const {
		return material;
	}

	void setMaterial(Material* m) {
		this->material;
	}

private:
	Material* material;
};


} //namespace rt


#endif /* SHAPE_H_ */
