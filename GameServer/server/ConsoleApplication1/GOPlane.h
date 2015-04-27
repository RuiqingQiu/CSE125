#pragma once
#include "definition.h"
#include "GameObj.h"
class GOPlane : public GameObj
{

private:
	double _xNorm;
	double _yNorm;
	double _zNorm;
	double _planeConst;
public:
	GOPlane(double, double, double, double, double, double, double, double, double, double, double, double);
	~GOPlane();
	void setXNorm(double);
	void setYNorm(double);
	void setZNorm(double);
	void setPlaneConst(double);
	double getXNorm();
	double getYNorm();
	double getZNorm();
	double getPlaneConst();
	btRigidBody* getRigidBody() override;
	void createRigidBody(std::map< btCollisionObject*, GameObj*> *) override;
};

