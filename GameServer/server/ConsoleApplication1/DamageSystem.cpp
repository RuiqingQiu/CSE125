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
		std::cout << "o1 GROUND"<< std::endl;
		switch (o2->getCollisionType())
		{
			case C_PROJECTILE:
			{
				std::cout << "o2 PROJ" << std::endl;
				e->setResult1(NOTHING); e->setResult2(DELETED);
				break;
			}
			default:
			{
				std::cout << "o2 DEFAULT" << std::endl;
				e->setResult1(NOTHING); e->setResult2(NOTHING);
				break;
			}
		}
		break;
	}
	case C_ROBOT:
	{
		std::cout << "o1 ROBOT" << std::endl;
		switch (o2->getCollisionType())
		{
			case C_PROJECTILE:
			{
			//TODO: NEED TO CHANGE TO DIE
				std::cout << "o2 PROJ" << std::endl;
				e->setResult1(BREAK_CONSTRAINT); e->setResult2(DELETED);
				if (((Robot*)o1)->applyDamage(o2->getDamage()) < 0)
				{
					e->setResult1(DEATH);
				}
				break;
			}
			case C_MELEE:
			{
				//TODO: NEED TO CHANGE TO DIE
				e->setResult1(BREAK_CONSTRAINT); e->setResult2(NOTHING);
				if (((Robot*)o1)->applyDamage(o2->getDamage()) < 0)
				{
					e->setResult1(DEATH);
				}
				break;
			}
			case C_GROUND:{

				std::cout << "o2 Ground" << std::endl;
				e->setResult1(NOTHING); e->setResult2(NOTHING);
				break; 
			}
			case C_ROBOT:{

				std::cout << "o2 ROBOT" << std::endl;
				e->setResult1(NOTHING); e->setResult2(NOTHING);
				break;
			}
			default:
			{
				std::cout << "o2 DONT CARE" << std::endl;
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
				e->setResult1(BREAK_CONSTRAINT); e->setResult2(DELETED);
				break;
			}
			case C_MELEE:
			{
				e->setResult1(BREAK_CONSTRAINT); e->setResult2(NOTHING);
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
		std::cout << "o1 PROJ" << std::endl;
		switch (o2->getCollisionType())
		{
			case C_WALLS:
			{
				std::cout << "O2 WALL" << std::endl;
				e->setResult1(DELETED); e->setResult2(NOTHING);
				break;
			}
			case C_GROUND:
			{
				std::cout << "O2 GROUND" << std::endl;
				e->setResult1(DELETED); e->setResult2(NOTHING);
				break;
			}
			case C_ROBOT:
			{
				std::cout << "o2 ROBOT" << std::endl;
				e->setResult1(DELETED); e->setResult2(BREAK_CONSTRAINT);
				if (((Robot*)o2)->applyDamage(o1->getDamage()) < 0)
				{
					e->setResult2(DEATH);
				}
				break;
			}
			case C_ROBOT_PARTS:
			{
				e->setResult1(DELETED); e->setResult2(BREAK_CONSTRAINT);
				break;
			}
			case C_PROJECTILE:
			{
				e->setResult1(DELETED); e->setResult2(DELETED);

				break;
			}
			case C_MELEE:
			{
				e->setResult1(DELETED); e->setResult2(BREAK_CONSTRAINT);
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
