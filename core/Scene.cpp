/*
 * Scene.cpp
 *
 */
#include "Scene.h"

#include "rapidjson/document.h"
#include "Shape.h"
#include "shapes/BVH.h"

namespace rt{
	/**
	 * Constructor
	 */
	Scene::Scene(){};

	/**
	 * Destructor
	 */
	Scene::~Scene(){
		for (auto light : lightSources) {
		    delete light;
		}
		for (auto shape : shapes) {
		    delete shape;
		}
	};

	/**
	 * Parses json scene object to generate scene to render
	 *
	 * @param scenespecs the json scene specificatioon
	 */
	void Scene::createScene(Value& scenespecs){

		if (scenespecs.HasMember("backgroundcolor")){
			auto r = scenespecs["backgroundcolor"][0].GetFloat();
			auto g = scenespecs["backgroundcolor"][1].GetFloat();
			auto b = scenespecs["backgroundcolor"][2].GetFloat();
			background = Vec3f(r,g,b);
		}

		if (scenespecs.HasMember("lightsources")){
			Value& allLights=scenespecs["lightsources"];
			for (SizeType i = 0; i < allLights.Size(); i++) {
				lightSources.push_back(LightSource::createLightSource(allLights[i]));
			}
		} else {
			std::cerr<<"No light sources specified in scene"<<std::endl;
			exit(-1);
		}

		if (scenespecs.HasMember("shapes")){
			Value& allShapes=scenespecs["shapes"];
			for (SizeType i = 0; i < allShapes.Size(); i++) {
				auto newshape = Shape::createShape(allShapes[i]);
				if (newshape!=0){
					shapes.push_back(newshape);
				}
			}
		} else {
			std::cerr<<"No shapes specified in scene"<<std::endl;
			exit(-1);
		}

		/*
		BVH* root = new BVH(shapes, 1, 0);
		shapes.clear();
		shapes.push_back(root);
		*/
	}

} //namespace rt
