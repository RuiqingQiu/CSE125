#pragma once
class GameObj
{

	double _x;
	double _y;
	double _z;
	unsigned int _id;

public:
	GameObj();
	GameObj(double, double, double);
	~GameObj();

	double getX();
	double getY();
	double getZ();
	unsigned int getId();

	void setX(double);
	void setY(double);
	void setZ(double);
};

