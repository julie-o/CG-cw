/*
 * Material.cpp
 *
 */
#include "Material.h"

#include "math/geometry.h"
#include "materials/BlinnPhong.h"

#include <opencv2/opencv.hpp>

namespace rt{
    /**
     * Constructor that returns a Material
     *
     * @param materialSpecs material specifications json object
     *
     * @return material subclass instance
     *
     */
    Material::Material(Value& materialSpecs){
        if (materialSpecs.HasMember("diffusecolor")){
            auto r = materialSpecs["diffusecolor"][0].GetFloat();
            auto g = materialSpecs["diffusecolor"][1].GetFloat();
            auto b = materialSpecs["diffusecolor"][2].GetFloat();

            this->diffusecolor = Vec3f(r,g,b);
        }

        if (materialSpecs.HasMember("specularcolor")){
            auto rs = materialSpecs["specularcolor"][0].GetFloat();
            auto gs = materialSpecs["specularcolor"][1].GetFloat();
            auto bs = materialSpecs["specularcolor"][2].GetFloat();
            this->specularcolor = Vec3f(rs,gs,bs);
        }
        
        this->ks = materialSpecs["ks"].GetFloat();
        this->kd = materialSpecs["kd"].GetFloat();

        if (materialSpecs.HasMember("kr")){
            this->kr = materialSpecs["kr"].GetFloat();
        }

        if (materialSpecs.HasMember("kt")){
            this->kt = materialSpecs["kt"].GetFloat();
            if (materialSpecs.HasMember("eta")){
                this->eta = materialSpecs["eta"].GetFloat();
            }
        }
        
        if (materialSpecs.HasMember("specularexponent")){
            this->specularexponent = materialSpecs["specularexponent"].GetInt();
        }
        
        
        if (materialSpecs.HasMember("tPath")){
            this->t = true;
            this->tPath = materialSpecs["tPath"].GetString();

            if (materialSpecs.HasMember("tWidth")){
                this->tWidth = materialSpecs["tWidth"].GetInt();
            }
            if (materialSpecs.HasMember("tHeight")){
                this->tHeight = materialSpecs["tHeight"].GetInt();
            }
            this->loadTexture();
        }
    }

    /**
     * Factory function that returns a material subclass based on material specifications
     *
     * @param materialSpecs camera specifications json object
     *
     * @return material subclass instance
     *
     */
    Material* Material::createMaterial(Value& materialSpecs){
        return new BlinnPhong(materialSpecs);
    }

    /**
     * Method for loading the texture from a file into an array of Vec3f colour values. Uses
     * the stored class variables.
    */
    void Material::loadTexture(){
        if(tPath==""){
            return;
        }

        std::string path = tPath;
        
        cv::Mat img = cv::imread(path, cv::IMREAD_COLOR);

        cv::Mat r_img;
        if (tWidth>0 && tHeight>0){
            cv::resize(img, r_img, cv::Size(tWidth, tHeight), cv::INTER_LINEAR);
        } else {
            r_img=img;
        }

        loadedTexture = new Vec3f[tWidth*tHeight];

        for( int j = 0; j < tHeight; ++j){
            for( int i = 0; i < tWidth; ++i ) {

                // Note the BGR order in the opencv images 
                auto b = r_img.at<cv::Vec3b>(j,i)[0]/ 255.0;
                auto g = r_img.at<cv::Vec3b>(j,i)[1]/ 255.0;
                auto r = r_img.at<cv::Vec3b>(j,i)[2]/ 255.0;

                loadedTexture[j*tHeight + i] = Vec3f(r,g,b);

            }
        }
        return;
    }

    /**
     * Method for finding the Vec3f colour value of a specific 2d uv point on the  texture.
     * 
     * @param uv A vector of 2d uv coordinates that specify a point on the texture
     * @return a Vec3f colour value
    */
    Vec3f Material::texture(Vec2f uv){
        int i = uv.x * (this->tWidth - 1);
        int j = uv.y * (this->tHeight - 1);  
        
        Vec3f textureColour = loadedTexture[j*tHeight + i];


	    return textureColour;
    }

} //namespace rt


