#pragma once

#ifndef MODEL3DFACTORY
#define MODEL3DFACTORY
#include "stdafx.h"
#include "Model3D.h"
#include <vector>
#include "RenderObject.h"
#include "Definition.h"
class Model3DFactory
{
	
public:
	//static vector<RenderObject*> render_obj_lst;

	Model3DFactory();
	~Model3DFactory();

	static Model3D* generateObjectWithType(int type);

	static Model3D * generateDefault();
};

static Model3DFactory* m_factory;

#endif

