#ifndef CSE167_Cube_h
#define CSE167_Cube_h
#include "stdafx.h"
#include <vector>
#include "ComponentNode.h"
#include "GeoNode.h"
class Cube : public GeoNode
{
    
public: 
    
    float size;

	std::vector<ComponentNode> components;

    Cube(float);
    virtual ~Cube(void);
	virtual void VOnClientUpdate(GameInfoPacket* pData);

	virtual void VOnDraw();
	virtual void VOnUpdate(GameInfoPacket* pData);
    
};

#endif

