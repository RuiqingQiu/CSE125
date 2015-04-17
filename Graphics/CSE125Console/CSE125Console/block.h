#pragma once

#include "GeoNode.h"

enum class blockType {
	BLOCK,
	WEAPON,
	WHEEL
};

class block : public GeoNode {
public:
	block();
	~block();

	//draw based on parent matrix
	void draw(Matrix4 mtx);

private:
	//moving the block
	Vector3 offset;
	Matrix4 rotateX;
	Matrix4 rotateY;
	Matrix4 rotateZ;

	//attributes
	blockType myType;
	double weight;
	double speed;
	//obj object;
	//mtl texture;

};

