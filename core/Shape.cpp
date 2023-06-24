/*
 * Shape.cpp
 *
 */
#include "Shape.h"

#include "shapes/Sphere.h"
#include "shapes/Triangle.h"
#include "shapes/TriMesh.h"
#include "shapes/Plane.h"
#include "core/Material.h"
#include "core/RayHitStructs.h"

namespace rt{
    /**
	 * Factory function that returns Shape subclass based on shape specifications
	 *
	 * @param shapeSpecs shape json object
	 *
	 * @return shape subclass instance
	 *
	 */
    Shape* Shape::createShape(Value& shapeSpecs){


        if (!shapeSpecs.HasMember("type")){
            std::cerr<<"Shape type not specified"<<std::endl;
            exit(-1);
        }

        std::string shapeType=shapeSpecs["type"].GetString();

        if (shapeType.compare("sphere")==0){
            Vec3f center(shapeSpecs["center"][0].GetFloat(),shapeSpecs["center"][1].GetFloat(),shapeSpecs["center"][2].GetFloat());
            float radius = shapeSpecs["radius"].GetFloat();
            Material* material = Material::createMaterial(shapeSpecs["material"]);
            Sphere* s = new Sphere(center,radius);
            s->material=material;
			return s;
		} else if (shapeType.compare("plane")==0) {
            Vec3f v0 = Vec3f(shapeSpecs["v0"][0].GetFloat(),shapeSpecs["v0"][1].GetFloat(),shapeSpecs["v0"][2].GetFloat());
            Vec3f v1 = Vec3f(shapeSpecs["v1"][0].GetFloat(),shapeSpecs["v1"][1].GetFloat(),shapeSpecs["v1"][2].GetFloat());
            Vec3f v2 = Vec3f(shapeSpecs["v2"][0].GetFloat(),shapeSpecs["v2"][1].GetFloat(),shapeSpecs["v2"][2].GetFloat());
            Vec3f v3  = Vec3f(shapeSpecs["v3"][0].GetFloat(),shapeSpecs["v3"][1].GetFloat(),shapeSpecs["v3"][2].GetFloat());
            Material* material = Material::createMaterial(shapeSpecs["material"]);
            Plane* s = new Plane(v0,v1,v2,v3);
            s->material=material;
			return s;
		} else if (shapeType.compare("triangle")==0) {
            Vec3f v0 = Vec3f(shapeSpecs["v0"][0].GetFloat(),shapeSpecs["v0"][1].GetFloat(),shapeSpecs["v0"][2].GetFloat());
            Vec3f v1 = Vec3f(shapeSpecs["v1"][0].GetFloat(),shapeSpecs["v1"][1].GetFloat(),shapeSpecs["v1"][2].GetFloat());
            Vec3f v2 = Vec3f(shapeSpecs["v2"][0].GetFloat(),shapeSpecs["v2"][1].GetFloat(),shapeSpecs["v2"][2].GetFloat());
            Material* material = Material::createMaterial(shapeSpecs["material"]);
            Triangle* s = new Triangle(v0,v1,v2);
            s->material=material;
			return s;
		} else if (shapeType.compare("trimesh")==0) {
            Value& v=shapeSpecs["vertices"];
            Vec3f* vertices = new Vec3f[v.Size()];
            for (SizeType i = 0; i < v.Size(); i++){
                if (v[i].GetArray().Size() != 3){
                    std::cerr << "Vertex " << i << " is invalid"<< std::endl;
                    exit(-1);
                }
                Value& arr = v[i];
                vertices[i] = Vec3f(arr[0].GetFloat(),arr[1].GetFloat(),arr[2].GetFloat());
            }

            Value& f=shapeSpecs["faces"];
            Vec3i* faces = new Vec3i[f.Size()];
            for (SizeType i = 0; i < f.Size(); i++){
                if (f[i].GetArray().Size() != 3 ){
                    std::cerr << "Face " << i << " is invalid" << std::endl;
                    exit(-1);
                }
                auto arr = f[i].GetArray();
                faces[i] = Vec3i(arr[0].GetInt(),arr[1].GetInt(),arr[2].GetInt());
            }

            Material* material = Material::createMaterial(shapeSpecs["material"]);
            TriMesh* s = new TriMesh(vertices,faces,f.Size());
            s->material=material;
			return s;
		} else {
			std::cerr<<"Unsupported shape type: "<< shapeType << ". Shape skipped."<<std::endl;
		}

        return 0;

    }
    
} //namespace rt

