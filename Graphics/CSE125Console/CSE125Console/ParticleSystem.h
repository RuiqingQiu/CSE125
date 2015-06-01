#pragma once
#include "stdafx.h"
#include "GeoNode.h"
#include "math.h"
#include "SOIL.h"
#include <ctime>
#include "Particles.h"
#include "Vector3.h"
#include "Window.h"
#include "Matrix4.h"

enum ParticleInitShape
{
	Cylinder,
	None
};
enum ParticleSize
{
	ParticleSizeConstant=0,
	DecreaseLinear=1,
	DecreaseNoneLinear=2
};
enum ParticleScale
{
	ParticleScaleConstant=0,
	IncreaseLinear=1,
	IncreaseNoneLinear=2
};
class ParticleSystem : public GeoNode
{
public:
	ParticleSystem();
	~ParticleSystem();
	ParticleInitShape spawnShape;
	ParticleScale scaleFunc;
	ParticleSize sizeFunc;
	float lifeTime = 5;
	float pduration = 5;
	float pemissionRate = 1;
	float pgravityModifier = 1;
	int maxParticles = 75;
	GLuint TextureGluint;
	float cylinderRadius = 5;
	Vector3 startColor = Vector3(1, 1, 1);
	float startTime;
	float lastTime;
	void LoadGLTextures();
	virtual void VOnClientUpdate(GameInfoPacket* pData);
	virtual void VOnDraw();
	virtual void VOnUpdate(GameInfoPacket* pData);
	void initParticles();
	void initParticle(int loop);
private:
	particles particle[1000];
};

