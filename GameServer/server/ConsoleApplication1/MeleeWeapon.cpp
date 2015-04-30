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
	double attackSpeed;
	double splash;
	_type = type;
	g->setIsWeapon();

	switch (type)
	{
	case NEEDLE:{
		damage = 1;
		attackSpeed = 2;
		splash = 1;
		break;
	}
	default:{
		damage = 5;
		attackSpeed = 5;
		splash = 2;
		break;
	}
	}

	setDamage(damage);
	setAttackSpeed(attackSpeed);
	setSplash(splash);
	setRange(MELEE);
}


MeleeWeapon::~MeleeWeapon()
{
}



