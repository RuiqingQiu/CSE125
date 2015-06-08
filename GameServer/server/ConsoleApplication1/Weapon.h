#pragma once


#ifndef WEAPON_H
#define WEAPON_H

#include "definition.h"

class Weapon
{
protected:
	int _type;

private:
	int _range;
	double _damage;
	double _splash;

public:
	Weapon();
	~Weapon();

	void setDamage(double);
	
	int getRange();
	void setRange(int);
	double getSplash();
	void setSplash(double);
	double getDamage();
};


#endif