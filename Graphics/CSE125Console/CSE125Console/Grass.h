#ifndef CSE167_Grass_h
#define CSE167_Grass_h
#include "stdafx.h"
#include <vector>
#include "GeoNode.h"
class Grass : public GeoNode
{

public:
	Grass();
	int texture;
	virtual ~Grass(void);
	virtual void VOnClientUpdate(GameInfoPacket* pData);

	virtual void VOnDraw();
	virtual void VOnUpdate(GameInfoPacket* pData);
private:
	void Initialize();
	float vClusterTranslation[3];
};

#endif

