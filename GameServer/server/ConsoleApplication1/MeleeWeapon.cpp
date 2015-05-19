#include "MeleeWeapon.h"

MeleeWeapon::MeleeWeapon(int type)
{

	double damage;
	double splash;
	double knockback;
	_type = type;

	switch (type)
	{
	case Needle:{
		damage = .5;
		splash = 1;
		knockback = 0;
		break;
	}
	default:{
		knockback = 50;
		damage = 1000;
		splash = 2;
		break;
	}
	}
	setKnockback(knockback);
	setDamage(damage);
	setSplash(splash);
	setRange(MELEE);
}


MeleeWeapon::~MeleeWeapon()
{
}

//GameObj* MeleeWeapon::shoot(btTransform * trans)
//{
//	return nullptr;
//}



void MeleeWeapon::setKnockback(double d)
{
	knockback = d;
}
double MeleeWeapon::getKnockback()
{
	return knockback;
}