#include "stdafx.h"
#include "roboBase.h"

#ifdef __APPLE__
#include <GLUT/glut.h>
#else
#include <GL/glut.h>
#endif

roboBase::roboBase()
{
	localTransform = Transform();
	width = 3;
	height = 1;
}

roboBase::roboBase(int w, int h) {
	localTransform = Transform();
	width = w;
	height = h;
}

roboBase::~roboBase()
{
}

void roboBase::VOnClientUpdate(GameInfoPacket* pData) {
	PlayerInfo* p = pData->get_player_info(this->identifier);
	if (p){

		localTransform.position.x = p->x;
		localTransform.position.y = p->y;
		localTransform.position.z = p->z;

		localTransform.rotation.x = p->rx;
		localTransform.rotation.y = p->ry;
		localTransform.rotation.z = p->rz;
		p->processed = true;
	}
}

void roboBase::VOnDraw() {
	int halfSize = 0.5;

	//Set the OpenGL Matrix mode to ModelView (used when drawing geometry)
	glMatrixMode(GL_MODELVIEW);
	glPushMatrix();
	glDisable(GL_CULL_FACE);
	//Apply local transformation
	glMultMatrixd(localTransform.GetGLMatrix4().getPointer());
	//glMultMatrixf(mat);

	//world.identity();
	//Push a save state onto the matrix stack, and multiply in the toWorld matrix
	//world = world * localTransform.GetMatrix4();
	//world.transpose();
	//glLoadMatrixd(world.getPointer());
	//glutSolidTeapot(2);
	//Make cube!
	//Note: The glBegin, and glEnd should always be as close to the glNormal/glVertex calls as possible
	//These are special calls that 'freeze' many internal states of OpenGL.
	//Once the glBegin state is active many of the calls made to OpenGL (like glMultMatrixf) will be IGNORED!
	//As a good habit, only call glBegin just before you need to draw, and call end just after you finish


	glBegin(GL_QUADS);
	//glTranslated(0, 0, 5);
	// Draw front face:
	//red
	glColor3f(1, 0, 0);
	glNormal3f(0.0, 0.0, 1.0);
	glVertex3f(-halfSize, halfSize, halfSize);
	glVertex3f(halfSize, halfSize, halfSize);
	glVertex3f(halfSize, -halfSize, halfSize);
	glVertex3f(-halfSize, -halfSize, halfSize);
	//green
	glColor3f(0, 1, 0);
	// Draw left side:

	glNormal3f(-1.0, 0.0, 0.0);
	glVertex3f(-halfSize, halfSize, halfSize);
	glVertex3f(-halfSize, halfSize, -halfSize);
	glVertex3f(-halfSize, -halfSize, -halfSize);
	glVertex3f(-halfSize, -halfSize, halfSize);

	//green + blue
	glColor3f(0.0, 1.0, 1.0);

	// Draw right side:
	glNormal3f(1.0, 0.0, 0.0);
	glVertex3f(halfSize, halfSize, halfSize);
	glVertex3f(halfSize, halfSize, -halfSize);
	glVertex3f(halfSize, -halfSize, -halfSize);
	glVertex3f(halfSize, -halfSize, halfSize);

	//yellow
	glColor3f(1.0, 1.0, 0.0);
	// Draw back face:
	glNormal3f(0.0, 0.0, -1.0);
	glVertex3f(-halfSize, halfSize, -halfSize);
	glVertex3f(halfSize, halfSize, -halfSize);
	glVertex3f(halfSize, -halfSize, -halfSize);
	glVertex3f(-halfSize, -halfSize, -halfSize);

	glColor3f(0.0, 0.0, 1.0);
	// Draw top side:
	glNormal3f(0.0, 1.0, 0.0);
	glVertex3f(-halfSize, halfSize, halfSize);
	glVertex3f(halfSize, halfSize, halfSize);
	glVertex3f(halfSize, halfSize, -halfSize);
	glVertex3f(-halfSize, halfSize, -halfSize);

	glColor3f(1.0, 1.0, 1.0);
	// Draw bottom side:
	glNormal3f(0.0, -1.0, 0.0);
	glVertex3f(-halfSize, -halfSize, -halfSize);
	glVertex3f(halfSize, -halfSize, -halfSize);
	glVertex3f(halfSize, -halfSize, halfSize);
	glVertex3f(-halfSize, -halfSize, halfSize);

	glEnd();


	//glColor4f(0.9f, 0.9f, 0.9f, 1);

	//The above glBegin, glEnd, glNormal and glVertex calls can be replaced with a glut convenience function
	//glutSolidCube(size);
	glColor4f(0.9f, 0.9f, 0.9f, 1);

	//Pop the save state off the matrix stack
	//This will undo the multiply we did earlier
	glPopMatrix();

}

void roboBase::VOnUpdate(GameInfoPacket* pData) {

}