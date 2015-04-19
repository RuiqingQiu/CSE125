#include "stdafx.h"
#pragma once
#include <vector>
#include "ComponentNode.h"
#include "GeoNode.h"
#include "Matrix4.h"
#include "Vector4.h"
class Light : public GeoNode
{
public:
	
	std::vector<ComponentNode> components;
	Light();
	~Light();
	void setPosition(float x, float y, float z);
	virtual void VOnClientUpdate(GameInfoPacket* pData);

	virtual void VOnDraw();
	virtual void VOnUpdate(GameInfoPacket* pData);
};

