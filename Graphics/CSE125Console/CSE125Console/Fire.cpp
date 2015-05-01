#include "stdafx.h"

#include "Fire.h"
#include "Window.h"

#ifdef __APPLE__
#include <GLUT/glut.h>
#else
#include <GL/glut.h>
#endif

#include "math.h"
#include "SOIL.h"
#include <ctime>

int const MAX=1000;

//int timeCount = 1;
//int timeToBurn = 500;
GLuint texture[1];
particles particle[MAX];

void Fire::LoadGLTextures()
{
	texture[0] = SOIL_load_OGL_texture
		(
		"Assets/Particles/particle.bmp",
		SOIL_LOAD_AUTO,
		SOIL_CREATE_NEW_ID,
		SOIL_FLAG_INVERT_Y
		);

	if (texture[0] == 0)
		cout << "Error loading fire texture" << endl;
	
	glBindTexture(GL_TEXTURE_2D, texture[0]);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
}

Fire::Fire(float x_pos, float y_pos, float z_pos)
{
	localTransform = Transform();
	x_origin = x_pos;
	y_origin = y_pos;
	z_origin = z_pos;

	this->size = size;
	//glutInitDisplayMode(GLUT_RGBA | GLUT_ALPHA | GLUT_DOUBLE | GLUT_DEPTH);
	initParticles();
	LoadGLTextures();
}

Fire::~Fire()
{
	//Delete any dynamically allocated memory/objects here
	delete texture;
}

void Fire::VOnUpdate(GameInfoPacket* pData)
{ }

void Fire::VOnClientUpdate(GameInfoPacket* pData){
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

void Fire::VOnDraw()
{
	srand(time(NULL));
	//if (timeCount >= timeToBurn)
		//return;

	glEnable(GL_TEXTURE_2D);							// Enable Texture Mapping ( NEW )
	glDisable(GL_DEPTH_TEST);                       // Disables Depth Testing
	glEnable(GL_BLEND);                         // Enable Blending
	glBlendFunc(GL_SRC_ALPHA, GL_ONE);                   // Type Of Blending To Perform
	glBindTexture(GL_TEXTURE_2D, texture[0]);
	
	for (int loop = 0; loop < MAX; loop++)                   // Loop Through All The Particles
	{
		p = particle[loop];

		if (particle[loop].alive)                  // If The Particle Is Active
		{
			float r = p.r;
			float g = p.g;
			float b = p.b;

			float x = p.x;
			float y = p.y;
			float z = p.z;

			//glColor4f(r, g, b, particle[loop].life / 5 * 30.0f/timeCount );
			glColor4f(r, g, b, particle[loop].life / 5 );

			//float split = rand() % 2 - rand() % 2;
		    float split = 0;

			glBegin(GL_TRIANGLE_STRIP);
			glTexCoord2d(1, 1); glVertex3f(x + 0.4f + split, y + 0.4f, z ); // Top Right
			glTexCoord2d(0, 1); glVertex3f(x - 0.4f + split, y + 0.4f, z ); // Top Left
			glTexCoord2d(1, 0); glVertex3f(x + 0.4f + split, y - 0.4f, z ); // Bottom Right
			glTexCoord2d(0, 0); glVertex3f(x - 0.4f + split, y - 0.4f, z ); // Bottom Left
			glEnd();

			glBegin(GL_TRIANGLE_STRIP);
			glTexCoord2d(1, 1); glVertex3f(x + 0.4f + split, y, z + 0.4f); // Top Right
			glTexCoord2d(0, 1); glVertex3f(x - 0.4f + split, y , z + 0.4f); // Top Left
			glTexCoord2d(1, 0); glVertex3f(x + 0.4f + split, y , z - 0.4f); // Bottom Right
			glTexCoord2d(0, 0); glVertex3f(x - 0.4f + split, y , z - 0.4f); // Bottom Left
			glEnd();

			particle[loop].x += 0.0075f  * float(rand() % 5 + 1) * p.life / 5.0f;
			particle[loop].x -= 0.0075f  * float(rand() % 5 + 1) * p.life / 5.0f;
			//particle[loop].y += 0.00055f * (float(rand() % 100 + 1) * 100.0f/timeCount );
			particle[loop].y += 0.00055f * (float(rand() % 100 + 1) );

			particle[loop].r += 0.0002f * float(rand() % 100);
			particle[loop].g += 0.0001f * float(rand() % 30);

			particle[loop].life -= particle[loop].fade;
			if (particle[loop].life <= 0.0f)
				particle[loop].alive = false;

		}
		else
			initParticle(loop);	
	}
	glBindTexture(GL_TEXTURE_2D, GL_TEXTURE0);
	glEnable(GL_DEPTH_TEST);                       // Disables Depth Testing
	glDisable(GL_BLEND);
	//timeCount++;
}


void Fire::initParticles()
{
	for (int loop = 0; loop < MAX; loop++)                   // Initialize All The Textures
		initParticle(loop);
}

void Fire::initParticle(int loop)
{
	particle[loop].alive = true;                 // Make All The Particles Active
	particle[loop].life = 4.5f;                   // Give All The Particles Full Life

	particle[loop].x = x_origin;
	particle[loop].y = y_origin;
	particle[loop].z = z_origin;

	particle[loop].fade = float(rand() % 100) / 1000.0f + 0.05f;   // Random Fade Speed
	particle[loop].r = 0.35f;        
	particle[loop].g = 0.3f;      
	particle[loop].b = 0.2f;
}