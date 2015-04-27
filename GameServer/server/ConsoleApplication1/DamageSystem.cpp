#include "DamageSystem.h"


DamageSystem::DamageSystem(int instantKill)
{
	_instantKill = instantKill;
}


DamageSystem::~DamageSystem()
{
}

void DamageSystem::performDamage(GameObj* o1, GameObj* o2,DamageEvent * e)
{
	std::cout << "enter damage system"<< std::endl;
	switch (o1->getCollisionType())
	{
	case C_WALLS:
	{
		switch (o2->getCollisionType())
		{
			case C_PROJECTILE:
			{
				e = new DamageEvent(o1, o2, NOTHING, DELETED);
				break;
			}
			default:
			{
				e = new DamageEvent(o1, o2, NOTHING, NOTHING);
				break;
			}
		}
		break;
	}
	case C_GROUND:
	{
		std::cout << "enter o1, ground"<< std::endl;
		switch (o2->getCollisionType())
		{
			case C_PROJECTILE:
			{
				std::cout << "enter o2, projectile" << std::endl;
				e = new DamageEvent(o1, o2, NOTHING, DELETED);
				break;
			}
			default:
			{
				std::cout << "enter o2, default" << std::endl;
				e = new DamageEvent(o1, o2, NOTHING, NOTHING);
				break;
			}
		}
		break;
	}
	case C_ROBOT:
	{
		switch (o2->getCollisionType())
		{
			case C_PROJECTILE:
			{
			//TODO: NEED TO CHANGE TO DIE
				e = new DamageEvent(o1, o2, BREAK_CONSTRAINT, DELETED);
				break;
			}
			case C_MELEE:
			{
				//TODO: NEED TO CHANGE TO DIE
				e = new DamageEvent(o1, o2, BREAK_CONSTRAINT, NOTHING);
				break;
			}
			default:
			{
				e = new DamageEvent(o1, o2, NOTHING, NOTHING);
				break;
			}
		}
		break;
	}
	case C_ROBOT_PARTS:
	{
		switch (o2->getCollisionType())
		{
			case C_PROJECTILE:
			{
				e = new DamageEvent(o1, o2, BREAK_CONSTRAINT, DELETED);
				break;
			}
			case C_MELEE:
			{
				e = new DamageEvent(o1, o2, BREAK_CONSTRAINT, NOTHING);
				break;
			}
			default:
			{
				e = new DamageEvent(o1, o2, NOTHING, NOTHING);
				break;
			}
		}
		break;
	}
	case C_PROJECTILE:
	{
		std::cout << "enter o1, projectile" << std::endl;
		switch (o2->getCollisionType())
		{
			case C_WALLS:
			{
				e = new DamageEvent(o1, o2, DELETED, NOTHING);
				break;
			}
			case C_GROUND:
			{
				std::cout << "enter o2, ground" << std::endl;
				e = new DamageEvent(o1, o2, DELETED, NOTHING);
				break;
			}
			case C_ROBOT:
			{
				e = new DamageEvent(o1, o2, DELETED, BREAK_CONSTRAINT);
				break;
			}
			case C_ROBOT_PARTS:
			{
				e = new DamageEvent(o1, o2, DELETED, BREAK_CONSTRAINT);
				break;
			}
			case C_PROJECTILE:
			{
				e = new DamageEvent(o1, o2, DELETED, DELETED);
				break;
			}
			case C_MELEE:
			{
				e = new DamageEvent(o1, o2, DELETED, BREAK_CONSTRAINT);
				break;
			}
			default:
			{
				std::cout << "DamageSystem Error: Should not have Projectile and Unknown type " << o2->getCollisionType() << std::endl;
				e = new DamageEvent(o1, o2, NOTHING, NOTHING);
				break;
			}	
		}
		break;
	}
	case C_MELEE:
	{
		switch (o2->getCollisionType())
		{
			case C_ROBOT:
			{
				e = new DamageEvent(o1, o2, NOTHING, BREAK_CONSTRAINT);
				break;
			}
			case C_ROBOT_PARTS:
			{
				e = new DamageEvent(o1, o2, NOTHING, BREAK_CONSTRAINT);
				break;
			}
			case C_PROJECTILE:
			{
				e = new DamageEvent(o1, o2, BREAK_CONSTRAINT, DELETED);
				break;
			}
			case C_MELEE:
			{
				e = new DamageEvent(o1, o2, BREAK_CONSTRAINT, BREAK_CONSTRAINT);
				break;
			}
			default:
			{
				e = new DamageEvent(o1, o2, NOTHING, NOTHING);
				break;
			}
		}
		break;
	}
	default:
	{
		e = new DamageEvent(o1, o2, NOTHING, NOTHING);
		break;
	}
	} //end of outer switch
	//if (e == nullptr)
	//{
		std::cout << "broken system" << std::endl;
		e = new DamageEvent(o1, o2, NOTHING, NOTHING);
//	}
}
