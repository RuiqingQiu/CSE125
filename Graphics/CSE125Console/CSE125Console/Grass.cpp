#include "stdafx.h"
#include "Grass.h"
#include "SOIL.h"
#include "glew.h"

Grass::Grass()
{
	Initialize();
}


Grass::~Grass()
{
}

void Grass::VOnUpdate(GameInfoPacket* pData)
{

}
void Grass::VOnClientUpdate(GameInfoPacket* pData){

}

void Grass::VOnDraw()
{
	//Set the OpenGL Matrix mode to ModelView (used when drawing geometry)
	glMatrixMode(GL_MODELVIEW);
	glPushMatrix();
	glDisable(GL_CULL_FACE);
	//Apply local transformation
	glMultMatrixd(localTransform.GetGLMatrix4().getPointer());
	// Use bilinear interpolation:
	glEnable(GL_TEXTURE_2D);
	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, texture);
	glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_MODULATE);
	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	glBegin(GL_QUADS);

	glNormal3f(0.0, 0.0, 1.0);
	glTexCoord2f(0,1);
	glVertex3f(-1, 1, 0);
	glTexCoord2f(1,1);
	glVertex3f(1, 1, 0);
	glTexCoord2f(1, 0);
	glVertex3f(1, -1, 0);
	glTexCoord2f(0,0);
	glVertex3f(-1, -1, 0);


	glNormal3f(-1.0, 0.0, 1.0);
	glTexCoord2f(0, 1);
	glVertex3f(-0.7, 1, 0.7);
	glTexCoord2f(1, 1);
	glVertex3f(0.7, 1, -0.7);
	glTexCoord2f(1, 0);
	glVertex3f(0.7, -1, -0.7);
	glTexCoord2f(0, 0);
	glVertex3f(-0.7, -1, 0.7);


	glNormal3f(-1.0, 0.0, 1.0);
	glTexCoord2f(0, 1);
	glVertex3f(-0.7, 1, -0.7);
	glTexCoord2f(1, 1);
	glVertex3f(0.7, 1, 0.7);
	glTexCoord2f(1, 0);
	glVertex3f(0.7, -1, 0.7);
	glTexCoord2f(0, 0);
	glVertex3f(-0.7, -1, -0.7);

	glDisable (GL_BLEND);
	glEnd();
	glColor4f(0.9f, 0.9f, 0.9f, 1);
	glPopMatrix();
}

void Grass::Initialize()
{
	texture = SOIL_load_OGL_texture("Assets/Grass/tallgrass.png", SOIL_LOAD_AUTO,
	SOIL_CREATE_NEW_ID,
	SOIL_FLAG_INVERT_Y);
	if (texture == 0)
	{
		cout << "error" << endl;
	}
	else{
		cout << texture << endl;
	}
}