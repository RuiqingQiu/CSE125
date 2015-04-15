#pragma once
#include "Weapon.h"
#include "definition.h"
class Robot
{
private:
	int _cid;
	int _takedowns;
	int _deaths;
	char* _name;
	GameObj * centerBlock;
	Weapon *_w1;
	Weapon *_w2;
	Weapon *_w3;


public:
	Robot(int, char*, Weapon*, Weapon*, Weapon*);
	~Robot();

	void setID(int);
	void setTakeDowns(int);
	void setDeaths(int);
	void setName(char*);
	void setWeapon1(Weapon*);
	void setWeapon2(Weapon*);
	void setWeapon3(Weapon*);

	int getID();
	int getTakeDowns();
	int getDeaths();
	char* getName();
	Weapon* getWeapon1();
	Weapon* getWeapon2();
	Weapon* getWeapon3();


};

