#include "MeleeWeapon.h"

MeleeWeapon::MeleeWeapon(int type)
{

	double damage;
	double splash;
	_type = type;

	switch (type)
	{
	case NEEDLE:{
		damage = 1;
		splash = 1;
		break;
	}
	default:{
		damage = 3;
		splash = 2;
		break;
	}
	}

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



