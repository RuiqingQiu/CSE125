#include "DamageEvent.h"


DamageEvent::DamageEvent(GameObj* o1, GameObj* o2)
{
	obj1 = o1;
	obj2 = o2;
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

void DamageEvent::setResult1(int r)
{
	result1 = r;
}

void DamageEvent::setResult2(int r)
{
	result2 = r;
}

void DamageEvent::setDamage2(){
	damageDealt2 = 1;
}
int DamageEvent::getDamage2(){
	return damageDealt2;
}


void DamageEvent::setDamage1(){
	damageDealt1 = 1;
}
int DamageEvent::getDamage1(){
	return damageDealt1;
}