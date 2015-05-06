#pragma once
#ifndef GAME_OBJ_H
#define GAME_OBJ_H


#include <map>
#include <btBulletDynamicsCommon.h>
#include <vector>
#include "Constraint.h"


// collision type
enum COLLISION_TYPE{
	C_WALLS = 0,
	C_GROUND = 1,
	C_ROBOT = 2,
	C_ROBOT_PARTS = 3,
	C_PROJECTILE = 4,
	C_MELEE = 5,

};

// GameObj (physical) types
enum OBJECT_TYPE
{
	PLANE = 0,
	TRIANGLE = 1,
	CAPSULE = 2,
	CONE = 3,
	CYLINDER = 4,
	BOX = 5,
	CLOUD = 6,
};

class GameObj
{

private:
	int deleted;
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
	int _isRobot;
	int _collisionType;
	int _isWeapon;
	double _damage = 0;
	btRigidBody* rigidBody;
		//constraints
		int below_id;
	int left_id;
	int right_id;
	int front_id;
	int back_id;
	int buildObj_id; //this is my id
		
	GameObj* _belongTo;

	std::vector<Constraint *> constraints;

protected:
	double _health;
	double _maxHealth;

public:
	static unsigned int _totalId;

	GameObj();

	// x, y, z, qX, qY, qZ, qW, type, mass
	GameObj(double, double, double, double, double, double, double, int, double);
	~GameObj();


	void setLeftID(int);
	void setRightID(int);
	void setFrontID(int);
	void setBackID(int);
	void setBelowID(int);


	int getLeftID();
	int getRightID();
	int getFrontID();
	int getBackID();
	int getBelowID();


	void setBuildID(int);


	int getBuildID();

	double getX();
	double getY();
	double getZ();
	double getqX();
	double getqY();
	double getqZ();
	double getqW();
	int getType(); // Physics world
	int getBlockType(); // Client world type
	unsigned int getId();
	double getMass();
	virtual btRigidBody* getRigidBody() = 0;
	double getRotX();
	double getRotY();
	double getRotZ();

	void setDamage(double);
	double getDamage();

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
	btRigidBody* getRB();
	virtual void createRigidBody(std::map< btCollisionObject*, GameObj*>*) = 0;
	void setRotX(double);
	void setRotY(double);
	void setRotZ(double);
	void setIsRobot(int);
	int getIsRobot();

	void setCollisionType(int);
	int getCollisionType();

	void setBelongTo(GameObj*);
	GameObj* getBelongTo();
	void addConstraint(GameObj*);
	void deleteConstraints(std::map< btCollisionObject*, GameObj*>*);
	void deleteInvalidConstraints();
	std::vector<Constraint *>* getConstraints();

	static int getOid(){ return _totalId; }

	void incOid(int i){ _totalId += i; }
	void setDeleted();
	int getDeleted();
	int getIsWeapon();
	void setIsWeapon();

	void setHealth(double);
	void setMaxHealth(double);
	double getHealth();
	double getMaxHealth();

	double applyDamage(double);

};


#endif