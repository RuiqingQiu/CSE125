#include "stdafx.h"
#include "Camera.h"
#include <math.h>
Camera::Camera()
{
	//localTransform = Transform();
	//localTransform.position = Vector3(1, 1, 0);
	IsFollowingEnabled = true;
}


Camera::~Camera()
{
}

void Camera::setUpCamera(){
	if (IsFollowingEnabled&&FollowingTarget != nullptr)
	{
		UpdateCamera();
		//printf("Euler Angle for camera:  %f %f %f\n", rotation->x, rotation->y, rotation->z);

	}
	else{
	}
	glRotatef(rotation->x, 1, 0, 0);
	glRotatef(rotation->y, 0, 1, 0);
	glRotatef(rotation->z, 0, 0, 1);
	glTranslatef(position->x, position->y, position->z);
}


void  Camera::setUpCameraWithGL(float position_x, float position_y, float position_z, float lookAt_x, float lookAt_y, float lookAt_z){
	if (IsFollowingEnabled&&FollowingTarget != nullptr)
	{
		UpdateCamera();

	}
	else{
	}
	/*
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluPerspective(60, width / height, 10, 40000);*/
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	gluLookAt(position_x, position_y, position_z, lookAt_x, lookAt_y, lookAt_z, 0, 1, 0);
}

void Camera::UpdateCamera()
{
	Matrix4 trans = FollowingTarget->localTransform.GetRotMatrix4();
	Vector4 forward = Vector4(0, 0, -1, 0);
	Vector4 direction_temp = trans*forward;
	Vector3 direction = Vector3(direction_temp.get_x(), direction_temp.get_y(), direction_temp.get_z());
	//direction.y = 0;
	direction.normalize();
	float distanceToPlayer = 15;
	Vector3* newposition = new Vector3(FollowingTarget->localTransform.position.x - direction.x*distanceToPlayer, FollowingTarget->localTransform.position.y - direction.y*distanceToPlayer + 10, FollowingTarget->localTransform.position.z - direction.z*distanceToPlayer);
	Vector3* newrotation = new Vector3(FollowingTarget->localTransform.rotation.x, FollowingTarget->localTransform.rotation.y, FollowingTarget->localTransform.rotation.z);//FollowingTarget->localTransform.rotation.z);

	this->position->negate();
	this->rotation->negate();

	*this->position = VectorLerp(position, newposition, 0.05, false);
	*this->rotation = VectorLerp(rotation, newrotation, 0.1, true);

	this->position->negate();
	this->rotation->negate();
	//newposition->negate();
	//newrotation->negate();
}


float mymode(float a, float b)
{
	float ret = fmod(a, b);
	if (ret < 0)
	{
		ret = -ret;
	}

	return ret;
}


Vector3 Camera::VectorLerp(Vector3* v1, Vector3* v2, float t, bool isangle)
{

	float v1x = fmod(v1->x, 360); //((int)v1->x) % 360;
	float v1y = fmod(v1->y, 360); //((int)v1->y) % 360;
	float v1z = fmod(v1->z, 360); //((int)v1->z) % 360;

	float v2x = fmod(v2->x, 360); //((int)v2->x) % 360;
	float v2y = fmod(v2->y, 360); //((int)v2->y) % 360;
	float v2z = fmod(v2->z, 360); //((int)v2->z) % 360;

	while (v1x < 0){
		v1x = v1x + 360;
	}
	while (v1x >= 360)
	{
		v1x = v1x - 360;
	}

	while (v1y < 0){
		v1y = v1y + 360;
	}
	while (v1y >= 360)
	{
		v1y = v1y - 360;
	}

	while (v1z < 0){
		v1z = v1z + 360;
	}
	while (v1z >= 360)
	{
		v1z = v1z - 360;
	}

	while (v2x < 0){
		v2x = v2x + 360;
	}
	while (v2x >= 360)
	{
		v2x = v2x - 360;
	}

	while (v2y < 0){
		v2y = v2y + 360;
	}
	while (v2y >= 360)
	{
		v2y = v2y - 360;
	}

	while (v2z < 0){
		v2z = v2z + 360;
	}
	while (v2z >= 360)
	{
		v2z = v2z - 360;
	}
	/*
	float v1x = fmod(v1->x, 1000); //((int)v1->x) % 360;
	float v1y = fmod(v1->y, 1000); //((int)v1->y) % 360;
	float v1z = fmod(v2->z, 1000); //((int)v1->z) % 360;
	float v2x = fmod(v2->x, 1000); //((int)v2->x) % 360;
	float v2y = fmod(v2->y, 1000); //((int)v2->y) % 360;
	float v2z = fmod(v2->z, 1000); //((int)v2->z) % 360;
	*/
	if (!isangle)
	{
		return Vector3(((1 - t)*v1->x + t*v2->x), ((1 - t)*v1->y + t*v2->y), ((1 - t)*v1->z + t*v2->z));
	}

	float retx, rety, retz;

	if (mymode(v2x - v1x, 360) < 180)
	{
		retx = ((1 - t)*v1x + t*v2x);
	}
	else{
		if (v2x>v1x){
			retx = ((1 - t)*(v1x + 360) + t*(v2x));

		}
		else{
			retx = ((1 - t)*v1x + t*(v2x + 360));

		}
	}


	if (mymode(v2y - v1y, 360) < 180)
	{
		rety = ((1 - t)*v1y + t*v2y);
	}
	else{
		if (v2y>v1y){
			rety = ((1 - t)*(v1y + 360) + t*(v2y));

		}
		else{
			rety = ((1 - t)*v1y + t*(v2y + 360));

		}
	}


	if (mymode(v2z - v1z, 360) < 180)
	{
		retz = ((1 - t)*v1z + t*v2z);

		//printf("camera: %f %f %f\n",v1z,v2z, retz);

	}
	else{
		if (v2z>v1z){
			retz = ((1 - t)*(v1z + 360) + t*(v2z));

		}
		else{
			retz = ((1 - t)*v1z + t*(v2z + 360));

		}
	}



	float rangeZero = 360;


	if (retx >= 0 && retx < 360)
	{
		retx = retx;
	}
	else{
		while (retx < 0){
			retx = retx + 360;
		}
		while (retx >= 360)
		{
			retx = retx - 360;
		}
	}

	if (rety >= 0 && rety < 360)
	{
		rety = rety;
	}
	else{
		while (rety < 0)
		{
			rety = rety + 360;
		}
		while (rety >= 360)
		{
			rety = rety - 360;
		}
	}

	if (retz >= 0 && retz < 360)
	{
		retz = retz;
	}else{
		while (retz < 0)
		{
			retz = retz + 360;
		}
		while (retz >= 360)
		{
			retz = retz - 360;
		}
	}


	return Vector3(retx, rety, retz);
}