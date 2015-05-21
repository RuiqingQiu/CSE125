#include "stdafx.h"
#pragma once
#ifndef __Light__
#define __Light__
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
	float red, green, blue;
	Light();
	Light(float x, float y, float z);
	~Light();
	void setPosition(float x, float y, float z);
	virtual void VOnClientUpdate(GameInfoPacket* pData);
	Vector4 getGlobalLightPosition();
	virtual void VOnDraw();
	virtual void VOnUpdate(GameInfoPacket* pData);
};
#endif
