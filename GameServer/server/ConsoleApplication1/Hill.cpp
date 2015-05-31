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
	int newX = rand()%(field_width/2-radius)*((rand()%2) ? 1: -1);
	int newZ = rand() % (field_width/2-radius)*((rand() % 2) ? 1 : -1);
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
		GameObj* object = new GOBox(x + rand() % radius *((rand() % 2) ? 1 : -1), rand() % field_height + 0.1, rand() % radius*((rand() % 2) ? 1 : -1),0, 0, 0, 1, .001, 1, 1, 1);
        object->setBlockType(THREEBYTHREE_GLOWING);
        object->setMass(0.001);
		particles.push_back(object);
		gameObjs->push_back(object);
        std::cout << "created particles" << std::endl;
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
        int randY = rand() % field_height + 0.1;
        btVector3 direction(x - xx + 0.001, randY - yy, z - zz);
        if (direction.getY() == 0) {
            direction.setY(direction.getY() + 0.001);
        }
        direction.normalize();
		if (distance > radius)
		{

			double force = 0.05;
            //std::cout << "updated particles with force" << std::endl;
            btVector3 correctForce = distance*direction*force;
            (*it)->getRigidBody()->applyCentralForce(correctForce);
		}
        else 
        {
            double force = 0.1;
            //std::cout << "updated particles with force" << std::endl;
            btVector3 correctForce = -direction*force;
            (*it)->getRigidBody()->applyCentralForce(correctForce);

        }
	}

}