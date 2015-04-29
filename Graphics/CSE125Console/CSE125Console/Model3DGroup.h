#pragma once
#pragma once
#include "stdafx.h"
#include "glew.h"

//#include "Shader.h"
//#include "GameCore.h"
#include "GeoNode.h"
#include "tiny_obj_loader.h"
#include <GL/glut.h>
#include "RenderObject.h"
#include "Model3D.h"
class Model3DGroup : public Model3D
{
public:
	vector<Model3D*> objects;
	Model3DGroup();
	~Model3DGroup();
	
	void addObject(Model3D* object);
	virtual void VOnClientUpdate(GameInfoPacket* pData);

	virtual void VOnDraw();
	virtual void VOnUpdate(GameInfoPacket* pData);
};

