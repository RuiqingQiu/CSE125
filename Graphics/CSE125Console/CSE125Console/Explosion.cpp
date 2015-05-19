#include "stdafx.h"
#include "Explosion.h"
#ifdef __APPLE__
#include <GLUT/glut.h>
#else
#include <GL/glut.h>
#endif

Explosion::Explosion()
{
}


Explosion::~Explosion()
{
}

void  Explosion::newSpeed(float dest[3]){
	float x;
	float y;
	float z;
	float len;
	x = (2.0 * ((GLfloat)rand()) / ((GLfloat)RAND_MAX)) - 1.0;
	y = (2.0 * ((GLfloat)rand()) / ((GLfloat)RAND_MAX)) - 1.0;
	z = (2.0 * ((GLfloat)rand()) / ((GLfloat)RAND_MAX)) - 1.0;

	if (wantNormalize){
		len = sqrt(x*x + y*y + z*z);
		if (len){
			x = x / len;
			y = y / len;
			z = z / len;
		}
	}
	dest[0] = x;
	dest[1] = y;
	dest[2] = z;
}
void Explosion::newExplosion(void){
	int i;
	for (i = 0; i < NUM_PARTICLES; i++){
		particles[i].position[0] = 0.0;
		particles[i].position[1] = 0.0;
		particles[i].position[2] = 0.0;

		particles[i].color[0] = 1.0;
		particles[i].color[1] = 1.0;
		particles[i].color[2] = 0.5;

		newSpeed(particles[i].speed);
	}
	fuel = 1000;
}
void Explosion::VOnClientUpdate(GameInfoPacket* pData){

}

void Explosion::VOnDraw(){
	//cout << "explosion fuel" << fuel << endl;
	//If fuel = 0, do nothing
	if (fuel = 0){

	}
	//The first time of the explosion
	if (fuel == 100){
		cout << "first time" << endl;
		glPushMatrix();
		glPointSize(4);
		glBegin(GL_POINTS);
		for (int i = 0; i < NUM_PARTICLES; i++){
			glColor3fv(particles[i].color);
			glVertex3fv(particles[i].position);
		}
		glEnd();
		glPopMatrix();
	}
	else if (fuel > 0){
		cout << "here" << endl;
		for (int i = 0; i < NUM_PARTICLES; i++){
			particles[i].position[0] += particles[i].speed[0] * 0.1;
			particles[i].position[1] += particles[i].speed[1] * 0.1;
			particles[i].position[2] += particles[i].speed[2] * 0.1;

			particles[i].color[0] -= 1.0 / 500.0;
			if (particles[i].color[0] < 0.0){
				particles[i].color[0] = 0.0;
			}

			particles[i].color[1] -= 1.0 / 500.0;
			if (particles[i].color[1] < 0.0){
				particles[i].color[1] = 0.0;
			}

			particles[i].color[2] -= 1.0 / 500.0;
			if (particles[i].color[2] < 0.0){
				particles[i].color[2] = 0.0;
			}

			--fuel;
		}
	}
}
void Explosion::VOnUpdate(GameInfoPacket* pData){

}
