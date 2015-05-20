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
		damage = 2;
		splash = 1;
		knockback = 0;
		break;
	}
	default:{
		knockback = 350;
		damage = 100;
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