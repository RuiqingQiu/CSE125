#include "DamageEvent.h"


DamageEvent::DamageEvent(GameObj* o1, GameObj* o2, int r1, int r2)
{
	obj1 = o1;
	obj2 = o2;
	result1 = r1;
	result2 = r2;
}


DamageEvent::~DamageEvent()
{
}

GameObj* DamageEvent::getObj1()
{
	return obj1;
}

GameObj* DamageEvent::getObj2()
{
	return obj2;
}
int DamageEvent::getResult1()
{
	return result1;
}int DamageEvent::getResult2()
{
	return result2;
}