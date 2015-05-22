#pragma once
#include "stdafx.h"
#include <vector>
#include "Light.h"

#ifndef __LightSystem__
#define __LightSystem__
#include "GameView.h"
class LightSystem
{
public:
	int num_of_lights = 6;
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

