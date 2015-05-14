#pragma once
#include "stdafx.h"
#include <vector>
#include "Light.h"

#ifndef __LightSystem__
#define __LightSystem__
class LightSystem
{
public:
	Vector3 camera_offset;
	vector<Light*> lights;
	void addLight(Light*);
	void setCameraOffset(float x, float y, float z);
	LightSystem();
	~LightSystem();
};
#endif

