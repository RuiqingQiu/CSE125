#pragma once
#include "stdafx.h"
#include <glew.h>
#ifndef _SHADER_H_
#define _SHADER_H_

/*! Handles GLSL shaders.  It can load the code from the file or read straight
* from the char array. */
class Shader
{
public:
	//unsigned int pid; // prog id
	GLhandleARB pid; // prog id

public:
	Shader(const char *vert, const char *frag, bool isFile = true);
	~Shader();

	/** bind/unbind this shader. */
	void bind();
	void unbind();

	/** get the program */
	//unsigned int getPid()
	GLhandleARB getPid()
	{
		return pid;
	}

	/** dump log */
	void printLog(const char* tag = "");

	static void enable();
	static void disable();

private:
	/** read a shader file
	programmer is responsible for deleting returned buffer */
	char* read(const char *filename);

	/** create shaders from given vert and frag programs. */
	void setup(const char *vs, const char *fs);
};


#endif