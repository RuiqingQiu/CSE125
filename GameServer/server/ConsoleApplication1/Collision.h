#pragma once
#include <btBulletDynamicsCommon.h>
class Collision
{
public:
	Collision(btCollisionObject * obj1, btCollisionObject * obj2, btManifoldPoint* pt);
	~Collision();

	btCollisionObject * getObj1();
	btCollisionObject * getObj2();

	btManifoldPoint * getPt();

	double getX();
	double getY();
	double getZ();

private:
	btCollisionObject * _obj1;
	btCollisionObject * _obj2;
	btManifoldPoint * _pt;
};

