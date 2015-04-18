#pragma once
#ifndef GAME_OBJ_H
#define GAME_OBJ_H



#include <btBulletDynamicsCommon.h>
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
	double _rotX;
	double _rotY;
	double _rotZ;
	unsigned int _id;
	int _type;
	int _blockType;
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
	int getBlockType();
	unsigned int getId();
	double getMass();
	btRigidBody* getRigidBody();
	double getRotX();
	double getRotY();
	double getRotZ();

	void setX(double);
	void setY(double);
	void setZ(double);
	void setqX(double);
	void setqY(double);
	void setqZ(double);
	void setqW(double);
	void setType(int);
	void setBlockType(int);
	void setMass(double);
	void setRigidBody(btRigidBody*);
	virtual void createRigidBody() = 0;
	void setRotX(double);
	void setRotY(double);
	void setRotZ(double);
	
};


#endif