#ifndef CSE167_Plane_h
#define CSE167_Plane_h
#include "stdafx.h"
#include <vector>
#include "ComponentNode.h"
#include "GeoNode.h"
class Plane : public GeoNode
{

public:

	float size;
	Vector3 color;
	std::vector<ComponentNode> components;
	Vector3 normal;
	Plane(float);
	void setColor(float r, float g, float b);
	virtual ~Plane(void);
	virtual void VOnClientUpdate(GameInfoPacket* pData);

	virtual void VOnDraw();
	virtual void VOnUpdate(GameInfoPacket* pData);

};

#endif