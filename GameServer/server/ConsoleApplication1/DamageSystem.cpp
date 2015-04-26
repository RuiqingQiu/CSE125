#include "DamageSystem.h"


DamageSystem::DamageSystem(int instantKill)
{
	_instantKill = instantKill;
}


DamageSystem::~DamageSystem()
{
}

//std::pair<DamageEvent*, DamageEvent*>* DamageSystem::performDamage(GameObj* o1, GameObj* o2)
//{
//	std::pair<DamageEvent*, DamageEvent*>* result;
//	if (_instantKill)
//	{
//
//
//
//
//		//DamageEvent* dE1 = new DamageEvent();
//		//DamageEvent* dE2 = new DamageEvent();
//	}
//	return result;
//}
