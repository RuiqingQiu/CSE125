#pragma once
#include "Weapon.h"

class MeleeWeapon: public Weapon
{
private:
	double knockback;
public:
	MeleeWeapon(int);
	~MeleeWeapon();

	void setKnockback(double);
	double getKnockback();
};

