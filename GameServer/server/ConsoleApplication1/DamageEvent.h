#pragma once
#include "Robot.h"

enum RESULT
{
	NOTHING = 0,
	BREAK_CONSTRAINT = 1,
	DELETED = 2,
};

class DamageEvent
{

private:
	GameObj* obj1;
	GameObj* obj2;

	int result1;
	int result2;

public:
	DamageEvent(GameObj*, GameObj*, int, int);
	~DamageEvent();

	GameObj* getObj1();
	GameObj* getObj2();
	int getResult1();
	int getResult2();
};

