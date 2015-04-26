#include "Collision.h"


Collision::Collision(btCollisionObject * obj1, btCollisionObject * obj2)
{
	_obj1 = obj1;
	_obj2 = obj2;
}


Collision::~Collision()
{
}
btCollisionObject * Collision::getObj1()
{return _obj1; }
btCollisionObject * Collision::getObj2()
{
	return _obj2;
}
