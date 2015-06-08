#include "Collision.h"


Collision::Collision(btCollisionObject * obj1, btCollisionObject * obj2, btManifoldPoint* pt)
{
	_obj1 = obj1;
	_obj2 = obj2;
	_pt = pt;
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

btManifoldPoint * Collision::getPt()
{
	return _pt;
}


double Collision::getX(){
	double center = (_pt->getPositionWorldOnA().getX() + _pt->getPositionWorldOnB().getX()) /2;
	return center;
}

double Collision::getY(){
	double center = (_pt->getPositionWorldOnA().getY() + _pt->getPositionWorldOnB().getY()) / 2;
	return center;
}


double Collision::getZ(){
	double center = (_pt->getPositionWorldOnA().getZ() + _pt->getPositionWorldOnB().getZ()) / 2;
	return center;
}


double getY();
double getZ();