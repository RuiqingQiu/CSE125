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
	case Railgun:
	{
		//range = FAR_RANGED;
		//damage = 60;
		//attackSpeed = 1.5;
		//splash = 1;

		//_pInitForce = -400;
		//_pMass = 2;
		//_pWidth = 0.3;
		//_pHeight = 0.3;
		//_pDepth = 1;
		_pBlockType =  BULLET;

				   range = FAR_RANGED;
				   damage = 100;
				   attackSpeed = 0.5;
				   splash = 4;

				   _pInitForce = -15000;
				   _pMass = 200;
				   _pWidth = .8;
				   _pHeight = .8;
				   _pDepth = .8;
		break;
	}
	case BGun:
	{
				 range = MEDIUM_RANGED;
				 damage = 10;
				 attackSpeed = 0.5;
				 splash = 1;

				 _pInitForce = -185;
				 _pMass = 0.8;
				 _pWidth = 0.2;
				 _pHeight = 0.2;
				 _pDepth = 0.5;
				 _pBlockType = BULLET;
				 break;
	}
	//case Cannon:
	//{

	//		   range = FAR_RANGED;
	//		   damage = 300;
	//		   attackSpeed = 0.5;
	//		   splash = 4;

	//		   _pInitForce = -3000;
	//		   _pMass = 20;
	//		   _pWidth = .8;
	//		   _pHeight = .8;
	//		   _pDepth = .8;
	//		   _pBlockType = Cannon_Ball;
	//		   break;
	//
	//}
	default:
	{
		range = FAR_RANGED;
		damage = 60;
		attackSpeed = 1;
		splash = 4;

		_pInitForce = -100;
		_pMass = 10;
		_pWidth = 0.3;
		_pHeight = 0.3;
		_pDepth = 1;
		_pBlockType = BULLET;
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

