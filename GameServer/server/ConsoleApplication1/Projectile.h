#pragma once
#include "GameObj.h"
class Projectile: public GameObj
{
private:
	double _width;
	double _height;
	double _depth;

public:

	Projectile(double, double, double, double, double, double, double, double, double, double, double);
	~Projectile();
	void setWidth(double);
	void setHeight(double);
	void setDepth(double);
	double getWidth();
	double getHeight();
	double getDepth();
	btRigidBody* getRigidBody() override;
	void createRigidBody() override; // std::map< btCollisionObject*, GameObj*> *) override;
	GameObj* shoot() override;
	float initForce;

};

