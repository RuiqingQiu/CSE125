#include "Weapon.h"


Weapon::Weapon()
{
}


Weapon::~Weapon()
{
}

//weapon.cpp
int Weapon::getRange(){
	return _range;
}

double Weapon::getDamage(){
	return _damage;
}

double Weapon::getAttackSpeed(){
	return _attackSpeed;
}

GameObj* Weapon::getGameObj()
{
	return gameObj;
}

void Weapon::setDamage(double d)
{
	_damage = d;
}
void Weapon::setAttackSpeed(double a)
{
	_attackSpeed = a;
}
void Weapon::setGameObj(GameObj* g)
{
	gameObj = g;
}

void Weapon::setRange(int r)
{
	_range = r;
}

void Weapon::setSplash(double s)
{
	_splash = s;
}

double Weapon::getSplash()
{
	return _splash;
}
