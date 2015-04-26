#pragma once
#include "GameObj.h"
#include "definition.h"
class GOCapsule : public GameObj
{
private:
	double _radius;
	double _height;
	

public:
	GOCapsule(double, double, double, double, double, double, double, double, double, double);
	~GOCapsule();
	void setRadius(double);
	void setHeight(double);
	double getRadius();
	double getHeight();
	void createRigidBody(std::map< btCollisionObject*, GameObj*> *) override;
	
};

