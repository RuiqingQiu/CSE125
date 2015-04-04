#include "stdafx.h"
#include "Vector3.h"
#include "Matrix4.h"
#ifndef CSE125Transform
#define CSE125Transform

class Transform
{
public:
	Transform();
	~Transform();
	Vector3 position;
	Vector3 rotation;
	Vector3 scale;

	Matrix4 GetGLMatrix4();
};

#endif