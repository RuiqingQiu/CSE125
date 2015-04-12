#include "GOCylinder.h"
GOCylinder::GOCylinder(double x, double y, double z, double qX, double qY, double qZ, double qW, double mass, double radius, double height)
	:GameObj(x, y, z, qX, qY, qZ, qW, CYLINDER, mass)
{
	_radius = radius;
	_height = height;
}


GOCylinder::~GOCylinder()
{
}

void GOCylinder::setRadius(double radius)
{
	_radius = radius;
}
void GOCylinder::setHeight(double height)
{
	_height = height;
}

double GOCylinder::getRadius()
{
	return _radius;
}
double GOCylinder::getHeight()
{
	return _height;
}

void GOCylinder::createRigidBody()
{
	btCollisionShape* fallShape = new btCylinderShape(btVector3(this->getRadius(), this->getHeight()/2, this->getRadius()));
	btDefaultMotionState* fallMotionState =
		new btDefaultMotionState(btTransform(btQuaternion(this->getqX(), this->getqY(), this->getqZ(), this->getqW()), btVector3(this->getX(), this->getY(), this->getZ())));
	btScalar mass = this->getMass();
	btVector3 fallInertia(0, 0, 0);
	fallShape->calculateLocalInertia(mass, fallInertia);
	btRigidBody::btRigidBodyConstructionInfo fallRigidBodyCI(mass, fallMotionState, fallShape, fallInertia);
	fallRigidBodyCI.m_friction = 0.5f;
	fallRigidBodyCI.m_restitution = 0.1f;
	fallRigidBodyCI.m_linearDamping = 0.2f;
	fallRigidBodyCI.m_angularDamping = 0.1f;
	this->setRigidBody(new btRigidBody(fallRigidBodyCI));
}