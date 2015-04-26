#pragma once
#include <btBulletDynamicsCommon.h>
#include "Collision.h"
#include <vector>
class CollisionDetector
{
public:
	CollisionDetector();
	~CollisionDetector();

	void static collisionCallback(btDynamicsWorld*, std::vector<Collision*>* collisionList);
};

