#pragma once
#include "stdafx.h"
#include <vector>
#include "Light.h"

#ifndef __LightSystem__
#define __LightSystem__
#include "GameView.h"
//This is a counter for light transition
#define MAXCOUNTER 5000
class LightSystem
{
public:
	int num_of_lights = 6;
	int counter = 0;
	Vector3 camera_offset;
	vector<Light*> lights;
	void addLight(Light*);
	void setCameraOffset(float x, float y, float z);

	void initLights();
	void renderLights(GameView* view);
	void passUniform(GLuint);
	LightSystem();
	~LightSystem();
};
#endif

