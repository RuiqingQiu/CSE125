#include "Robot.h"


Robot::Robot(int cid, char* name, Weapon* weapon1, Weapon* weapon2, Weapon* weapon3)
{
	_cid = cid;
	_name = name;
	_w1 = weapon1;
	_w2 = weapon2;
	_w3 = weapon3;
}


Robot::~Robot()
{
}


void Robot::setID(int cid)
{
	_cid = cid;
}

void Robot::setTakeDowns(int takedowns)
{
	_takedowns = takedowns;
}

void Robot::setDeaths(int deaths){ }
void Robot::setName(char* name){ _name = name; }
void Robot::setWeapon1(Weapon* weapon){ _w1 = weapon; }
void Robot::setWeapon2(Weapon* weapon){ _w2 = weapon; }
void Robot::setWeapon3(Weapon* weapon){ _w3 = weapon; }

int Robot::getID(){ return _cid; }
int Robot::getTakeDowns(){ return _takedowns; }
int Robot::getDeaths(){ return _deaths; }
char* Robot::getName(){ return _name; }
Weapon* Robot::getWeapon1(){ return _w1; }
Weapon* Robot::getWeapon2(){ return _w2; }
Weapon* Robot::getWeapon3(){ return _w3; }
