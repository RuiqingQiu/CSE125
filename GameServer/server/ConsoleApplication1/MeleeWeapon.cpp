#include "MeleeWeapon.h"

MeleeWeapon::MeleeWeapon(int type)
{

	double damage;
	double splash;
	double knockback;
	double spin;
	_type = type;

	switch (type)
	{
	case Needle:{
		damage = 2;
		splash = 1;
		knockback = 0;
		spin = 0;
		break;
	}
	case Mace:{
		knockback = 0;
		damage = 75;
		splash = 1;
		spin = 250;
		break;
	}
	case Mallet:
	{
				   spin = 0;
				   knockback = 350;
				   damage = 100;
				   splash = 2;
				   break;
	}
	default:
	{
			   damage = 0;
			   splash = 0;
			   knockback = 0;
			   spin = 0;
			   break;
	}
	}
	setSpin(spin);
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

void MeleeWeapon::setSpin(double s)
{
	spin = s;
}
double MeleeWeapon::getSpin()
{
	return spin;
}