#pragma once
#include "Weapon.h"
#include "GOBox.h"
#include "definition.h"
#include <time.h>

enum RANGED_TYPES{
	GUN = 0,
	LASER = 1,
	ROCKET = 2,
};
class RangedWeapon:public Weapon
{
private:
	clock_t lastShot;
	double _attackSpeed;
	double _pInitForce;
	double _pMass;
	double _pWidth;
	double _pHeight;
	double _pDepth;
	int _pBlockType;
	double time;

public:
	RangedWeapon(int, GameObj*);
	~RangedWeapon();

	void setAttackSpeed(double);
	double getAttackSpeed();
	double getPInitForce();
	double getPMass();
	double getPWidth();
	double getPHeight();
	double getPDepth();
	int getPBlockType();
	int readyToShoot();
	void setLastShot();
};


