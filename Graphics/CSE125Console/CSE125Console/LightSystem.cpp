#include "stdafx.h"
#include "LightSystem.h"


LightSystem::LightSystem()
{
}


LightSystem::~LightSystem()
{
}
void LightSystem::addLight(Light* l){
	lights.push_back(l);
}

void LightSystem::setCameraOffset(float x, float y, float z){
	camera_offset.x = x;
	camera_offset.y = y;
	camera_offset.z = z;

}