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
	float startTime;
	float x_origin = 0;
	float y_origin = 0;
	float z_origin = 0;
	float lifeTime = 10;
	int mode;
	int color;
	void Fire::initParticles();
	//Initialize particular particle
	void Fire::initParticle(int loop);

	// Fire column
	void Fire::DoFire();
	// Some sparks
	void Fire::DoSparks();
	// Moneyzone effect
	void Fire::DoMoneyZone();

	std::vector<ComponentNode> components;

	Fire(float x_pos, float y_pos, float z_pos, int mode, int color);
	void LoadGLTextures();
	virtual ~Fire(void);
	virtual void VOnClientUpdate(GameInfoPacket* pData);

	virtual void VOnDraw();
	virtual void VOnUpdate(GameInfoPacket* pData);
};

#endif

