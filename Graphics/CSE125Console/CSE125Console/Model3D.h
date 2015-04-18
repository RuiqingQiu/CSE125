#pragma once
#include "stdafx.h"
#include "glew.h"
//#include "Shader.h"
#include "GeoNode.h"
#include "tiny_obj_loader.h"
#include "GameCore.h"
#include <GL/glut.h>
class Model3D: public GeoNode
{
public:
	std::vector<tinyobj::shape_t> shapes;
	std::vector<tinyobj::material_t> materials;

	Model3D();
	Model3D(string filename, string matname, string rough, string metal, string normal );

	int textureId = 0;
	int roughId = 0;
	int metalId = 0;
	int normalId = 0;

	~Model3D();
	virtual void VOnClientUpdate(GameInfoPacket* pData);

	virtual void VOnDraw();
	virtual void VOnUpdate(GameInfoPacket* pData);
private:
	bool isTextured = false;

	GLhandleARB loadShader(char* filename, unsigned int type);
	void loadObjShader();

	GLhandleARB shaderId;
	GLuint textureUniform;
	GLuint normalUniform;
	GLuint cameraUniform;
	GLuint metalUniform;
	GLuint roughUniform;
	GLuint worldMatUniform;

};

