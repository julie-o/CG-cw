/*
 * TriMesh.h
 *
 *
 */

#ifndef TRIMESH_H_
#define TRIMESH_H_

#include "core/Shape.h"
#include "shapes/Triangle.h"

namespace rt{

class TriMesh: public Shape{
public:
	TriMesh(Vec3f* vertices,Vec3i* faces,int count){
		this->f_count=count;
		triangles.begin();
		for (int i = 0; i < count; i++){
			auto face = faces[i];
			auto x = vertices[face.x];
			auto y = vertices[face.y];
			auto z = vertices[face.z];
			Triangle* t = new Triangle(x,y,z);
			triangles.push_back(t);
		}

		this->maxBound = boundingBoxMax();
    	this->minBound = boundingBoxMin();
		this->objectCenter = (this->maxBound+this->minBound)*0.5;
	}
    ~TriMesh(){
		for (auto triangle : triangles) {
		    delete triangle;
		}
	};

	Vec2f uv(int index,int f_count,Vec2f uv);

	Hit TriMesh::intersect(Ray ray){
		Hit hit;
		bool foundHit {false};
		int ind {-1};
		for (int i = 0; i < triangles.size(); i++){
			Triangle* face = triangles.at(i);
			Hit nextHit = face->intersect(ray);
			if((nextHit.hasHit==OUTSIDE && nextHit.distance>hit.epsilon)) {
				if (!foundHit) {
					hit = nextHit;
					foundHit = true;
					ind = i;
				} else if (hit.distance>nextHit.distance) {
					hit = nextHit;
					ind = i;
				}
			}
		}
		if (hit.hasHit==OUTSIDE){
			hit.normal = hit.normal;
			hit.material = this->getMaterial();
			hit.uv = this->uv(ind,f_count,hit.uv);
		}

		return hit;
	}

	Vec3f boundingBoxMax();
    Vec3f boundingBoxMin();

	
	Vec3f getObjectCenter() const {
		return objectCenter;
	}

	Vec3f getMaxBound() const {
		return maxBound;
	}
	Vec3f getMinBound() const {
		return minBound;
	}
	
private:
	Vec3f objectCenter;
	Vec3f maxBound;
	Vec3f minBound;
	
	int f_count {0};
	std::vector<Triangle*> triangles;
};



} //namespace rt




#endif /* TRIMESH_H_ */
