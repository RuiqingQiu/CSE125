#pragma once
#include "stdafx.h"
#include "glew.h"

//#include "Shader.h"
//#include "GameCore.h"
#include "GeoNode.h"
#include "tiny_obj_loader.h"
#include <GL/glut.h>
#include "RenderObject.h"
#include "Materials.h"
class Model3D: public GeoNode
{
public:
	//If auto rotate for the object
	bool auto_rotate = false;
	Materials material;
	//If require two pass draw
	bool two_pass_draw = false;

	RenderObject* render_obj;
	int shader_type;
	//File path for the vertex and fragment shader
	string vertex_shader;
	string fragment_shader;
	//File path for the 4 maps
	string texture_map;
	string normal_map;
	string gloss_map;
	string metallic_map;
	Model3D();
	Model3D(RenderObject* render_obj);
	~Model3D();
	void setTextureMap(string pathname);
	void setNormalMap(string pathname);
	void setGlossMap(string pathname);
	void setMetallicMap(string pathname);
	void setShaderType(int type);


	virtual void VOnClientUpdate(GameInfoPacket* pData);

	virtual void VOnDraw();
	virtual void VOnUpdate(GameInfoPacket* pData);

	Vector3 offset;
private:
	bool isTextured = false;
};

