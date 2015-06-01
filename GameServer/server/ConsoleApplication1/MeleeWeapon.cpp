#include "MeleeWeapon.h"
#include <iostream>
MeleeWeapon::MeleeWeapon(int type)
{

	double damage;
	double splash;
	double knockback;
	double spin;
	_type = type;

	switch (type)
	{
	case Needle:{
		damage = 30;
		splash = 1;
		knockback = -100;
		spin = 0;
		DoT = 0;
		break;
	}
	case Mace:{
				  std::cout << "defaultmaceg" << std::endl;
		knockback = 100;
		damage = 80;
		splash = 1;
		spin = 0;
		DoT = 80;
		break;
	}
	case Mallet:
	{
				   spin = 0;
				   knockback = 800;
				   damage = 180;
				   splash = 2;
				   DoT = 0;
				   break;
	}
	default:
	{
			   std::cout << "default no dmg" << std::endl;
			   
			   damage = 0;
			   splash = 0;
			   knockback = 0;
			   spin = 0;
			   break;
	}
	}
	setSpin(spin);
	setKnockback(knockback);
	setDamage(damage);
	setSplash(splash);
	setRange(MELEE);
}


MeleeWeapon::~MeleeWeapon()
{
}

//GameObj* MeleeWeapon::shoot(btTransform * trans)
//{
//	return nullptr;
//}



void MeleeWeapon::setKnockback(double d)
{
	knockback = d;
}
double MeleeWeapon::getKnockback()
{
	return knockback;
}

void MeleeWeapon::setSpin(double s)
{
	spin = s;
}
double MeleeWeapon::getSpin()
{
	return spin;
}


void MeleeWeapon::setDoT(double d){
	DoT = d;

}
double MeleeWeapon::getDoT(){
	return DoT;
}