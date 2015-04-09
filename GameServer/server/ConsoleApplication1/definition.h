#pragma once
	//ACTIONS FOR STATE MACHINE
	enum ACTION
	{
		WAIT = 0,
		ADDCLIENT = 1,
		TIMEUP = 2,
		COUNTDOWN = 3,
		RESTART = 4,
	};


	//game states
	enum STATE {
		INIT_STATE0 = 0,
		INIT_STATE1 = 1,
		INIT_STATE2 = 2,
		INIT_STATE3 = 3,
		BUILD_STATE = 4,
		GAME_STATE0 = 5,
		END_STATE = 8,

	};

	// GameObj (physical) types
	enum OBJECT_TYPE
	{
		PLANE = 0,
		TRIANGLE = 1,
		CAPSULE = 2,
		CONE = 3,
		CYLINDER = 4,
		BOX = 5,
		CLOUD = 6,
	};

#define BIT(x) (1<<(x))
	enum COLLISION_TYPE {
		COL_NOTHING = 0, //<Collide with nothing
		COL_GROUND = BIT(1), //<Collide with ground
		COL_WALL = BIT(2), //<Collide with walls
		COL_PLAYER = BIT(3),
	};


#define oneStep 0.1
#define TIMEFRAME 300