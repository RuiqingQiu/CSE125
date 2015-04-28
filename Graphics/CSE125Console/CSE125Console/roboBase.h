#pragma once
#include "stdafx.h"
#include <vector>
#include "ComponentNode.h"
#include "GeoNode.h"

class roboBase : public GeoNode
{
public:
	roboBase();
	roboBase(int w, int h);
	virtual void VOnClientUpdate(GameInfoPacket* pData);

	virtual void VOnDraw();
	virtual void VOnUpdate(GameInfoPacket* pData);

	int width;
	int height;

	~roboBase();
};

