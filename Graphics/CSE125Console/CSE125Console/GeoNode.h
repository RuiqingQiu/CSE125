#pragma once
#include "stdafx.h"
#include "Matrix4.h"
#include "GameInfoPacket.h"
class GeoNode
{
public:
	GeoNode();
	~GeoNode();
	int identifier;

	virtual void VOnDraw(){ };
	virtual void VOnUpdate(GameInfoPacket* pData){ };
};

