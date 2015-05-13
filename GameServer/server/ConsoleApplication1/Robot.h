#pragma once
#include "GameObj.h"

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
	double _width;
	double _height;
	double _depth;
	std::vector<GameObj*> parts;
	int _wheelType;
	Robot* diedTo = nullptr;
	int _state;

public:
	Robot(int, char*);
	~Robot();

	void setCID(int);
	void setTakeDowns(int);
	void setDeaths(int);
	void setName(char*);

	void setDiedTo(Robot*);
	Robot* getDiedTo();

	void setWidth(double);
	void setHeight(double);
	void setDepth(double);

	void setWheelType(int);
	int getWheelType();


	double getWidth();
	double getHeight();
	double getDepth();

	int getCID();
	int getTakeDowns();
	int getDeaths();
	char* getName();
	GameObj* shoot() override;
	void shoot(std::vector<GameObj*>*);
	void clearWeapons();

	void addPart(GameObj*);
	std::vector<GameObj*> getParts();

	btRaycastVehicle * getVehicle();
	void createVehicle(btDynamicsWorld* dynamicWorld, double width, double height, double depth);// , std::map< btCollisionObject*, GameObj*> *);
	void createRigidBody();// std::map< btCollisionObject*, GameObj*> *);
	btRigidBody* getRigidBody() override;
	void nextState();
	void setParts(std::vector<GameObj*> );
	int getState();
	void setState(int);
};

