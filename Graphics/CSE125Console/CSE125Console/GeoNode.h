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
	//if requires two pass
	bool edge_highlight = false;
	bool blur = false;
	bool static_object = false;
	//send to server object id, must be unique per player id
	int identifier;
	//send to server (0 for 1x1 nontexture cube) (1 for nontexture battlefield) (2 for nontexture wall) (3 for nontexture 3x3 cube)
	int textureType;
	int type = 0;

	Transform localTransform;
	float mat[16];

	virtual void VOnDraw(){ };
	virtual void VOnUpdate(GameInfoPacket* pData){ };
	virtual void VOnClientUpdate(GameInfoPacket* pData){ };

	virtual void clearConstraints();

	bool isUpdated;
	int healthStat;
	int damageStat;
	int speedStat;
	int width;
	int height;

	int below_id;
	int left_id;
	int right_id;
	int front_id;
	int back_id;
	void setEdgeHighlight(bool);
	virtual bool intersect(Vector3 pos);
};

