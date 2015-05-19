#ifndef CSE167_Explosion_h
#define CSE167_Explosion_h
#include "stdafx.h"
#include "particles.h"
#include <vector>
#include "ComponentNode.h"
#include "GeoNode.h"

#define NUM_PARTICLES 5000
struct particleData{
	float position[3];
	float speed[3];
	float color[3];
};
typedef struct particleData particleData;

class Explosion : public GeoNode
{
public:
	std::vector<ComponentNode> components;

	particleData particles[NUM_PARTICLES];
	int fuel = 0;
	int wantNormalize = 0;
	Explosion();
	~Explosion();
	void newSpeed(float dest[3]);
	void newExplosion(void);
	virtual void VOnClientUpdate(GameInfoPacket* pData);

	virtual void VOnDraw();
	virtual void VOnUpdate(GameInfoPacket* pData);
};
#endif
