#pragma once
#ifndef GE_COLLISION_HAPPEN_H
#define GE_COLLISION_HAPPEN_H

#include "GameEvents.H"
#include <iostream>

enum ClientCollisionType
{
	CH_BULLETPLAYER = 0,
	CH_PLAYERPLAYER = 1,
	CH_PLAYERWALL = 2,
	CH_BULLETWALL = 3,
	CH_EXPLOSION = 4,
	CH_INVALIDCOLLISION = -1,
};


class GECollisonHappen : public GameEvents
{
private:
	int _collisiontype;
	double _x;
	double _y;
	double _z;


public:
	GECollisonHappen(int collisiontype, double x, double y, double z);
	~GECollisonHappen();

	void to_string(std::string&) override;
};

#endif