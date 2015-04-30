#ifndef CSE167_Grass_h
#define CSE167_Grass_h
#include "stdafx.h"
#include <vector>
#include "ComponentNode.h"
#include "GeoNode.h"
class Grass : public GeoNode
{

public:
	Grass();
	virtual ~Grass(void);
	int texture;
	virtual void VOnClientUpdate(GameInfoPacket* pData);
	virtual void VOnDraw();
	virtual void VOnUpdate(GameInfoPacket* pData);
private:
	void Initialize();

};

#endif