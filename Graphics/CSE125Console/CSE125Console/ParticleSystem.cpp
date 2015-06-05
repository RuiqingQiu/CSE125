#include "stdafx.h"
#include "ParticleSystem.h"
#ifdef __APPLE__
#include <GLUT/glut.h>
#else
#include <GL/glut.h>
#endif

ParticleSystem::ParticleSystem()
{
	LoadGLTextures();
	startTime = clock();
	lastTime = startTime;
	isDead = false;
}


ParticleSystem::~ParticleSystem()
{
}

void ParticleSystem::LoadGLTextures()
{
	TextureGluint = SOIL_load_OGL_texture
		(
		"Assets/Particles/smoke2.tga",
		//"Assets/Particles/smoke2.jpg",
		SOIL_LOAD_AUTO,
		SOIL_CREATE_NEW_ID,
		SOIL_FLAG_INVERT_Y
		);

	if (TextureGluint == 0)
		cout << "Error loading fire texture" << endl;
	/*
	glBindTexture(GL_TEXTURE_2D, TextureGluint);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	*/
}

void ParticleSystem::VOnUpdate(GameInfoPacket* pData)
{ }

void ParticleSystem::VOnClientUpdate(GameInfoPacket* pData){

}

void ParticleSystem::VOnDraw()
{
	printf("init life time %f\n", lifeTime);

	float currentTime = clock();
	float seconds = (currentTime - startTime) / CLOCKS_PER_SEC;
	float deltatime = (currentTime - lastTime) / CLOCKS_PER_SEC;
	lastTime = currentTime;
	//begin to draw
	srand(time(NULL));
	//if (timeCount >= timeToBurn)
	//return;

	glDisable(GL_DEPTH_TEST);                       // Disables Depth Testing
	glEnable(GL_TEXTURE_2D);
	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, TextureGluint);
	glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_MODULATE);
	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

	glBegin(GL_QUADS);
	for (int loop = 0; loop < maxParticles; loop++)
	{
		if (particle[loop].alive)                  // If The Particle Is Active
		{
			
			particles p = particle[loop];
			/*
			float deltaPos = deltatime*p.speed;
			Vector4 currentpos = Vector4(p.x, p.y, p.z,1);
			Matrix4 transforward = Matrix4();
			Matrix4 rotateX = Matrix4();
			Matrix4 rotateY = Matrix4();
			Matrix4 rotateZ = Matrix4();

			transforward.makeTranslate(0, deltaPos, 0);
			rotateX.makeRotateX(p.rx);
			rotateY.makeRotateX(p.ry);
			rotateZ.makeRotateX(p.rz);
			Vector4 nextpos = transforward*rotateZ*rotateY*rotateX *Vector4(0,0,0,1) + currentpos;
			p.x = nextpos.x;
			p.y = nextpos.y;
			p.z = nextpos.z;

			p.rx = (rand() % 100)*0.01 * 30 - 15;
			p.rz = (rand() % 100)*0.01 * 30 - 15;
			*/

			float x = p.x;
			float y = p.y;
			float z = p.z;
			glColor4f(p.r, p.g, p.b, max(0.0,1 - log10(((pduration-p.life) / pduration) * 10)));
			float sx = max(0.0,log10((1 - p.life / pduration) * 10)*p.sx);
			float sy = max(0.0,log10((1 - p.life / pduration) * 10)*p.sy);
			float sz = max(0.0,log10((1 - p.life / pduration) * 10)*p.sz);

			glTexCoord2d(0, 0); glVertex3f(x - sx, y - sy, z); // Top Right
			glTexCoord2d(1, 0); glVertex3f(x + sx, y - sy, z); // Top Left
			glTexCoord2d(1, 1); glVertex3f(x + sx, y + sy, z); // Bottom Right
			glTexCoord2d(0, 1); glVertex3f(x - sx, y + sy, z); // Bottom Left
			//glEnd();

			//glBegin(GL_TRIANGLE_STRIP);
			glTexCoord2d(0, 0); glVertex3f(x  , y - sy, z - sz); // Top Right
			glTexCoord2d(1, 0); glVertex3f(x  , y - sy, z + sz); // Top Left
			glTexCoord2d(1, 1); glVertex3f(x  , y + sy, z + sz); // Bottom Right
			glTexCoord2d(0, 1); glVertex3f(x  , y + sy, z - sz); // Bottom Left

			particle[loop].x += 0.0075f  * float(rand() % 5 + 1) * p.life / 5.0f;
			particle[loop].x -= 0.0075f  * float(rand() % 5 + 1) * p.life / 5.0f;
			//particle[loop].y += 0.00055f * (float(rand() % 100 + 1) * 100.0f/timeCount );
			particle[loop].y += 0.00055f * (float(rand() % 100 + 1));

			//particle[loop].r += 0.0002f * float(rand() % 100);
			//particle[loop].g += 0.0001f * float(rand() % 30);

			particle[loop].life -= deltatime;
			if (particle[loop].life <= 0.0f)
				particle[loop].alive = false;
		}
		else{
			float rate = rand() % 100 * 0.01;
			if (rate < pemissionRate){
				initParticle(loop);
			}
		}

	}
	glEnd();

	glBindTexture(GL_TEXTURE_2D, GL_TEXTURE0);
	glEnable(GL_DEPTH_TEST);                       // Disables Depth Testing
	glDisable(GL_BLEND);

	if (seconds>lifeTime)
	{
		isDead = true;
	}
}

void ParticleSystem::initParticles()
{
	for (int loop = 0; loop < maxParticles; loop++)                   // Initialize All The Textures
	{
		float rate = rand() % 100 * 0.01;
		if (rate < pemissionRate){
			initParticle(loop);
		}
	}
}

void ParticleSystem::initParticle(int loop)
{
	particle[loop].alive = true;                 // Make All The Particles Active
	particle[loop].life = pduration;                   // Give All The Particles Full Life
	
	switch (spawnShape)
	{
	case Cylinder:
	{
					 float x = float(rand() % 100) / 100.0f * cylinderRadius - cylinderRadius*0.5;
					 float z = float(rand() % 100) / 100.0f * cylinderRadius - cylinderRadius*0.5;
					 if ((x*x + z*z) < cylinderRadius*cylinderRadius){
						 particle[loop].x = x;
						 particle[loop].y = 0;
						 particle[loop].z = z;
					 }
					 else{
						// initParticle(loop);
						// return;
					 }
	}
		break;
	case None:
	{
					particle[loop].x = 0;
					particle[loop].y = 0;
					particle[loop].z = 0;
	}
		break;
	default:
		break;
	}
	

	particle[loop].alpha = 1;
	
	particle[loop].r = startColor.x;
	particle[loop].g = startColor.y;
	particle[loop].b = startColor.z;

	particle[loop].sx = 1;
	particle[loop].sy = 1;
	particle[loop].sz = 1;

	particle[loop].rx = 0;
	particle[loop].ry = 0;
	particle[loop].rz = 0;

	particle[loop].speed = 1.0;

}