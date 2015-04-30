#pragma once
#include "GameObj.h"
#include "RangedWeapon.h"
#include "MeleeWeapon.h"
class Robot : public GameObj
{
private:
	int _r_cid;
	int _takedowns;
	int _deaths;
	char* _name;
	btRaycastVehicle *vehicle;
	std::vector<Weapon *> weapons;
	double _width;
	double _height;
	double _depth;


public:
	Robot(int, char*);
	~Robot();

	void setID(int);
	void setTakeDowns(int);
	void setDeaths(int);
	void setName(char*);

	void setWidth(double);
	void setHeight(double);
	void setDepth(double);

	double getWidth();
	double getHeight();
	double getDepth();

	int getID();
	int getTakeDowns();
	int getDeaths();
	char* getName();
	std::vector<Weapon*>* getWeapons();
	void addWeapon(Weapon *);
	void shoot(std::vector<std::pair<GameObj*, double>>*);
	void clearWeapons();

	btRaycastVehicle * getVehicle();
	void createVehicle(btDynamicsWorld* dynamicWorld, double width, double height, double depth, std::map< btCollisionObject*, GameObj*> *);
	void createRigidBody(std::map< btCollisionObject*, GameObj*> *);
	btRigidBody* getRigidBody() override;
};

