#include "stdafx.h"
#include "Transform.h"

Transform::Transform()
{
	position = Vector3(0, 0, 0);
	rotation = Vector3(0, 0, 0);
	scale = Vector3(1, 1, 1);
}

Transform::~Transform()
{

}

Matrix4 Transform::GetGLMatrix4()
{
//	printf("pos %f %f %f\n", position.x,position.y,position.z);

	Matrix4 ret;
	ret.identity();

	Matrix4 m4_pos;
	m4_pos.makeTranslate(position.x, position.y, position.z);

	Matrix4 m4_rotx;
	m4_rotx.makeRotateX(rotation.x);

	Matrix4 m4_roty;
	m4_roty.makeRotateY(rotation.y);

	Matrix4 m4_rotz;
	m4_rotz.makeRotateZ(rotation.z);

	Matrix4 m4_rot;
	m4_rot = m4_rotx*m4_roty*m4_rotz;

	Matrix4 m4_sca;
	m4_sca.makeScale(scale.x, scale.y, scale.z);

	ret = ret*m4_pos*m4_rot*m4_sca;
	ret.transpose();

	return ret;
}

Matrix4 Transform::GetMatrix4()
{
	//	printf("pos %f %f %f\n", position.x,position.y,position.z);

	Matrix4 ret;
	ret.identity();

	Matrix4 m4_pos;
	m4_pos.makeTranslate(position.x, position.y, position.z);

	Matrix4 m4_rotx;
	m4_rotx.makeRotateX(rotation.x);

	Matrix4 m4_roty;
	m4_roty.makeRotateY(rotation.y);

	Matrix4 m4_rotz;
	m4_rotz.makeRotateZ(rotation.z);

	Matrix4 m4_rot;
	m4_rot = m4_rotx*m4_roty*m4_rotz;

	Matrix4 m4_sca;
	m4_sca.makeScale(scale.x, scale.y, scale.z);

	ret = ret*m4_pos*m4_rot*m4_sca;
	//ret.transpose();

	return ret;
}