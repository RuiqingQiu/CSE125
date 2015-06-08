#include "SpawnPoint.h"


SpawnPoint::SpawnPoint(int width)
{
	index = 0;
	spawnPoints[0] = btVector3(-width / 2 + width / 10, 0, -width / 2 + width / 10);
	spawnPoints[1] = btVector3(-width / 2 + width / 10, 0, width / 2 - width / 10);
	spawnPoints[2] = btVector3(width / 2 - width / 10, 0, -width / 2 + width / 10);
	spawnPoints[3] = btVector3(width / 2 - width / 10, 0, width / 2 - width / 10);
}


SpawnPoint::~SpawnPoint()
{
}


btVector3 SpawnPoint::nextPoint(){
	currPoint = spawnPoints[index];
	index = (index + 1) % 4;
	return currPoint;

}
