#pragma once
#include "GameObj.h"

enum RANGE{
	MELEE = 0,
	MEDIUM_RANGED = 1,
	FAR_RANGED = 2,
};

class Weapon
{
protected:
	int _type;

private:
	int _range;
	double _damage;
	double _splash;
	GameObj* gameObj;

public:
	Weapon();
	~Weapon();

	void setDamage(double);
	
	void setGameObj(GameObj*);

	int getRange();
	void setRange(int);
	double getSplash();
	void setSplash(double);
	double getDamage();
	GameObj* getGameObj();
};

