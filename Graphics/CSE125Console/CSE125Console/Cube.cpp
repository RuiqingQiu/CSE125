#include "stdafx.h"

#include "Cube.h"
#include "Window.h"

#ifdef __APPLE__
    #include <GLUT/glut.h>
#else
    #include <GL/glut.h>
#endif

#include "math.h"
#include "SOIL.h"
Cube::Cube(float size)
{
	localTransform = Transform();
    this->size = size;
}

Cube::~Cube()
{
    //Delete any dynamically allocated memory/objects here
}

void Cube::VOnUpdate(GameInfoPacket* pData)
{

}
void Cube::VOnClientUpdate(GameInfoPacket* pData){ 
	PlayerInfo* p = pData->get_player_info(this->identifier);
	if (p){
		this->localTransform.position = Vector3(mat[12], mat[13], mat[14]);
		/*
		float r11 = mat[0];
		float r21 = mat[4];
		float r31 = mat[8];
		float r12 = mat[1];
		float r22 = mat[5];
		float r32 = mat[9];
		float r13 = mat[2];
		float r23 = mat[6];
		float r33 = mat[10];
		*/
		float r11 = mat[0];
		float r21 = mat[1];
		float r31 = mat[2];
		float r12 = mat[4];
		float r22 = mat[5];
		float r32 = mat[6];
		float r13 = mat[8];
		float r23 = mat[9];
		float r33 = mat[10];
		
		float x = atan2(r32, r33);
		float y = atan2(-r31, sqrt(r32*r32 + r33*r33));
		float z = atan2(r21, r11);
		this->localTransform.rotation = Vector3(x, y, z);
		//localTransform.rotation.print("local transform rotation: ");
		for (int i = 0; i < 16; i++){
			mat[i] = p->mat[i];
		}
		p->processed = true;
	}
}

void Cube::VOnDraw()
{
    float halfSize = size/2.0;

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
	glColor3f(1, 0, 0);
    glNormal3f(0.0, 0.0, 1.0);
    glVertex3f(-halfSize,  halfSize,  halfSize);
    glVertex3f( halfSize,  halfSize,  halfSize);
    glVertex3f( halfSize, -halfSize,  halfSize);
    glVertex3f(-halfSize, -halfSize,  halfSize);
	glColor3f(0, 1, 0);
    // Draw left side:
    glNormal3f(-1.0, 0.0, 0.0);
    glVertex3f(-halfSize,  halfSize,  halfSize);
    glVertex3f(-halfSize,  halfSize, -halfSize);
    glVertex3f(-halfSize, -halfSize, -halfSize);
    glVertex3f(-halfSize, -halfSize,  halfSize);
    
    // Draw right side:
    glNormal3f(1.0, 0.0, 0.0);
    glVertex3f( halfSize,  halfSize,  halfSize);
    glVertex3f( halfSize,  halfSize, -halfSize);
    glVertex3f( halfSize, -halfSize, -halfSize);
    glVertex3f( halfSize, -halfSize,  halfSize);
    
    // Draw back face:
    glNormal3f(0.0, 0.0, -1.0);
    glVertex3f(-halfSize,  halfSize, -halfSize);
    glVertex3f( halfSize,  halfSize, -halfSize);
    glVertex3f( halfSize, -halfSize, -halfSize);
    glVertex3f(-halfSize, -halfSize, -halfSize);
    
    // Draw top side:
    glNormal3f(0.0, 1.0, 0.0);
    glVertex3f(-halfSize,  halfSize,  halfSize);
    glVertex3f( halfSize,  halfSize,  halfSize);
    glVertex3f( halfSize,  halfSize, -halfSize);
    glVertex3f(-halfSize,  halfSize, -halfSize);
    
    // Draw bottom side:
    glNormal3f(0.0, -1.0, 0.0);
    glVertex3f(-halfSize, -halfSize, -halfSize);
    glVertex3f( halfSize, -halfSize, -halfSize);
    glVertex3f( halfSize, -halfSize,  halfSize);
    glVertex3f(-halfSize, -halfSize,  halfSize);
    
    glEnd();
    

	//glColor4f(0.9f, 0.9f, 0.9f, 1);

    //The above glBegin, glEnd, glNormal and glVertex calls can be replaced with a glut convenience function
    //glutSolidCube(size);
	glColor4f(0.9f, 0.9f, 0.9f, 1);

    //Pop the save state off the matrix stack
    //This will undo the multiply we did earlier
    glPopMatrix();

}


