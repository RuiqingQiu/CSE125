#include "MeleeWeapon.h"
enum MELEE_TYPES{
	NEEDLE = 0,
	MACE = 1,
	HAMMER = 2,
};

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
		damage = 5;
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



