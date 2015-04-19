#include "stdafx.h"

#include "Teapot.h"
#include "Window.h"

#ifdef __APPLE__
#include <GLUT/glut.h>
#else
#include <GL/glut.h>
#endif

#include "math.h"
#include "SOIL.h"
Teapot::Teapot(float size)
{
	localTransform = Transform();
	this->size = size;
}

Teapot::~Teapot()
{
	//Delete any dynamically allocated memory/objects here
}

void Teapot::VOnUpdate(GameInfoPacket* pData)
{

}
void Teapot::VOnClientUpdate(GameInfoPacket* pData){
}


// Use to activate/disable shadowShader
//GLuint shadowMapUniform;



void Teapot::VOnDraw()
{



	//shadowMapUniform = glGetUniformLocationARB(shader_id, "ShadowMap");

	glMatrixMode(GL_MODELVIEW);
	glPushMatrix();
	glMultMatrixd(localTransform.GetGLMatrix4().getPointer());
	
	glutSolidTeapot(2);

	glColor4f(0.9f, 0.9f, 0.9f, 1);

	glPopMatrix();

}


