#include "GOCapsule.h"


GOCapsule::GOCapsule(double x, double y, double z, double qX, double qY, double qZ, double qW, double mass, double radius, double height)
	:GameObj(x, y, z, qX, qY, qZ, qW, CAPSULE, mass)
{
	_radius = radius;
	_height = height;
}


GOCapsule::~GOCapsule()
{
}

void GOCapsule::setRadius(double radius)
{
	_radius = radius;
}
void GOCapsule::setHeight(double height)
{
	_height = height;
}

double GOCapsule::getRadius()
{
	return _radius;
}
double GOCapsule::getHeight()
{
	return _height;
}


void GOCapsule::createRigidBody(std::map< btCollisionObject*, GameObj*> * map)
{
	btCollisionShape* fallShape = new btCapsuleShape(this->getRadius(), this->getHeight());
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
	btRigidBody* rb = new btRigidBody(fallRigidBodyCI);
	map->insert(std::pair<btCollisionObject*, GameObj*>(rb, this));
	this->setRigidBody(rb);
}