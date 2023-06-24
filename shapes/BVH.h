/*
 * BVH.h
 *
 *
 */

#ifndef BVH_H_
#define BVH_H_

#include "core/Shape.h"
#include "shapes/Plane.h"
#include "math/geometry.h"
#include <vector>

namespace rt{

class BVH: public Shape{
public:
    BVH(std::vector<Shape*> shapes, int maxLeafAmount, int axis);
    ~BVH(){
        for (auto shape : shapes) {
		    delete shape;
		}
    };
    
	Hit intersect(Ray ray); // traverses tree and returns final intersection
    bool intersectBVH(Ray ray); // checks intersection with this BVH node

    Vec3f boundingBoxMax();
    Vec3f boundingBoxMin();
	
	Vec3f getObjectCenter() const {
		return median;
	}
	Vec3f getMaxBound() const {
		return maxBound;
	}
	Vec3f getMinBound() const {
		return minBound;
	}

    bool isLeaf(){
        return leaf;
    }
    // not relevant for BVH
    Vec2f uv(Vec3f normal,Vec3f point){return Vec2f(0,0);};
private:
    Vec3f median;
    Vec3f maxBound;
    Vec3f minBound;
    
    int axis;

    bool leaf;
    int maxLeafAmount;

    std::vector<Shape*> shapes;
    Shape* left;
    Shape* right;
};



} //namespace rt



#endif /* BVH_H_ */
