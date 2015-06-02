#include "Hill.h"


Hill::Hill(int xx, int zz, int w, int h, int rr, int gold)
{
	x = xx;
	z = zz;
	field_width = w;
	field_height = h;
	radius = rr;
	goldInc = gold;
	srand(time(NULL));
}


Hill::~Hill()
{

}

void Hill::update()
{
	int newX = rand()%(field_width/2-2*radius)*((rand()%2) ? 1: -1);
	int newZ = rand() % (field_width/2-2*radius)*((rand() % 2) ? 1 : -1);
	x = newX;
    z = newZ;
}

int Hill::getX()
{
	return x;
}


int Hill::getZ()
{
	return z;
}

int Hill::inHill(int xx, int zz)
{
	return (sqrt((xx-x)*(xx-x) + (zz-z)*(zz-z)) <= radius) ? goldInc : 0;
}

int Hill::getRadius()
{
	return radius;
}

void Hill::createParticles(std::vector<GameObj*>* gameObjs)
{
	for (int i = 0; i < NUM_OF_PARTICLES; i++)
	{
		GameObj* object = new GOBox(x + rand() % radius *((rand() % 2) ? 1 : -1), rand() % field_height + 0.1, rand() % radius*((rand() % 2) ? 1 : -1),0, 0, 0, 1, .001, 0.1, 0.1, 0.1);
		object->setBlockType(MONEY);
        object->setMass(0.001);
		object->setCollisionType(C_INVALID);
		particles.push_back(object);
		gameObjs->push_back(object);
	}
}

void Hill::updateParticles()
{
	std::vector<GameObj* >::iterator it;
	for (it = particles.begin(); it != particles.end(); it++)
	{
		double xx = (*it)->getX();
		double yy = (*it)->getY();
		double zz = (*it)->getZ();
        double distance = sqrt((xx - x)*(xx - x) + (zz - z)*(zz - z));
		int randY = ((double)(rand() -1)/ (RAND_MAX )) * (field_height - 0 + 1) + 0;
        btVector3 direction(x - xx, randY - yy, z - zz);
        
		if (direction.getY() == 0) {
            direction.setY(direction.getY() + 0.00001);
        }
        direction.normalize();
		double force = .1;
		btVector3 vel = (*it)->getRigidBody()->getLinearVelocity();
		btVector3 normY(0,1,0);
		btVector3 directionNoY(direction.getX(), 0, direction.getZ());
		btVector3 rotDirection = directionNoY.cross(normY);
		double len = rotDirection.length();
		double scalar = vel.dot(rotDirection) / (len*len);
		if (scalar == 0)
		{
			scalar = force;
		}
		double speedThreshold = 15;
		vel = scalar*rotDirection;

		if (rotDirection.getZ() == 0)
		{
			rotDirection.setZ(0.001);
		}
		rotDirection.normalize();
		if (vel.length() > speedThreshold)
		{
			//(*it)->getRigidBody()->applyCentralForce(-rotDirection*force);
		}
		else
		{
			(*it)->getRigidBody()->applyCentralForce(rotDirection*force/8);
		}

		//if (distance > radius)
		//{

		//	double force = 0.05;
  //          //std::cout << "updated particles with force" << std::endl;
  //          btVector3 correctForce = distance*direction*force;
  //          (*it)->getRigidBody()->applyCentralForce(correctForce);
		//}
  //      else 
  //      {
  //          double force = 0.1;
  //          //std::cout << "updated particles with force" << std::endl;
  //          btVector3 correctForce = -direction*force;
  //          (*it)->getRigidBody()->applyCentralForce(correctForce);

  //      }

		if (distance > radius)
		{
			//std::cout << "updated particles with force" << std::endl;
			btVector3 correctForce = distance/radius*direction*force;
			(*it)->getRigidBody()->applyCentralForce(correctForce);
		}
		else
		{
			//std::cout << "updated particles with force" << std::endl;
			btVector3 correctForce = -((distance + 1) / distance)*direction*force/8;
			(*it)->getRigidBody()->applyCentralForce(correctForce);

		}
	}

}