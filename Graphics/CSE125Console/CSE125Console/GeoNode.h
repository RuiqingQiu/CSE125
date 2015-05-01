#pragma once
#include "stdafx.h"
#include "Matrix4.h"
#include "GameInfoPacket.h"
#include "Transform.h"
class GeoNode
{
public:
	GeoNode();
	~GeoNode();

	//send to server object id, must be unique per player id
	int identifier;
	//send to server (0 for 1x1 nontexture cube) (1 for nontexture battlefield) (2 for nontexture wall) (3 for nontexture 3x3 cube)
	int textureType;

	Transform localTransform;
	float mat[16];

	virtual void VOnDraw(){ };
	virtual void VOnUpdate(GameInfoPacket* pData){ };
	virtual void VOnClientUpdate(GameInfoPacket* pData){ };

	bool isUpdated;
	int healthStat;
	int damageStat;
	int speedStat;
	int width;
	int height;

	virtual bool intersect(Vector3 pos);
};

