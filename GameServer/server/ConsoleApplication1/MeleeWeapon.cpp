#include "MeleeWeapon.h"

MeleeWeapon::MeleeWeapon(int type, GameObj* g)
{
	setGameObj(g);
	double damage;
	double splash;
	_type = type;
	g->setIsWeapon();

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
	g->setDamage(damage);
}


MeleeWeapon::~MeleeWeapon()
{
}



