#include "DamageSystem.h"


DamageSystem::DamageSystem(int instantKill)
{
	_instantKill = instantKill;
}


DamageSystem::~DamageSystem()
{
}

void DamageSystem::performDamage(GameObj* o1, GameObj* o2, DamageEvent* e)
{
	switch (o1->getCollisionType())
	{
	case C_WALLS:
	{
		switch (o2->getCollisionType())
		{
			case C_PROJECTILE:
			{
				std::cout << "COLLISION: WALL WITH PROJECTILE" << std::endl;
				e->setResult1(NOTHING); e->setResult2(DELETED);
				break;
			}
			default:
			{
				e->setResult1(NOTHING); e->setResult2(NOTHING);
				break;
			}
		}
		break;
	}
	case C_GROUND:
	{
	    
		switch (o2->getCollisionType())
		{
			case C_PROJECTILE:
			{
				std::cout << "COLLISION: GROUND WITH PROJECTILE" << std::endl;
				e->setResult1(NOTHING); e->setResult2(DELETED);
				break;
			}
			default:
			{
				e->setResult1(NOTHING); e->setResult2(NOTHING);
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
				std::cout << "COLLISION: ROBOT WITH PROJECTILE" << std::endl;
				e->setResult1(BREAK_CONSTRAINT); e->setResult2(DELETED);
				if (o1->applyDamage(o2->getDamage()) < 0)
				{
					e->setResult1(DEATH);
				}
				break;
			}
			case C_MELEE:
			{
				std::cout << "COLLISION: ROBOT WITH MELEE" << std::endl;
				e->setResult1(BREAK_CONSTRAINT); e->setResult2(NOTHING);
				if (o1->applyDamage(o2->getDamage()) < 0)
				{
					e->setResult1(DEATH);
				}
				break;
			}
			case C_GROUND:{
				e->setResult1(NOTHING); e->setResult2(NOTHING);
				break; 
			}
			case C_ROBOT:{

				std::cout << "COLLISION: ROBOT WITH ROBOT" << std::endl;
				e->setResult1(NOTHING); e->setResult2(NOTHING);
				break;
			}
			default:
			{
				e->setResult1(NOTHING); e->setResult2(NOTHING);
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
				std::cout << "COLLISION: ROBOT PART WITH PROJECTILE" << std::endl;
				e->setResult1(NOTHING); e->setResult2(DELETED);
				if (o1->applyDamage(o2->getDamage()) < 0)
				{
					e->setResult1(BREAK_CONSTRAINT);
				}
				break;
			}
			case C_MELEE:
			{
				std::cout << "COLLISION: ROBOT PART WITH MELEE" << std::endl;
				e->setResult1(NOTHING); e->setResult2(NOTHING);
				if (o1->applyDamage(o2->getDamage()) < 0)
				{
					e->setResult1(BREAK_CONSTRAINT);
				}
				break;
			}
			default:
			{
				e->setResult1(NOTHING); e->setResult2(NOTHING);
				break;
			}
		}
		break;
	}
	case C_PROJECTILE:
	{
		switch (o2->getCollisionType())
		{
			case C_WALLS:
			{
				std::cout << "COLLISION: PROJECTILE WITH WALL" << std::endl;
				e->setResult1(DELETED); e->setResult2(NOTHING);
				break;
			}
			case C_GROUND:
			{
				std::cout << "COLLISION: PROJECTILE WITH GROUND" << std::endl;
				e->setResult1(DELETED); e->setResult2(NOTHING);
				break;
			}
			case C_ROBOT:
			{
				std::cout << "COLLISION: PROJECTILE WITH ROBOT" << std::endl;
				e->setResult1(DELETED); e->setResult2(BREAK_CONSTRAINT);
				if (o2->applyDamage(o1->getDamage()) < 0)
				{
					e->setResult2(DEATH);
				}
				break;
			}
			case C_ROBOT_PARTS:
			{
				std::cout << "COLLISION: PROJECTILE WITH ROBOT PART" << std::endl;
				e->setResult1(DELETED); e->setResult2(NOTHING);
				if (o2->applyDamage(o1->getDamage()) < 0)
				{
					e->setResult2(BREAK_CONSTRAINT);
				}
				break;
			}
			case C_PROJECTILE:
			{
				std::cout << "COLLISION: PROJECTILE WITH PROJECTILE" << std::endl;
				e->setResult1(DELETED); e->setResult2(DELETED);

				break;
			}
			case C_MELEE:
			{
				std::cout << "COLLISION: PROJECTILE WITH MELEE" << std::endl;
				e->setResult1(DELETED); e->setResult2(NOTHING);
				if (o2->applyDamage(o1->getDamage()) < 0)
				{
					e->setResult2(BREAK_CONSTRAINT);
				}
				break;
			}
			default:
			{
				std::cout << "DamageSystem Error: Should not have Projectile and Unknown type " << o2->getCollisionType() << std::endl;
				e->setResult1(NOTHING); e->setResult2(NOTHING);
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
				e->setResult1(NOTHING); e->setResult2(BREAK_CONSTRAINT);
				if (((Robot*)o2)->applyDamage(o1->getDamage()) < 0)
				{
					e->setResult2(DEATH);
				}
				break;
			}
			case C_ROBOT_PARTS:
			{
				e->setResult1(NOTHING); e->setResult2(BREAK_CONSTRAINT);
				break;
			}
			case C_PROJECTILE:
			{
				e->setResult1(BREAK_CONSTRAINT); e->setResult2(DELETED);
				break;
			}
			case C_MELEE:
			{
				e->setResult1(BREAK_CONSTRAINT); e->setResult2(BREAK_CONSTRAINT);
				break;
			}
			default:
			{
				e->setResult1(NOTHING); e->setResult2(NOTHING);
				break;
			}
		}
		break;
	}
	default:
	{
		e->setResult1(NOTHING); e->setResult2(NOTHING);
		break;
	}
	} //end of outer switch
}
