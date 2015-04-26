#pragma once
#include "GameObj.h"
#include <utility>
#include "DamageEvent.h"
class DamageSystem
{

private:
	int _instantKill;

public:
	DamageSystem(int);
	~DamageSystem();
	//std::pair<DamageEvent*, DamageEvent*>* performDamage(GameObj*, GameObj*);
};



