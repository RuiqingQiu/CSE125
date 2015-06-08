#pragma once
#include "Weapon.h"

class MeleeWeapon: public Weapon
{
private:
	double knockback;
	double spin;
	double DoT;

public:
	MeleeWeapon(int);
	~MeleeWeapon();

	void setKnockback(double);
	double getKnockback();
	void setSpin(double);
	double getSpin();
	void setDoT(double);
	double getDoT();
};

