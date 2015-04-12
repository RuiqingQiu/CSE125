#include "stdafx.h"

#include "Plane.h"
#include "Window.h"

#ifdef __APPLE__
#include <GLUT/glut.h>
#else
#include <GL/glut.h>
#endif

#include "math.h"
#include "SOIL.h"
Plane::Plane(float size)
{
	localTransform = Transform();
	this->size = size;
}

Plane::~Plane()
{
	//Delete any dynamically allocated memory/objects here
}

void Plane::VOnUpdate(GameInfoPacket* pData)
{

}
void Plane::VOnClientUpdate(GameInfoPacket* pData){
	PlayerInfo* p = pData->get_player_info(this->identifier);
	if (p){
		this->localTransform.position = Vector3(p->x, p->y, p->z);
		p->processed = true;
	}
}

void Plane::VOnDraw()
{
	float halfSize = size / 2.0;

	//Set the OpenGL Matrix mode to ModelView (used when drawing geometry)
	glMatrixMode(GL_MODELVIEW);
	glPushMatrix();
	//Apply local transformation
	glMultMatrixd(localTransform.GetGLMatrix4().getPointer());
	glColor4f(0.3f, 0.3f, 0.3f, 1);

	glBegin(GL_QUADS);
	//glTranslated(0, 0, 5);
	// Draw front face:
	glNormal3f(0.0, 10, 0.0);
	glVertex3f(-45, 0, -45);
	glVertex3f(-45, 0, 55);
	glVertex3f(55, 0, 55);
	glVertex3f(55, 0, -45);

	glEnd();
	glColor4f(0.3f, 0.3f, 0.3f, 1);


	//Pop the save state off the matrix stack
	//This will undo the multiply we did earlier
	glPopMatrix();

}


