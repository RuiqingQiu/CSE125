#include "stdafx.h"
#include "Light.h"
#ifdef __APPLE__
#include <GLUT/glut.h>
#else
#include <GL/glut.h>
#endif

static int counter = 0;
Light::Light()
{
	localTransform.position = Vector3(0, 0, 0);
}

Light::Light(float x, float y, float z){
	localTransform.position = Vector3(x,y,z);
}

Light::~Light()
{
}

void Light::VOnClientUpdate(GameInfoPacket* pData){

}

void Light::setPosition(float x, float y, float z){
	localTransform.position = Vector3(x, y, z);
}

void Light::VOnDraw(){
	counter = (counter + 1) % 360;
	Matrix4 tmp;
	tmp.makeRotateY(1);
	Vector4 tmp1 = tmp * Vector4(localTransform.position.x, localTransform.position.y, localTransform.position.z, 1);
	localTransform.position.x = tmp1.x;
	localTransform.position.y = tmp1.y;
	localTransform.position.z = tmp1.z;


	glMatrixMode(GL_MODELVIEW);
	glPushMatrix();
	//Apply local transformation
	glMultMatrixd(localTransform.GetGLMatrix4().getPointer());
	glColor3f(0, 1, 0);
	//glutSolidCube(20);
	glutSolidSphere(1,20,20);
	glColor3f(1, 1, 1);
	glPopMatrix();
	
}
void Light::VOnUpdate(GameInfoPacket* pData){

}