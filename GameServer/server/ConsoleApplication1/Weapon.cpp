#include "Weapon.h"


Weapon::Weapon(int type, double mass, double damage, double attackSpeed)
{
	_type = type;
	_damage = damage;
	_attackSpeed = attackSpeed;
}


Weapon::~Weapon()
{
}



void Weapon::setProjectileSpeed(double speed)
{
	_projectileSpeed = speed;
}

//weapon.cpp
int Weapon::getType(){
	return _type;
}

double Weapon::getDamage(){
	return _damage;
}

double Weapon::getAttackSpeed(){
	return _attackSpeed;
}

double Weapon::getProjectileSpeed(){
	return _projectileSpeed;
}

double Weapon::getMass()
{
	return _mass;
}
