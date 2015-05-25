#pragma once
#include <btBulletDynamicsCommon.h>
class SpawnPoint
{

private:
	int index;

	btVector3 currPoint;
	btVector3 spawnPoints[4];
public:
	SpawnPoint(int);
	~SpawnPoint();



	

	btVector3 nextPoint();
};

