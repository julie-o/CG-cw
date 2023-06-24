/*
 * RayTracer.cpp
 *
 */
#include "RayTracer.h"
#include <cmath>
#include <random>
#include <time.h>

namespace rt{


/**
 * Method for tracing a single ray
 *
 * @param ray the ray to trace in the scene
 * @param scene the scene to render
 * @param bounces the number of bounces to consider for raytracing 
 * 
 * @return a Vec3f colour value
 */
Vec3f RayTracer::trace(Ray ray, Scene* scene, int bounces){
	if (bounces<=0){
		return Vec3f(0,0,0);
	} else {
		Hit hit;
		bool foundhit = false;

		for (Shape * S : scene->getShapes()) {
			Hit tryHit = (*S).intersect(ray);
			if((tryHit.hasHit!=NO_HIT && tryHit.distance>hit.epsilon)) {
				if (!foundhit) {
					hit = tryHit;
					foundhit = true;
				} else if (hit.distance>tryHit.distance) {
					hit = tryHit;
				}
			}
		}

		if (hit.hasHit==NO_HIT){
			return scene->getBackground();
		} else {
			Material* m = hit.material;

			Vec3f reflect {Vec3f(0,0,0)};
			Vec3f refract {Vec3f(0,0,0)};
						
			Vec3f diffuse = Vec3f(0,0,0);
			Vec3f specular = Vec3f(0,0,0);


			for (LightSource * L : scene->getLightSources()){
				double shadow = (*L).isShadow(scene->getShapes(),hit.point);

				if (shadow > 0.0005){
					double distance {0};
					Vec3f l {Vec3f()};
					if (((*L).getType()).compare("pointlight")==0){
						distance = ((*L).getPosition() - hit.point).length();
						l = ((*L).getPosition() - hit.point).normalize();
					} else if (((*L).getType()).compare("arealight")==0) {
						auto closestPoint = (*L).closestPointOnPlane(hit.point);
						distance = (closestPoint - hit.point).length();
						l = (closestPoint - hit.point).normalize();
					} else {
						std::cerr<<"Light has been intialised with invalid type"<<std::endl;
			            exit(-1);
					}

					double atten = 4 * pi * pow(distance,2);

					Vec3f diffuseBlinn {Vec3f()}; Vec3f specularBlinn {Vec3f()};
					
					(*m).shade(ray.direction, hit.normal, l, &diffuseBlinn, &specularBlinn);

					diffuse = diffuse + shadow * (diffuseBlinn * (*L).getID() * (1/atten));
					specular = specular + shadow * (specularBlinn * (*L).getIS() * (1/atten));
				}
			}

			if ((*m).getKR()>0){
				Ray reflectRay; 

				Vec3f i = ray.direction;
				Vec3f n = hit.normal;
				Vec3f r = i - 2*(i.dotProduct(n)*n);

				reflectRay.origin = hit.point;
				reflectRay.direction = r;
				reflectRay.raytype = SECONDARY;

				reflect = trace(reflectRay, scene, bounces-1);
			} else {
				reflect = Vec3f(0,0,0);
			}
			if ((*m).getKT()>0){
				double ni = 1.0f;
				double nt = (*m).getEta();
				Vec3f i = -ray.direction; // vector in (but pointing in negative direction)
				Vec3f n = hit.normal;

				auto sroot = 1 - ((ni*ni)/(nt*nt))*(1-pow((i.dotProduct(n)),2));
				if (sroot < 0){
					refract = Vec3f(0,0,0);
				} else {
					auto inparenthesis = (ni/nt)*(i.dotProduct(n)) - sqrtf(sroot);
					auto T = (-(ni/nt)*i) + (inparenthesis)*n;

					Ray refractRay; 
					refractRay.origin = hit.point;
					refractRay.direction = T;
					refractRay.raytype = SECONDARY;
					refract = trace(refractRay, scene, bounces-1);
				} 
			} else {
				refract = Vec3f(0,0,0);
			}

			
			if ((*m).hasTexture()){
				//std::cout << hit.uv << " " << m.getDiffuseColor() << std::endl;
				Vec3f textureColour = hit.material->texture(hit.uv);

				return textureColour*capAtOne((*m).getKD()*diffuse+(*m).getKS()*specular+(*m).getKR()*reflect+(*m).getKT()*refract);
			}
			
			return capAtOne((*m).getKD()*diffuse+(*m).getKS()*specular+(*m).getKR()*reflect+(*m).getKT()*refract); //
		}
	}
}



/**
 * Method for ensuring all floats in a Vec3f are less than or equal to 1
 *
 * @param v Vec3f to cap
 *
 * @return the capped Vec3f
 */
Vec3f RayTracer::capAtOne(Vec3f v){
	Vec3f w = Vec3f(1,1,1);
	if (v.x<1){
		w.x = v.x;
	}
	if (v.y<1){
		w.y = v.y;
	}
	if (v.z<1){
		w.z = v.z;
	}
	return w;
}

/**
 * Performs ray tracing to render a photorealistic scene
 *
 * @param camera the camera viewing the scene
 * @param scene the scene to render, including objects and lightsources
 * @param nbounces the number of bounces to consider for raytracing
 *
 * @return a pixel buffer containing pixel values in linear RGB format
 */
Vec3f* RayTracer::render(Camera* camera, Scene* scene, int nbounces){
	srand(time(NULL));
	
	Vec3f* pixelbuffer=new Vec3f[camera->getWidth()*camera->getHeight()];

	for (int j = 0; j < camera->getHeight(); ++j) {
		for (int i = 0; i < camera->getWidth(); ++i) {

			if (camera->getAperture()==0){
				Ray newRay = camera->initRay(PRIMARY, double(i), double(camera->getHeight()-j-1));
				pixelbuffer[j*camera->getHeight() + i] = trace(newRay, scene, nbounces);
			} else {
				Vec3f sampling = Vec3f(); 
				for (int k = 0; k < camera->getSamples(); k++){
					Ray newRay = camera->initRay(PRIMARY, double(i), double(camera->getHeight()-j-1));
					sampling = sampling + trace(newRay, scene, nbounces);
				}
				Vec3f avgsample = sampling * (1.0/camera->getSamples());
				pixelbuffer[j*camera->getHeight() + i] = avgsample;
			}
			
        }
		//std::cout << j << std::endl;
    }
	//std::cout << "done" << std::endl;
	return pixelbuffer;

}

/**
 * Tonemaps the rendered image (conversion of linear RGB values [0-1] to low dynamic range [0-255]
 *
 * @param pixelbuffer the array of size width*height containing linear RGB pixel values
 *
 * @return the tonemapped image
 */
Vec3f* RayTracer::tonemap(Vec3f* pixelbuffer,Camera* camera){

	std::cout << "tonemap" << std::endl;

	//---------tonemapping function to be filled--------
	for (int i = 0; i < (camera->getWidth()*camera->getHeight()); i++) {
		Vec3f curr = pixelbuffer[i];
		Vec3f tonemap = Vec3f(255 * curr.x,255 * curr.y,255 * curr.z);
		pixelbuffer[i] = tonemap;
	}



	return pixelbuffer;

}

} //namespace rt


