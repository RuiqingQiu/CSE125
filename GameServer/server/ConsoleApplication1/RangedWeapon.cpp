#include "RangedWeapon.h"


RangedWeapon::RangedWeapon(int type, GameObj* g)
{
	setGameObj(g);
	g->setIsWeapon();
	_type = type;

	int range;
	double damage;
	double attackSpeed;
	double splash;


	switch (type)
	{
	case GUN:
	{
		range = MEDIUM_RANGED;
		damage = 1;
		attackSpeed = 10;
		splash = 1;

		_pInitForce = -200;
		_pMass = 1;
		_pWidth = 0.3;
		_pHeight =0.3;
		_pDepth =0.5;
		_pBlockType = NEEDLE;
		break;
	}
	default:
	{
		range = FAR_RANGED;
		damage = 10;
		attackSpeed = 2;
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
