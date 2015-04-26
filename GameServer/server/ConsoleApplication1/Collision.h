#pragma once
#include <btBulletDynamicsCommon.h>
class Collision
{
public:
	Collision(btCollisionObject * obj1, btCollisionObject * obj2);
	~Collision();

	btCollisionObject * getObj1();
	btCollisionObject * getObj2();

private:
	btCollisionObject * _obj1;
	btCollisionObject * _obj2;
};

