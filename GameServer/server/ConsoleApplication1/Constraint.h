#pragma once
//#include "GameObj.h"
#include <btBulletDynamicsCommon.h>
class Constraint
{
public:
	btFixedConstraint * _joint6DOF;
	
	Constraint();
	~Constraint();
};

