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
	WEAPON1 = 10,
};

//Game Events
enum GameEvents {
	EXPLOSION = 0,
	RESUME = 1,
	PAUSE = 2,
	SCOREBOARD = 3,



};



	//ACTIONS FOR STATE MACHINE
	enum ACTION
	{
		WAIT = 0,
		ADDCLIENT = 1,
		TIMEUP = 2,
		COUNTDOWN = 3,
		RESTART = 4,
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

	//block types
	enum BLOCK_TYPE
	{
		CUBE = 0,
		WHEEL = 1,
		HAMMER = 2,
		MACE = 3,
		NEEDLE = 4,
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