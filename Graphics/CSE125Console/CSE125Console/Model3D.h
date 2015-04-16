#pragma once
#include "stdafx.h"
#include "Shader.h"
#include "GeoNode.h"
#include "tiny_obj_loader.h"
#include <GL/glut.h>
class Model3D: public GeoNode
{
public:
	std::vector<tinyobj::shape_t> shapes;
	std::vector<tinyobj::material_t> materials;

	Model3D();
	Model3D(string filename);
	~Model3D();
	virtual void VOnClientUpdate(GameInfoPacket* pData);

	virtual void VOnDraw();
	virtual void VOnUpdate(GameInfoPacket* pData);
private:
	bool isTextured = false;
};

