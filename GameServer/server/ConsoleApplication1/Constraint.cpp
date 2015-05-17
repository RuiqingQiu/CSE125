#include "Constraint.h"


Constraint::Constraint()
{
	_joint6DOF = nullptr;
}

Constraint::~Constraint()
{

}

btRigidBody* Constraint::getRigidBodyA()
{
	if (_joint6DOF != nullptr)
	{
		return &_joint6DOF->getRigidBodyA();
	}
	else
	{
		return nullptr;
	}
}
btRigidBody* Constraint::getRigidBodyB()
{
	if (_joint6DOF != nullptr)
	{
		return &_joint6DOF->getRigidBodyB();
	}
	else
	{
		return nullptr;
	}
}

