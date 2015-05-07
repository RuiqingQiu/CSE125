#pragma once
#ifndef GAME_OBJ_H
#define GAME_OBJ_H


#include <map>
#include <btBulletDynamicsCommon.h>
#include <vector>
#include "Constraint.h"
#include <iostream>
#include <time.h>

#define DEATH_DELAY 5

//block types
enum BLOCK_TYPE
{
	BASICCUBE = 0,
	GLOWINGCUBE = 1,
	WOODENCUBE = 2,
	METHCUBE = 3,
	BGUN = 4,
	MACE = 5,
	MALLET = 6,
	NEEDLE = 7,
	DISCOUNTWHEEL = 8,
	TIRE = 9,
	WOODENWHEEL = 10,

	BATTLEFIELD = 12,
	THREEBYTHREE_BASIC = 13,
	THREEBYTHREE_GLOWING = 14,
	THREEBYTHREE_WOODEN = 15,

	WALL = 101,
	BULLET_1 = 102,

};

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
	int _isWheel = 0;
	int _type;
	int _blockType;
	double _mass;
	int _isRobot = 0;
	int _collisionType;
	int _isWeapon = 0;
	int _weaponType =0;
	int _isRangedWeapon = 0;
	double _damage = 0;
	btRigidBody* rigidBody;
		//constraints
	int below_id = -1;
	int left_id = -1;
	int right_id = -1;
	int front_id = -1;
	int back_id = -1;
	int buildObj_id; //this is my id
	clock_t deathTimer;

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

	int getIsWheel();

	int getIsRangedWeapon();

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
	Constraint* addConstraint(GameObj*);
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