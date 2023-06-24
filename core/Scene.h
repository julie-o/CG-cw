/*
 * Scene.h
 *
 */

#ifndef SCENE_H_
#define SCENE_H_

#include <vector>

#include "rapidjson/document.h"
#include "core/LightSource.h"
#include "core/Shape.h"

//using namespace rapidjson;

namespace rt{

class Scene {
public:

	//
	// Constructor and destructor
	//
	Scene();
	~Scene();

	//
	// Method for parsing json to scene
	//
	void createScene(Value& scenespecs);

	//
	// Getters
	//
	std::vector<Shape*> getShapes(){
		return shapes;
	}
	std::vector<LightSource*> getLightSources(){
		return lightSources;
	}
	Vec3f getBackground() const {
		return background;
	}

private:
	std::vector<LightSource*> lightSources;
	std::vector<Shape*> shapes;
	Vec3f background {Vec3f(0,0,0)};

};

} //namespace rt



#endif /* SCENE_H_ */
