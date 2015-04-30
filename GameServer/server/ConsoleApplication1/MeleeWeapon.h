#pragma once
#include "Weapon.h"

class MeleeWeapon:public Weapon
{
public:
	MeleeWeapon(int, GameObj*);
	~MeleeWeapon();
};

