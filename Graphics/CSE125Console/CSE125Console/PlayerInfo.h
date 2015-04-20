#pragma once
#include <iostream>
class PlayerInfo
{
public:
	//unique id
	int id;

	//locations
	double x;
	double y;
	double z;

	//Rotation
	double rx;
	double ry;
	double rz;

	//Type of the block
	int type;

	float mat[16];
	bool processed = false;
	void print();
	PlayerInfo();
	~PlayerInfo();
};

