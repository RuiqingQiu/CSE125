#pragma once
#include "stdafx.h"
#include "glew.h"

//#include "Shader.h"
#include "GameCore.h"
#include "GeoNode.h"
#include "tiny_obj_loader.h"
#include <GL/glut.h>
class Model3D: public GeoNode
{
public:
	std::vector<tinyobj::shape_t> shapes;
	std::vector<tinyobj::material_t> materials;
	GLhandleARB shader_id;
	GLuint texturaID[4];
	string texture_map;
	string normal_map;
	string gloss_map;
	string metallic_map;
	Model3D();
	Model3D(string filename);
	~Model3D();
	void setTextureMap(string pathname);
	void setNormalMap(string pathname);
	void setGlossMap(string pathname);
	void setMetallicMap(string pathname);
	virtual void VOnClientUpdate(GameInfoPacket* pData);

	virtual void VOnDraw();
	virtual void VOnUpdate(GameInfoPacket* pData);
private:
	bool isTextured = false;
};

