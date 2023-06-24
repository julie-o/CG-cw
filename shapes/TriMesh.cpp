/*
 * TriMesh.cpp
 *
 *
 */
#include "TriMesh.h"


namespace rt{

    Vec2f TriMesh::uv(int index, int f_count, Vec2f uv){
        auto u = uv.x;
        auto v = uv.y;

        if (index%2==1){
            u = (1-u);
            v = (1-v);
        }

        auto cell = (ceil((f_count)/2)+1);
        auto ind = (floor(index/2))/cell;

        u = ind + u/cell;
        
        return Vec2f(u,v);
    }

    Vec3f TriMesh::boundingBoxMax(){
        Triangle* face = triangles.at(0);
		Vec3f v0 = face->getV0();
        Vec3f v1 = face->getV1();
        Vec3f v2 = face->getV2();
        Vec3f maxBound = Vec3f(std::max({v0.x,v1.x,v2.x}),std::max({v0.y,v1.y,v2.y}),std::max({v0.z,v1.z,v2.z}));

        for (int i = 1; i < this->triangles.size(); i++){
			Triangle* face = triangles.at(i);
			Vec3f v0 = face->getV0();
            Vec3f v1 = face->getV1();
            Vec3f v2 = face->getV2();

            auto x = std::max({v0.x,v1.x,v2.x});
            auto y = std::max({v0.y,v1.y,v2.y});
            auto z = std::max({v0.z,v1.z,v2.z});

            maxBound = Vec3f(std::max(maxBound.x,x),std::max(maxBound.y,y),std::max(maxBound.z,z));
		}
		return maxBound;
	}

	Vec3f TriMesh::boundingBoxMin(){
        Triangle* face = triangles.at(0);
		Vec3f v0 = face->getV0();
        Vec3f v1 = face->getV1();
        Vec3f v2 = face->getV2();
        Vec3f minBound = Vec3f(std::min({v0.x,v1.x,v2.x}),std::min({v0.y,v1.y,v2.y}),std::min({v0.z,v1.z,v2.z}));

        for (int i = 1; i < this->triangles.size(); i++){
			Triangle* face = triangles.at(i);
			Vec3f v0 = face->getV0();
            Vec3f v1 = face->getV1();
            Vec3f v2 = face->getV2();

            auto x = std::min({v0.x,v1.x,v2.x});
            auto y = std::min({v0.y,v1.y,v2.y});
            auto z = std::min({v0.z,v1.z,v2.z});

            minBound = Vec3f(std::min(minBound.x,x),std::min(minBound.y,y),std::min(minBound.z,z));
		}
		return minBound;
	}

} //namespace rt


