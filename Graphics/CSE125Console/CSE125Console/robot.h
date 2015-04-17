#pragma once

//#include <GL\glut.h>
#include "block.h"

#define MAX_ROBO_SIZE 9

class robot {

public:
	robot();
	~robot();

	void draw();

	block * selected;

private:
	block * root;

	Matrix4 * localMtx;
	Matrix4 * rotateX;
	Matrix4 * rotateY;
	Matrix4 * rotateZ;

	vector<block *> blocks;
};

