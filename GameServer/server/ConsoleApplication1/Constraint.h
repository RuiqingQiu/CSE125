#pragma once
#include "GameObj.h"
class Constraint
{
public:
	btFixedConstraint * joint6DOF;
	Constraint();
	~Constraint();
	void addConstraint(GameObj* a, GameObj* b);
};

