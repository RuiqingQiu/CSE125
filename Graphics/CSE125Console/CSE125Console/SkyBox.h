#pragma once
#include "GeoNode.h"
//#include "Shader.h"
#include <GL/glut.h>
#include "Transform.h"
#include <gl\GL.h>
#include "SOIL.h"

class SkyBox :
	public GeoNode
{
public:
	float size_of_texture_cube = 100;

	SkyBox();
	SkyBox(char* filename);

	~SkyBox();

	virtual void VOnClientUpdate(GameInfoPacket* pData);

	virtual void VOnDraw();
	virtual void VOnUpdate(GameInfoPacket* pData);
private :
	bool initSkyBox();
	GLuint texture[5];
};

