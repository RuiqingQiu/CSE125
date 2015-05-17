#include "RangedWeapon.h"
#include <iostream>


RangedWeapon::RangedWeapon(int type)
{
	_type = type;
	lastShot = clock();

	int range;
	double damage;
	double attackSpeed;
	double splash;


	switch (type)
	{
	case BGUN:
	{
		range = MEDIUM_RANGED;
		damage = 15;
		attackSpeed = 4;
		splash = 1;

		_pInitForce = -300;
		_pMass = 1;
		_pWidth = 0.3;
		_pHeight = 0.3;
		_pDepth = 0.5;
		_pBlockType = 103;
		break;
	}
	default:
	{
		range = FAR_RANGED;
		damage = 30;
		attackSpeed = 0.5;
		splash = 4;

		_pInitForce = -600;
		_pMass = 10;
		_pWidth = 0.3;
		_pHeight = 0.3;
		_pDepth = 1;
		_pBlockType = MACE;
		break;
	}
	}

	setRange(range);
	setDamage(damage);
	setAttackSpeed(attackSpeed);
	setSplash(splash);

}

double RangedWeapon::getPInitForce()
{
	return _pInitForce;
}
double RangedWeapon::getPMass()
{
	return _pMass;
}
double RangedWeapon::getPWidth()
{
	return _pWidth;
}
double RangedWeapon::getPHeight()
{
	return _pHeight;
}
double RangedWeapon::getPDepth()
{
	return _pDepth;
}
int RangedWeapon::getPBlockType()
{
	return _pBlockType;
}


RangedWeapon::~RangedWeapon()
{
}

void RangedWeapon::setAttackSpeed(double a)
{
	_attackSpeed = a;
}

double RangedWeapon::getAttackSpeed(){
	return _attackSpeed;
}


int RangedWeapon::readyToShoot()
{
	double diff = ((double)(clock() - lastShot)/CLOCKS_PER_SEC);
	if (diff > 1/_attackSpeed)
	{
		//std::cout << "Time elasped: " << diff << std::endl;
		return 1;
	}
	else
	{
		return 0;
	}
}

void RangedWeapon::setLastShot()
{
	double diff = ((double)(clock() - lastShot) / CLOCKS_PER_SEC);
	
	lastShot = clock();
}

