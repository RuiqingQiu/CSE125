#pragma once
#include "GameObj.h"
#include "Weapon.h"
class Robot : public GameObj
{
private:
	int _r_cid;
	int _takedowns;
	int _deaths;
	char* _name;
	btRaycastVehicle *vehicle;
	Weapon *_w1;
	Weapon *_w2;
	Weapon *_w3;


public:
	Robot(int, char*);
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

	btRaycastVehicle * getVehicle();
	void createVehicle(btDynamicsWorld* dynamicWorld, double width, double height, double depth, std::map< btCollisionObject*, GameObj*> *);
	void createRigidBody(std::map< btCollisionObject*, GameObj*> *);
	btRigidBody* getRigidBody();
};

