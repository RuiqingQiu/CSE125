#pragma once
#include "GameObj.h"
#include "definition.h"
class GOCylinder : public GameObj
{
private:
	double _radius;
	double _height;

public:
	GOCylinder(double, double, double, double, double, double, double, double, double, double);
	~GOCylinder();
	void setRadius(double);
	void setHeight(double);
	double getRadius();
	double getHeight();
	btRigidBody* getRigidBody() override;
	void createRigidBody() override; // std::map< btCollisionObject*, GameObj*> *) override;
	GameObj* shoot() override;

};



