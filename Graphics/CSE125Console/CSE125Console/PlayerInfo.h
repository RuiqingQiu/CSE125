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
	float mat[16];
	bool processed = false;
	void print();
	PlayerInfo();
	~PlayerInfo();
};

