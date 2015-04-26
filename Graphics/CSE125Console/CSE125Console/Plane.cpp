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
	color = Vector3(0.3, 0.3, 0.3);
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

void Plane::setColor(float r, float g, float b){
	color.x = r;
	color.y = g;
	color.z = b;
}

void Plane::VOnDraw()
{
	float halfSize = size / 2.0;

	//Set the OpenGL Matrix mode to ModelView (used when drawing geometry)
	glMatrixMode(GL_MODELVIEW);
	glPushMatrix();
	//Apply local transformation
	glMultMatrixd(localTransform.GetGLMatrix4().getPointer());
	glColor4f(color.x, color.y, color.z, 1);

	glBegin(GL_QUADS);

		glNormal3f(0.0, 1, 0.0);
		glVertex3f(-halfSize, 0, -halfSize);
		glVertex3f(-halfSize, 0, halfSize);
		glVertex3f(halfSize, 0, halfSize);
		glVertex3f(halfSize, 0, -halfSize);

	glEnd();
	glColor4f(1, 1, 1, 1);


	//Pop the save state off the matrix stack
	//This will undo the multiply we did earlier
	glPopMatrix();

}


