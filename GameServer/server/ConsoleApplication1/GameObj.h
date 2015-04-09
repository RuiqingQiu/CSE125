#pragma once
class GameObj
{
private:
	double _x;
	double _y;
	double _z;
	double _qX;
	double _qY;
	double _qZ;
	double _qW;
	unsigned int _id;
	int _type;

public:
	GameObj();
	GameObj(double, double, double, double, double, double, double, int);
	~GameObj();

	double getX();
	double getY();
	double getZ();
	double getqX();
	double getqY();
	double getqZ();
	double getqW();
	int getType();
	unsigned int getId();

	void setX(double);
	void setY(double);
	void setZ(double);
	void setqX(double);
	void setqY(double);
	void setqZ(double);
	void setqW(double);
	void setType(int);
};

