#include "Projectile.h"

Projectile::Projectile(double x, double y, double z, double qX, double qY, double qZ, double qW, double mass, double width, double height, double depth)
:GameObj(x, y, z, qX, qY, qZ, qW, BOX, mass)
{
	_width = width;
	_height = height;
	_depth = depth;
}

Projectile::~Projectile()
{

}
GameObj* Projectile::shoot()
{
	return nullptr;
}
void Projectile::setWidth(double width)
{
	_width = width;
}
void Projectile::setHeight(double height)
{
	_height = height;
}
void Projectile::setDepth(double depth)
{
	_depth = depth;
}
double Projectile::getWidth()
{
	return _width;
}
double Projectile::getHeight()
{
	return _height;
}
double Projectile::getDepth()
{
	return _depth;
}

btRigidBody* Projectile::getRigidBody()
{
	return getRB();
}


void Projectile::createRigidBody()//std::map< btCollisionObject*, GameObj*> * map)
{
	btCollisionShape* fallShape = new btBoxShape(btVector3(this->getWidth() / 2, this->getHeight() / 2, this->getDepth() / 2));
	btDefaultMotionState* fallMotionState =
		new btDefaultMotionState(btTransform(btQuaternion(this->getqX(), this->getqY(), this->getqZ(), this->getqW()), btVector3(this->getX(), this->getY(), this->getZ())));
	btScalar mass = this->getMass();
	btVector3 fallInertia(0, 0, 0);
	fallShape->calculateLocalInertia(mass, fallInertia);
	btRigidBody::btRigidBodyConstructionInfo fallRigidBodyCI(mass, fallMotionState, fallShape, fallInertia);
	fallRigidBodyCI.m_friction = 0.0f;
	fallRigidBodyCI.m_restitution = 0.0f;
	fallRigidBodyCI.m_linearDamping = 0.2f;
	fallRigidBodyCI.m_angularDamping = 0.1f;
	btRigidBody* rb = new btRigidBody(fallRigidBodyCI);
	//map->insert(std::pair<btCollisionObject*, GameObj*> (rb, this));
	rb->setUserPointer(this);
	this->setRigidBody(rb);
}
