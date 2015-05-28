#pragma once
#ifndef __SKYBOX__
#define __SKYBOX__
#include <string>
#include "GeoNode.h"
#include "glew.h"
#include <GL/glut.h>
#include "Transform.h"
#include <gl\GL.h>
#include "SOIL.h"


//image requirements:
//     must be in jpg format
//loading format: [name]_front.jpg, [name]_back.jpg, [name]_left.jpg, [name]_right.jpg, [name]_top.jpg
class SkyBox :
	public GeoNode
{
public:
	float size_of_texture_cube = 500;
	GLuint cubemapTexture;
	SkyBox();
	//pass in format: [path]/[skytexture name] do not pass in [_front.jpg] segment
	SkyBox(std::string filename);

	~SkyBox();

	virtual void VOnClientUpdate(GameInfoPacket* pData);

	virtual void VOnDraw();
	virtual void VOnUpdate(GameInfoPacket* pData);
private :
	bool initSkyBox();
	GLuint texture[5];

	std::string skyBoxName;
};
#endif
