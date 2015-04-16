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

	std::vector<ComponentNode> components;

	Plane(float);
	virtual ~Plane(void);
	virtual void VOnClientUpdate(GameInfoPacket* pData);

	virtual void VOnDraw();
	virtual void VOnUpdate(GameInfoPacket* pData);

};

#endif