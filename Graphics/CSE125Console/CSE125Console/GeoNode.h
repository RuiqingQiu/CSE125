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
	int identifier;
	Transform localTransform;
	float mat[16];

	virtual void VOnDraw(){ };
	virtual void VOnUpdate(GameInfoPacket* pData){ };
	virtual void VOnClientUpdate(GameInfoPacket* pData){ };

};

