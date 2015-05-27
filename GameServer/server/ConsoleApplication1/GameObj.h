#pragma once


#ifndef GAME_OBJ_H
#define GAME_OBJ_H



#include <map>
#include <btBulletDynamicsCommon.h>
#include <vector>
#include "Constraint.h"
#include <iostream>
#include <time.h>
#include "MeleeWeapon.h"
#include "RangedWeapon.h"
#include "Weapon.h"

#define DEATH_DELAY 15



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
	double speedMultiplier = 0;
	unsigned int _id;
	int _isWheel = 0;
	int _type;
	int _blockType;
	double _mass;
	int _isRobot = 0;
	int	_isRanged = 0;
	int _collisionType;
	double blockForce = 0;
	double blockHealing = 0;
	double blockSlow = 0;

	btRigidBody* rigidBody;
		//constraints
	int below_id = -1;
	int left_id = -1;
	int right_id = -1;
	int front_id = -1;
	int back_id = -1;
	int buildObj_id; //this is my id

	double DoT;
	double DoTTick;
	

	int DoTFrom = -1;

	clock_t deathTimer;

	GameObj* _belongTo;

	std::vector<Constraint *> constraints;

protected:
	double _health;
	double _maxHealth;
	int _isWeapon = 0;
	double _damage = 0;
	double _initForce;
	Weapon* weapon;

public:
	static unsigned int _totalId;
	int _deathSent;

	GameObj();

	// x, y, z, qX, qY, qZ, qW, type, mass
	GameObj(double, double, double, double, double, double, double, int, double);
	~GameObj();


	double getBlockForce();
	void setInitForce(double);
	double getInitForce();
	void setSpeedMultiplier(double);
	double getSpeedMultiplier();
	void addSpeedMultipler(double);
	void setLeftID(int);
	void setRightID(int);
	void setFrontID(int);
	void setBackID(int);
	void setBelowID(int);
	int getDoTFrom();
	double getHealing();
	double getSlow();

	double getDoT();

	virtual GameObj* shoot() = 0;

	int getIsWheel();
	void setImmediateDeleted();

	int getHasDeleted();
	int getIsRangedWeapon();

	int getLeftID();
	int getRightID();
	int getFrontID();
	int getBackID();
	int getBelowID();
	void setId(unsigned int i);
	

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
	Weapon* getWeapon();

	void setDamage(double);
	double getDamage();
	void addDoT(double d, int);
	int applyDotDamge();
	double getDoTTick();

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
	virtual void createRigidBody() = 0;// std::map< btCollisionObject*, GameObj*>*) = 0;
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
	int deleteConstraints();// std::map< btCollisionObject*, GameObj*>*);
	int deleteInvalidConstraints();
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


	void setWeapon(int meleeorranged, int weapontype);

};


#endif