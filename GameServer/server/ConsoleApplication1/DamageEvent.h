#pragma once
#include "Robot.h"

enum RESULT
{
	NOTHING = 0,
	BREAK_CONSTRAINT = 1,
	DELETED = 2,
	DEATH = 3,
};

class DamageEvent
{

private:
	GameObj* obj1;
	GameObj* obj2;

	int result1;
	int result2;

	int damageDealt1 = 0;
	int damageDealt2 = 0;

public:
	DamageEvent(GameObj*, GameObj*);
	~DamageEvent();

	GameObj* getObj1();
	GameObj* getObj2();
	int getResult1();
	int getResult2();
	void setResult1(int);
	void setResult2(int);
	void setDamage1();
	int getDamage1();
	void setDamage2();
	int getDamage2();

};

