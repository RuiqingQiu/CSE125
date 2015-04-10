#pragma once
#include <btBulletDynamicsCommon.h>
#include "definition.h"
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
	double _mass;
	btRigidBody* rigidBody;

public:
	GameObj();

	// x, y, z, qX, qY, qZ, qW, type, mass
	GameObj(double, double, double, double, double, double, double, int, double);
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
	double getMass();
	btRigidBody* getRigidBody();

	void setX(double);
	void setY(double);
	void setZ(double);
	void setqX(double);
	void setqY(double);
	void setqZ(double);
	void setqW(double);
	void setType(int);
	void setMass(double);
	void setRigidBody(btRigidBody*);
	virtual void createRigidBody() = 0;
	
};

