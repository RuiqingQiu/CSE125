#pragma once
#include "stdafx.h"
#include "glew.h"
//#include "GameCore.h"
#include "tiny_obj_loader.h"
#include <GL/glut.h>
#include <string>
#include <iostream>
#include "SOIL.h"
using namespace std;
//#include "GeoNode.h"
class RenderObject
{


public:
	GLhandleARB shader_id;
	GLuint texturaID[4];

	std::vector<tinyobj::shape_t> shapes;
	std::vector<tinyobj::material_t> materials;
	RenderObject(string filename, string texture, string normal, string gloss,
		string metal);
	~RenderObject();
};

