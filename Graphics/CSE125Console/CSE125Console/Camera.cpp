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
	}
	else{
	}
	glRotatef(rotation->x, 1, 0, 0);
	glRotatef(rotation->y, 0, 1, 0);
	glRotatef(rotation->z, 0, 0, 1);
	glTranslatef(-position->x, -position->y, -position->z);
}


void  Camera::setUpCameraWithGL(float position_x, float position_y, float position_z, float lookAt_x, float lookAt_y, float lookAt_z){
	if (IsFollowingEnabled&&FollowingTarget != nullptr)
	{
		UpdateCamera();
	}
	else{
		printf("nah\n");
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
	Vector4 forward = Vector4(0, 0, -1, 1);
	Vector4 direction_temp = trans*forward;
	Vector3 direction = Vector3(direction_temp.get_x(), direction_temp.get_y(), direction_temp.get_z());
	direction.normalize();
	float distanceToPlayer = 15;
	Vector3* newposition = new Vector3(FollowingTarget->localTransform.position.x - direction.x*distanceToPlayer, FollowingTarget->localTransform.position.y - direction.y*distanceToPlayer, FollowingTarget->localTransform.position.z - direction.z*distanceToPlayer);
	Vector3* newrotation = new Vector3(-FollowingTarget->localTransform.rotation.x, -FollowingTarget->localTransform.rotation.y, -FollowingTarget->localTransform.rotation.z);
	*this->position = VectorLerp(position, newposition, 0.1);
	*this->rotation = VectorLerp(rotation, newrotation, 0.056);
}

Vector3 Camera::VectorLerp(Vector3* v1, Vector3* v2, float t)
{
	return Vector3(((1 - t)*v1->x + t*v2->x), ((1 - t)*v1->y + t*v2->y), ((1 - t)*v1->z + t*v2->z));
}
/*
Matrix4 Camera::GetCameraMatrix()
{
	Vector3 z = *e - *d;
	z.normalize();
	Vector3 x = (*up).cross(*up, z);
	x.normalize();
	Vector3 y = (*up).cross(z, x);
	y.normalize();
	Matrix4 C = Matrix4(x, y, z, *e);
	Matrix4 rotation = Matrix4();
	rotation.identity();
	for (int i = 0; i < 3; i++){
		for (int j = 0; j < 3; j++){
			rotation.m[i][j] = C.m[i][j];
		}
	}
	rotation.transpose();
	Matrix4 translation = Matrix4();
	translation.makeTranslate(-e->x, -e->y, -e->z);
	C = rotation * translation;
	//C.print("C matrix");
	return C;
	
	//Matrix4 ret = localTransform.GetGLMatrix4();
	//ret.transpose();
	//return ret;
	
}*/