#ifndef CSE167_Fire_h
#define CSE167_Fire_h
#include "stdafx.h"
#include "particles.h"
#include <vector>
#include "ComponentNode.h"
#include "GeoNode.h"

class Fire : public GeoNode
{

public:

	float size;
	particles p;
	
	float x_origin=0;
	float y_origin=0;
	float z_origin=0;

	void Fire::initParticles();
	//Initialize particular particle
	void Fire::initParticle(int loop);

	std::vector<ComponentNode> components;

	Fire(float x_pos, float y_pos, float z_pos);
	void LoadGLTextures();
	virtual ~Fire(void);
	virtual void VOnClientUpdate(GameInfoPacket* pData);

	virtual void VOnDraw();
	virtual void VOnUpdate(GameInfoPacket* pData);

};

#endif

