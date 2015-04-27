#pragma once
#include "Robot.h"
#include "DamageEvent.h"
#include <iostream>
class DamageSystem
{

private:
	int _instantKill;

public:
	DamageSystem(int);
	~DamageSystem();
	void performDamage(GameObj*, GameObj*, DamageEvent*);
};



