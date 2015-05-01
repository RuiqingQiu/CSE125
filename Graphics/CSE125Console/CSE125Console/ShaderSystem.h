#pragma once
#ifndef __ShaderSystem__
#define __ShaderSystem__
#include "stdafx.h"
#include "glew.h"
#include "tiny_obj_loader.h"
#include <GL/glut.h>
#include <string>
#include "Definition.h"
#include <iostream>
#include "SOIL.h"

class ShaderSystem
{
public:
	//Shader ids
	vector<GLhandleARB> shader_ids;

	//These are for two pass rendering
	//FBO handle
	GLuint fb;
	//Color texture from FBO
	GLuint color;
	//Depth buffer from FBO
	GLuint depth;
	ShaderSystem();
	bool loadShaders(string vertex_shader_path, string fragment_shader_path);
	void BindShader(int type);
	void UnbindShader();
	~ShaderSystem();
};
#endif

