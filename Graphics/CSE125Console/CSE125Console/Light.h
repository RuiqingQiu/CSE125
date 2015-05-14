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
	float pos_x, pos_y, pos_z;
	Light();
	Light(float x, float y, float z);
	~Light();
	void setPosition(float x, float y, float z);
	virtual void VOnClientUpdate(GameInfoPacket* pData);
	Vector4 getGlobalLightPosition();
	virtual void VOnDraw();
	virtual void VOnUpdate(GameInfoPacket* pData);
};

