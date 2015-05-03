#pragma once
#include "GameObj.h"
#include "RangedWeapon.h"
#include "MeleeWeapon.h"

enum PLAYER_STATE {
	PS_BUILD = 0,
	PS_ALIVE = 1,
	PS_DEAD = 2,
};
class Robot : public GameObj
{
private:
	int _r_cid;
	int _takedowns;
	int _deaths;
	char* _name;
	btRaycastVehicle *vehicle;
	std::vector<Weapon *> weapons ;
	double _width;
	double _height;
	double _depth;
	double _health;
	int _state;
	double _maxHealth;


public:
	Robot(int, char*);
	~Robot();

	void setCID(int);
	void setTakeDowns(int);
	void setDeaths(int);
	void setName(char*);

	void setWidth(double);
	void setHeight(double);
	void setDepth(double);

	void setHealth(double);
	void setMaxHealth(double);
	double getHealth();
	double getMaxHealth();

	double applyDamage(double);

	double getWidth();
	double getHeight();
	double getDepth();

	int getCID();
	int getTakeDowns();
	int getDeaths();
	char* getName();
	std::vector<Weapon*> getWeapons();
	void setWeapons(std::vector<Weapon*>);
	void addWeapon(Weapon *);
	void shoot(std::vector<std::pair<GameObj*, double>>*);
	void clearWeapons();

	btRaycastVehicle * getVehicle();
	void createVehicle(btDynamicsWorld* dynamicWorld, double width, double height, double depth, std::map< btCollisionObject*, GameObj*> *);
	void createRigidBody(std::map< btCollisionObject*, GameObj*> *);
	btRigidBody* getRigidBody() override;
	void nextState();
	int getState();
	void setState(int);
};

