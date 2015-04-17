#ifndef TEAPOT
#define TEAPOT
#include "stdafx.h"
#include <vector>
#include "ComponentNode.h"
#include "GeoNode.h"
class Teapot : public GeoNode
{

public:

	float size;
	std::vector<ComponentNode> components;

	Teapot(float);
	virtual ~Teapot(void);
	virtual void VOnClientUpdate(GameInfoPacket* pData);

	virtual void VOnDraw();
	virtual void VOnUpdate(GameInfoPacket* pData);

};

#endif

