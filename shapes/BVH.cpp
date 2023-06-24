/*
 * BVH.cpp
 *
 *
 */
#include "BVH.h"
#include "core/Shape.h"
#include "math/geometry.h"
#include <algorithm>
#include <vector>


namespace rt{
    BVH::BVH(std::vector<Shape*> shapes, int maxLeafAmount, int axis){
        this->shapes = shapes;
        this->maxLeafAmount = maxLeafAmount;
        this->maxBound = boundingBoxMax();
        this->minBound = boundingBoxMin();

        if (shapes.size()<=this->maxLeafAmount){
            this->leaf = true;
        } else {
            this->axis = axis;
            int n = std::floor(shapes.size()/2);
            
            if (this->axis==0){
               std::nth_element(shapes.begin(), shapes.begin()+2, shapes.end()
                    , [](Shape* a, Shape* b){return a->getObjectCenter().x < b->getObjectCenter().x;});
            } else if (this->axis==1){
                std::nth_element(shapes.begin(), shapes.begin()+2, shapes.end()
                    , [](Shape* a, Shape* b){return a->getObjectCenter().y < b->getObjectCenter().y;});
            } else {
                std::nth_element(shapes.begin(), shapes.begin()+2, shapes.end()
                    , [](Shape* a, Shape* b){return a->getObjectCenter().z < b->getObjectCenter().z;});
            }

            auto first = shapes.begin() + 0;
            auto last = shapes.begin() + std::floor(shapes.size()/2) + 1;

            std::vector<Shape*> left;
            std::copy(shapes.begin(), shapes.begin()+n, back_inserter(left));
            this->left = new BVH(left, this->maxLeafAmount, (axis + 1)%3);

            std::vector<Shape*> right;
            std::copy(shapes.begin()+n, shapes.end(), back_inserter(right)); 
            this->right = new BVH(right, this->maxLeafAmount, (axis + 1)%3);
            this->leaf = false;
        }
    }

    Vec3f BVH::boundingBoxMax(){
        float x = -std::numeric_limits<double>::infinity();
		float y = -std::numeric_limits<double>::infinity();
		float z = -std::numeric_limits<double>::infinity();
        for (auto shape : shapes) {
    		x = std::max(x,shape->getObjectCenter().x);
    		y = std::max(y,shape->getObjectCenter().y);
	    	z = std::max(z,shape->getObjectCenter().z);
		}
		return Vec3f(x,y,z);
	}

	Vec3f BVH::boundingBoxMin(){
        float x = std::numeric_limits<double>::infinity();
		float y = std::numeric_limits<double>::infinity();
		float z = std::numeric_limits<double>::infinity();
        for (auto shape : shapes) {
    		x = std::min(x,shape->getObjectCenter().x);
    		y = std::min(y,shape->getObjectCenter().y);
	    	z = std::min(z,shape->getObjectCenter().z);
		}
		return Vec3f(x,y,z);
	}

    Hit BVH::intersect(Ray ray){
        Hit hit;
		hit.epsilon = 0.00005;

        if (!intersectBVH(ray)) return hit; // check ir ray hits bounding box 

        if (this->leaf) {
            Hit hit;
		    bool foundhit = false;
            for (Shape* shape : this->shapes) {
                Hit tryHit = (*shape).intersect(ray);
                if((tryHit.hasHit!=NO_HIT && tryHit.distance>hit.epsilon)) {
                    if (!foundhit) {
                        hit = tryHit;
                        foundhit = true;
                    } else if (hit.distance>tryHit.distance) {
                        hit = tryHit;
                    }
                }
		    }
            return hit;
        } else {
            Hit hitLeft = this->left->intersect(ray);
            Hit hitRight = this->right->intersect(ray);

            if (hitLeft.distance < hitRight.distance){
                return hitLeft;
            } else {
                return hitRight;
            }
        }


        hit.hasHit = INSIDE;
		return hit;
    }

    bool BVH::intersectBVH(Ray ray){
        assert(this->maxBound.x>=this->minBound.x);
        assert(this->maxBound.y>=this->minBound.y);
        assert(this->maxBound.z>=this->minBound.z);

		auto u = ray.origin + (ray.direction);
		
        if (ray.direction.x == 0)
            if (ray.origin.x < this->minBound.x || ray.origin.x > this->maxBound.x) return false;
        else {
            float ratio = 1.0 / ray.direction.x;
            float t1 = (this->minBound.x - ray.origin.x) * ratio;
            float t2 = (this->maxBound.x - ray.origin.x) * ratio;

            float tmin = -std::numeric_limits<double>::infinity();
            float tmax = std::numeric_limits<double>::infinity();

            auto txmin = std::min(t1, t2);
            auto txmax = std::max(t1, t2); 

            tmin = std::max(t1, tmin);
            tmax = std::min(t2, tmax);

            if (tmin > txmax || txmax < 0.0) return false;
        }

        if (ray.direction.y == 0)
            if (ray.origin.y < this->minBound.y || ray.origin.y > this->maxBound.y) return false;
        else {
            auto ratio = 1.0 / ray.direction.y;
            float t1 = (this->minBound.y - ray.origin.y) * ratio;
            float t2 = (this->maxBound.y - ray.origin.y) * ratio;

            float tmin = -std::numeric_limits<double>::infinity();
            float tmax = std::numeric_limits<double>::infinity();

            auto tymin = std::min(t1, t2);
            auto tymax = std::max(t1, t2); 

            tmin = std::max(t1, tmin);
            tmax = std::min(t2, tmax);

            if (tmin > tymax || tymax < 0.0) return false;
        }

        if (ray.direction.z == 0)
            if (ray.origin.z < this->minBound.z || ray.origin.z > this->maxBound.z) return false;
        else {

            auto ratio = 1.0 / ray.direction.z;
            float t1 = (this->minBound.z - ray.origin.z) * ratio;
            float t2 = (this->maxBound.z - ray.origin.z) * ratio;

            float tmin = -std::numeric_limits<double>::infinity();
            float tmax = std::numeric_limits<double>::infinity();

            auto tzmin = std::min(t1, t2);
            auto tzmax = std::max(t1, t2); 

            tmin = std::max(t1, tmin);
            tmax = std::min(t2, tmax);

            if (tmin > tzmax || tzmax < 0.0) return false;
        }

		return true;
    }

} //namespace rt


