#include "DamageSystem.h"


DamageSystem::DamageSystem(int instantKill)
{
	_instantKill = instantKill;
}


DamageSystem::~DamageSystem()
{
}

int DamageSystem::performDamage(GameObj* o1, GameObj* o2, DamageEvent* e)
{
	switch (o1->getCollisionType())
	{
	case C_WALLS:
	{
		switch (o2->getCollisionType())
		{
			case C_PROJECTILE:
			{
				//std::cout << "COLLISION: WALL WITH PROJECTILE" << std::endl;
				e->setResult1(NOTHING); e->setResult2(DELETED);
				return CH_BULLETWALL;
			}
			case C_ROBOT_PARTS:
			{
					e->setResult1(NOTHING); e->setResult2(NOTHING);
					return CH_PLAYERWALL;
			}
			case C_ROBOT:
			{
					e->setResult1(NOTHING); e->setResult2(NOTHING);
					return CH_PLAYERWALL;
			}
			default:
			{
				e->setResult1(NOTHING); e->setResult2(NOTHING);
				return CH_INVALIDCOLLISION;
			}
		}
		return CH_INVALIDCOLLISION;
	}
	case C_GROUND:
	{
	    
		switch (o2->getCollisionType())
		{
			case C_PROJECTILE:
			{
				//std::cout << "COLLISION: GROUND WITH PROJECTILE" << std::endl;
				e->setResult1(NOTHING); e->setResult2(DELETED);
				return CH_BULLETWALL;
			}
			default:
			{
				e->setResult1(NOTHING); e->setResult2(NOTHING);
				return CH_INVALIDCOLLISION;
			}
		}
		return CH_INVALIDCOLLISION;
	}
	case C_ROBOT:
	{
		switch (o2->getCollisionType())
		{
			case C_PROJECTILE:
			{
				//std::cout << "COLLISION: ROBOT WITH PROJECTILE" << std::endl;
				e->setResult1(NOTHING); e->setResult2(DELETED);
				e->setDamage1();
				double damage = o2->getDamage();
				if (o2->getBlockType() == BULLET)
				{
					damage *= 2;
				}
				//std::cout << "O2 damage" << o2->getDamage() << std::endl;
				if (o1->applyDamage(damage) <= 0)
				{

					//std::cout << "ROB WITH PROJ BREAK CONST" << std::endl;
					((Robot*)o1)->setDiedTo((Robot*)o2->getBelongTo());
					e->setResult1(DEATH);
				}
				return CH_BULLETPLAYER;
				
			}
			case C_MELEE:
			{
				//std::cout << "COLLISION: ROBOT WITH MELEE" << std::endl;
				e->setResult1(NOTHING); e->setResult2(NOTHING);

				e->setDamage1();
				if (o1->applyDamage(o2->getDamage()) <= 0)
				{
					((Robot*)o1)->setDiedTo((Robot*)o2->getBelongTo());
					e->setResult1(DEATH);
				}
				return CH_PLAYERPLAYER;
			}
			case C_GROUND:{
				e->setResult1(NOTHING); e->setResult2(NOTHING);
				return CH_INVALIDCOLLISION; 
			}
			case C_ROBOT:{

				//std::cout << "COLLISION: ROBOT WITH ROBOT" << std::endl;
				e->setResult1(NOTHING); e->setResult2(NOTHING);
				return CH_PLAYERPLAYER;
			}
			case C_ROBOT_PARTS:
			{
								  e->setResult1(NOTHING); e->setResult2(NOTHING);
								  return CH_PLAYERPLAYER;
			}

			case C_WALLS:{
							 e->setResult1(NOTHING); e->setResult2(NOTHING);
							 return CH_PLAYERWALL;
			}
			default:
			{
				e->setResult1(NOTHING); e->setResult2(NOTHING);
				return CH_INVALIDCOLLISION;
			}
		}
		return CH_INVALIDCOLLISION;
	}
	case C_ROBOT_PARTS:
	{
		switch (o2->getCollisionType())
		{
			case C_PROJECTILE:
			{
				//std::cout << "COLLISION: ROBOT PART WITH PROJECTILE" << std::endl;
				e->setResult1(NOTHING); e->setResult2(DELETED);
				double damage = o2->getDamage();
				if (o2->getBlockType() == BULLET)
				{
					damage *= 2;
				}
				//std::cout << "O2 damage" << o2->getDamage() << std::endl;
				if (o1->applyDamage(damage) <= 0)
				{
					//std::cout << "ROB PART WITH PROJ BREAK CONST" << std::endl;
					e->setResult1(BREAK_CONSTRAINT);
				}
				e->setDamage1();
				Robot* r = (Robot*)o1->getBelongTo();
				
				if (r->applyDamage(damage) <= 0)
				//if (r->applyDamage(1000) <= 0)
				{
					r->setDiedTo((Robot*)o2->getBelongTo());
					//std::cout << "o2 belongto pointer in ds: " << (Robot*)o2->getBelongTo() << std::endl;
					//std::cout << "o2 belongto cid in ds: " << ((Robot*)o2->getBelongTo())->getCID() << std::endl;
				}
				return CH_BULLETPLAYER;
			}
			case C_MELEE:
			{
				//std::cout << "COLLISION: ROBOT PART WITH MELEE" << std::endl;
				e->setResult1(NOTHING); e->setResult2(NOTHING);

		
				if (o1->applyDamage(o2->getDamage()) <= 0)
				{
					e->setResult1(BREAK_CONSTRAINT);
				}
				e->setDamage1();
				Robot* r = (Robot*)o1->getBelongTo();
				if (r->applyDamage(o2->getDamage()) <= 0)
				{
					r->setDiedTo((Robot*)o2->getBelongTo());
				}
				return CH_PLAYERPLAYER;
			}
			case C_WALLS:{
							 e->setResult1(NOTHING); e->setResult2(NOTHING);
							 return CH_PLAYERWALL;
			}
			case C_ROBOT_PARTS:
			{
								  e->setResult1(NOTHING); e->setResult2(NOTHING);
								  return CH_PLAYERPLAYER;
			}
			case C_ROBOT:
			{
								  e->setResult1(NOTHING); e->setResult2(NOTHING);
								  return CH_PLAYERPLAYER;
			}


			default:
			{
				e->setResult1(NOTHING); e->setResult2(NOTHING);
				return CH_INVALIDCOLLISION;
			}
		}
		return CH_INVALIDCOLLISION;
	}
	case C_PROJECTILE:
	{
		switch (o2->getCollisionType())
		{
			case C_WALLS:
			{
				//std::cout << "COLLISION: PROJECTILE WITH WALL" << std::endl;
				e->setResult1(DELETED); e->setResult2(NOTHING);
				return CH_BULLETWALL;
			}
			case C_GROUND:
			{
				//std::cout << "COLLISION: PROJECTILE WITH GROUND" << std::endl;
				e->setResult1(DELETED); e->setResult2(NOTHING);
				return CH_INVALIDCOLLISION;
			}
			case C_ROBOT:
			{
				//std::cout << "COLLISION: PROJECTILE WITH ROBOT" << std::endl;
				e->setResult1(DELETED); e->setResult2(NOTHING);
				
				double damage = o1->getDamage();
				if (o2->getBlockType() == BULLET)
				{
					damage *= 2;
				}

				if (o2->applyDamage(damage) <= 0)
				{
					((Robot*)o2)->setDiedTo((Robot*)o1->getBelongTo());
					e->setResult2(DEATH);
				}


				e->setDamage2();
				return CH_PLAYERWALL;
			}
			case C_ROBOT_PARTS:
			{
				//std::cout << "COLLISION: PROJECTILE WITH ROBOT PART" << std::endl;
				e->setResult1(DELETED); e->setResult2(NOTHING);

				double damage = o1->getDamage();
				if (o2->getBlockType() == BULLET)
				{
					damage *= 2;
				}
				if (o2->applyDamage(damage) <= 0)
				{
					e->setResult2(BREAK_CONSTRAINT);
				}
				e->setDamage2();
				Robot* r = (Robot*)o2->getBelongTo();
				if (r->applyDamage(damage) <= 0)
				{
					r->setDiedTo((Robot*)o1->getBelongTo());
				}
				return CH_PLAYERWALL;
			}
			case C_PROJECTILE:
			{
				//std::cout << "COLLISION: PROJECTILE WITH PROJECTILE" << std::endl;
				e->setResult1(DELETED); e->setResult2(DELETED);
				return CH_BULLETWALL;
			}
			case C_MELEE:
			{
				//std::cout << "COLLISION: PROJECTILE WITH MELEE" << std::endl;
				e->setResult1(DELETED); e->setResult2(NOTHING);
			
				double damage = o1->getDamage();
				if (o2->getBlockType() == BULLET)
				{
					damage *= 2;
				}
				if (o2->applyDamage(damage) <= 0)
				{
					e->setResult2(BREAK_CONSTRAINT);
				}
				e->setDamage2();
				Robot* r = (Robot*)o2->getBelongTo();
				if (r->applyDamage(damage) <= 0)
				{
					r->setDiedTo((Robot*)o1->getBelongTo());
				}
				return CH_PLAYERWALL;
			}
			default:
			{
				//std::cout << "DamageSystem Error: Should not have Projectile and Unknown type " << o2->getCollisionType() << std::endl;
				e->setResult1(NOTHING); e->setResult2(NOTHING);
				return CH_INVALIDCOLLISION;
			}	
		}
		return CH_INVALIDCOLLISION;
	}
	case C_MELEE:
	{
		switch (o2->getCollisionType())
		{
			case C_ROBOT:
			{
				//std::cout << "COLLISION: MELEE WITH ROBOT" << std::endl;
				e->setResult1(NOTHING); e->setResult2(NOTHING);

				if (((Robot*)o2)->applyDamage(o1->getDamage()) <= 0)
				{
					((Robot*)o2)->setDiedTo((Robot*)o1->getBelongTo());
					e->setResult2(DEATH);
				}
				e->setDamage2();
				return CH_PLAYERPLAYER;
			}
			case C_ROBOT_PARTS:
			{
				//std::cout << "COLLISION: MELEE WITH ROBOT PART" << std::endl;
				e->setResult1(NOTHING); e->setResult2(BREAK_CONSTRAINT);
				 
				e->setDamage2();
				Robot* r = (Robot*)o2->getBelongTo();
				if (r->applyDamage(o1->getDamage()) <= 0)
				{
					r->setDiedTo((Robot*)o1->getBelongTo());
				}
				return CH_PLAYERPLAYER;
			}
			case C_PROJECTILE:
			{
				
				//std::cout << "COLLISION: ROBOT PART WITH PROJECTILE" << std::endl;
				e->setResult1(NOTHING); e->setResult2(DELETED);
				//std::cout << "O2 damage" << o2->getDamage() << std::endl;
				 
				double damage = o2->getDamage();
				if (o2->getBlockType() == BULLET)
				{
					damage *= 2;
				}
				if (o1->applyDamage(damage) <= 0)
				{
					//std::cout << "ROB PART WITH PROJ BREAK CONST" << std::endl;
					e->setResult1(BREAK_CONSTRAINT);
				}
				e->setDamage1();
				Robot* r = (Robot*)o1->getBelongTo();
				if (r->applyDamage(damage) <= 0)
				{
					r->setDiedTo((Robot*)o2->getBelongTo());
				}
				return CH_BULLETPLAYER;

			}
			case C_MELEE:
			{
				//std::cout << "COLLISION: MELEE WITH MELEE" << std::endl;
				e->setResult1(BREAK_CONSTRAINT); e->setResult2(BREAK_CONSTRAINT);
			

				e->setDamage1();
				Robot* r1 = (Robot*)o1->getBelongTo();
				if (r1->applyDamage(o2->getDamage()) <= 0)
				{
					r1->setDiedTo((Robot*)o2->getBelongTo());
				}

				e->setDamage2();
				Robot* r2 = (Robot*)o2->getBelongTo();
				if (r2->applyDamage(o1->getDamage()) <= 0)
				{
					r2->setDiedTo((Robot*)o1->getBelongTo());
				}
				return CH_PLAYERPLAYER;
			}
			default:
			{
				e->setResult1(NOTHING); e->setResult2(NOTHING);
				return CH_INVALIDCOLLISION;
			}
		}
		return CH_INVALIDCOLLISION;
	}
	default:
	{
		e->setResult1(NOTHING); e->setResult2(NOTHING);
		return CH_INVALIDCOLLISION;
	}
	} //end of outer switch
}
