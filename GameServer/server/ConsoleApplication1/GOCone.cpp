#include "GOCone.h"
GOCone::GOCone(double x, double y, double z,double qX, double qY, double qZ, double qW, double mass, double radius, double height)
	:GameObj(x, y, z, qX, qY, qZ, qW, CONE, mass)
{
	_radius = radius;
	_height = height;
}


GOCone::~GOCone()
{
}

void GOCone::setRadius(double radius)
{
	_radius = radius;
}
void GOCone::setHeight(double height)
{
	_height = height;
}

double GOCone::getRadius()
{
	return _radius;
}
double GOCone::getHeight()
{
	return _height;
}

void GOCone::createRigidBody()
{
	btCollisionShape* fallShape = new btCapsuleShape(this->getRadius(), this->getHeight());
	btDefaultMotionState* fallMotionState =
		new btDefaultMotionState(btTransform(btQuaternion(this->getqX(), this->getqY(), this->getqZ(), this->getqW()), btVector3(this->getX(), this->getY(), this->getZ())));
	btScalar mass = this->getMass();
	btVector3 fallInertia(0, 0, 0);
	fallShape->calculateLocalInertia(mass, fallInertia);
	btRigidBody::btRigidBodyConstructionInfo fallRigidBodyCI(mass, fallMotionState, fallShape, fallInertia);
	this->setRigidBody(new btRigidBody(fallRigidBodyCI));
}