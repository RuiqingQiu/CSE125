#include "GOPlane.h"


GOPlane::GOPlane(double x, double y, double z, double qX, double qY, double qZ, double qW, double mass, double xNorm, double yNorm, double zNorm, double planeConst)
	:GameObj(x, y, z, qX, qY, qZ, qW, PLANE, mass)
{
	_xNorm = xNorm;
	_yNorm = yNorm;
	_zNorm = zNorm;
	_planeConst = planeConst;
}


GOPlane::~GOPlane()
{
}

btRigidBody* GOPlane::getRigidBody()
{
	return getRB();
}

void GOPlane::setXNorm(double xNorm)
{
	_xNorm = xNorm;
}
void GOPlane::setYNorm(double yNorm)
{
	_yNorm = yNorm;
}
void GOPlane::setZNorm(double zNorm)
{
	_zNorm = zNorm;
}
void GOPlane::setPlaneConst(double planeConst)
{
	_planeConst = planeConst;
}

double GOPlane::getXNorm()
{
	return _xNorm;
}

double GOPlane::getYNorm()
{ 
	return _yNorm; 
}

double GOPlane::getZNorm()
{ 
	return _zNorm; 
}

double GOPlane::getPlaneConst()
{
	return _planeConst;
}


void GOPlane::createRigidBody()//std::map< btCollisionObject*, GameObj*> * map)
{
	btCollisionShape* fallShape = new btStaticPlaneShape(btVector3(this->getXNorm(), this->getYNorm(), this->getZNorm()), this->getPlaneConst());
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
	//map->insert(std::pair<btCollisionObject*, GameObj*>(rb, this));
	rb->setUserPointer(this);
	this->setRigidBody(rb);
}




GameObj* GOPlane::shoot(){ return nullptr; }
