#pragma once
#include "stdafx.h"
#include "glew.h"
#include "GameCore.h"
#include "tiny_obj_loader.h"
#include <GL/glut.h>

class RenderObject
{


public:
	std::vector<tinyobj::shape_t> shapes;
	std::vector<tinyobj::material_t> materials;
	RenderObject(string filename);
	~RenderObject();
};

