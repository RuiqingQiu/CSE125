#include "stdafx.h"
#include "Grass.h"
#include "SOIL.h"
#include "glew.h"
#include "Window.h"

Grass::Grass(void)
{
	vClusterTranslation[0] = rand() % 100 * 0.1;
	vClusterTranslation[1] = 0;// rand() % 100 * 0.1;
	vClusterTranslation[2] = 0;// rand() % 100 * 0.1;

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
	Window::shader_system->BindShader(GRASS_SHADER);

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

	float vlight[3] = { 0, 5, 0 };
	glUniform3fv(glGetUniformLocationARB(Window::shader_system->shader_ids[GRASS_SHADER], "vLight"), 1, vlight);
	float vClusterTranslation_i[3] = { sin(vClusterTranslation[0])*0.25, 0, 0 };

	glUniform3fv(glGetUniformLocationARB(Window::shader_system->shader_ids[GRASS_SHADER], "vClusterTranslation"), 1, vClusterTranslation_i);

	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, texture);
	glUniform1i(glGetUniformLocation(Window::shader_system->shader_ids[GRASS_SHADER], "tex"), 0);

	glBegin(GL_QUADS);

	int scale = 3;

	glNormal3f(0.0, 0.0, 1.0);
	glTexCoord2f(0, 1);
	glVertex3f(-1, 1 * 0.5, 0);
	glTexCoord2f(1, 1);
	glVertex3f(1, 1 * 0.5, 0);
	glTexCoord2f(1, 0);
	glVertex3f(1, -1 * 0.5, 0);
	glTexCoord2f(0, 0);
	glVertex3f(-1, -1 * 0.5, 0);


	glNormal3f(-1.0, 0.0, 1.0);
	glTexCoord2f(0, 1);
	glVertex3f(-0.7, 1 * 0.5, 0.7);
	glTexCoord2f(1, 1);
	glVertex3f(0.7, 1 * 0.5, -0.7);
	glTexCoord2f(1, 0);
	glVertex3f(0.7, -1 * 0.5, -0.7);
	glTexCoord2f(0, 0);
	glVertex3f(-0.7, -1 * 0.5, 0.7);


	glNormal3f(-1.0, 0.0, 1.0);
	glTexCoord2f(0, 1);
	glVertex3f(-0.7, 1 * 0.5, -0.7);
	glTexCoord2f(1, 1);
	glVertex3f(0.7, 1 * 0.5, 0.7);
	glTexCoord2f(1, 0);
	glVertex3f(0.7, -1 * 0.5, 0.7);
	glTexCoord2f(0, 0);
	glVertex3f(-0.7, -1 * 0.5, -0.7);

	glDisable(GL_BLEND);
	glEnd();
	glColor4f(0.9f, 0.9f, 0.9f, 1);
	glPopMatrix();
	Window::shader_system->UnbindShader();

	vClusterTranslation[0] = vClusterTranslation[0] + 0.01;

}

void Grass::Initialize()
{
	texture = SOIL_load_OGL_texture("Assets/Grass/thingrass.tga", SOIL_LOAD_AUTO,
		SOIL_CREATE_NEW_ID,
		SOIL_FLAG_INVERT_Y);
	if (texture == 0)
	{
		cout << "error" << endl;
	}
	else{
	}
}