#pragma once
#include "GameObj.h"
#include "ObjectEvents.h"
# define M_PI  3.14159265358979323846

// Packet Types
enum PacketTypes {
	INIT_CONNECTION = 0,
	GAME_STATE = 1,
	MOVE_LEFT = 2,
	MOVE_RIGHT = 3,
	MOVE_FORWARD = 4,
	MOVE_BACKWARD = 5,
	MOVE_UP = 6,
	MOVE_DOWN = 7,
	INIT_CLIENT = 8,
	CONFIRM_CONNECTION = 9,
	BUILD_ROBOT = 10,
	SHOOT = 11,
	INIT_BUILD = 12,
	TIMER = 13,
	BUILD_REQUEST = 14,
};


	//Game Events
	enum GameEventType {
		PLAYER_DEATH = 0,
		PARTICLE = 1,
		TIME = 2,
		SCOREBOARD = 3,

	};

	//TEXTURES
	enum TEXTURE
	{
		ASPHALT = 0,
		BLUE = 1,
		BRICK = 2,
		CLOTH = 3,
		CONCRETE = 4,
		GLASS = 5,
		GOLD = 6,
		IRON = 7,
		LEATHER = 8,
		METAL1 = 9,
		METAL2 = 10,
		METAL3 = 11,
		RUBBER1 = 12,
		RUBBER2 = 13,
		SILVER = 14,
		WARNING = 15,
		WOOD1 = 16,
		WOOD2 = 17,
		WOOD3 = 18,

	};




#define BIT(x) (1<<(x))
	enum BIT_COLLISION_TYPE {
		COL_NOTHING = 0, //<Collide with nothing
		COL_GROUND = BIT(1), //<Collide with ground
		COL_WALL = BIT(2), //<Collide with walls
		COL_PLAYER = BIT(3),
		COL_OBJECT = BIT(4),
	};

	static const int playerCollisions = COL_PLAYER | COL_WALL | COL_GROUND | COL_OBJECT;
	static const int groundCollisions = COL_NOTHING;
	static const int wallCollisions = COL_NOTHING;
	static const int objectCollisions = COL_PLAYER | COL_WALL | COL_GROUND | COL_OBJECT;


#define oneStep 0.1
#define TIMEFRAME 300