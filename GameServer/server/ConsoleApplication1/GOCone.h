#pragma once
#include "GameObj.h"
#include "definition.h"
class GOCone : public GameObj
{
private:
	double _radius;
	double _height;

public:
	GOCone(double, double, double, double, double, double, double, double, double, double);
	~GOCone();
	void setRadius(double);
	void setHeight(double);
	double getRadius();
	double getHeight();
	void createRigidBody(std::map< btCollisionObject*, GameObj*> *) override;
};

