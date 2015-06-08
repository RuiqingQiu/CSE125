#pragma once
#include "Robot.h"
#include "DamageEvent.h"
#include <iostream>
#include "GECollisonHappen.h"
class DamageSystem
{

private:
	int _instantKill;

public:
	DamageSystem(int);
	~DamageSystem();
	int performDamage(GameObj*, GameObj*, DamageEvent*);
};



