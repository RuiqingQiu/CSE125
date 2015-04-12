#pragma once

#include "stdafx.h"
#include "Transform.h"
#include <GL/glut.h>

class Camera
{
private:
	

	
public:
	//Center of the projection
	Vector3 *position = new Vector3(0, 0, -10);
	Vector3 *rotation = new Vector3(0, 0, 0);
	Vector3 *lookat = new Vector3(0, 0, - 1);
	/*
	Vector3 *e = new Vector3(0, 0, -10);
	//Look at vector
	Vector3 *d = new Vector3(0, 0, 0);
	//Up vector
	Vector3 *up = new Vector3(0, 1, 0);*/
	//Transform localTransform;
	//Matrix4 GetCameraMatrix();
	void setCameraPosition(double x, double y, double z);
	void setCameraRotation(double angle, const Vector3& axis);
	Camera();
	~Camera();
	void setUpCamera();
};




