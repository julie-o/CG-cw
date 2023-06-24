/*
 * Material.h
 *
 */

#ifndef MATERIAL_H_
#define MATERIAL_H_

#include "rapidjson/document.h"
#include "math/geometry.h"

#include <opencv2/opencv.hpp>

using namespace rapidjson;

namespace rt{

class Material{
public:
  //
	// Constructor
	//
  Material(Value& materialSpecs);
  //
	// Destructor
	//
  virtual ~Material(){};

  //
	// Factory function that returns a material subclass based on material specifications
	//
  static Material* createMaterial(Value& materialSpecs);

  //
	// Method for shading a specific point
	//
  virtual void shade(Vec3f raydirection, Vec3f hitnormal, Vec3f l, Vec3f* diffuse, Vec3f* specular)=0;

  //
	// Method for loading the texture from a file into an array of Vec3f colour values
	//
  void loadTexture();
  //
	// Method for finding the Vec3f colour value on a texture that corresponds to a 
  // particular uv value (uv values are computed in the Shape subclasses).
	//
	Vec3f texture(Vec2f uv);

  //
	// Method for shading a specific point
	//
  //void shade(Hit hit, Ray ray, Vec3f l, Vec3f* diffuse, Vec3f* specular);

  

  double getKA() const {
    return ka;
  }
  double getKD() const {
    return kd;
  }
  double getKS() const {
    return ks;
  }
  double getKR() const {
    return kr;
  }
  double getKT() const {
    return kt;
  }
  double getEta() const {
    return eta;
  }
  int getSpecExp() const {
    return specularexponent;
  }
  Vec3f getDiffuseColor() const {
    return diffusecolor;
  }
  Vec3f getSpecularColor() const {
    return specularcolor;
  }
  Vec3f getAmbientColor() const {
    return ambientcolor;
  }

  bool hasTexture() const {
    return t;
  }
  std::string getTPath() const {
    return tPath;
  }
  int getTWidth() const {
    return tWidth;
  }
  int getTHeight() const {
    return tHeight;
  }
  Vec3f* getTexture() const {
    return loadedTexture;
  }
private:
  double ka{0};
  double ks{0}; //specular reflectivity of the surface
  double kd{0}; //diffuse reflectivity of the surface
  double kr{0}; //Specular reflection
  double kt{0}; //Specular transmissivity
  double eta{1}; //Index of refraction

  int specularexponent{0}; //alpha
  Vec3f diffusecolor {Vec3f(0,0,0)};
  Vec3f specularcolor {Vec3f(0,0,0)};
  Vec3f ambientcolor {Vec3f(0,0,0)};

  bool t = false;
  std::string tPath {""}; // texture
  int tWidth {-1}; // texture
  int tHeight {-1}; // texture

  Vec3f* loadedTexture;
};


} //namespace rt



#endif /* MATERIAL_H_ */
