#pragma once
#ifndef DEFINITION_H
#define DEFINITION_H


# define M_PI  3.14159265358979323846


//block types
enum BLOCK_TYPE
{
	//BASICCUBE = 100,
	//GLOWINGCUBE = 101,
	//WOODENCUBE = 102,
	//METHCUBE = 3,
	//BGUN = 4,
	//MACE = 5,
	//MALLET = 6,
	//NEEDLE = 7,
	//DISCOUNTWHEEL = 8,
	//TIRE = 9,
	//WOODENWHEEL = 10,

	//BATTLEFIELD = 12,
	//THREEBYTHREE_BASIC = 13,
	//THREEBYTHREE_GLOWING = 14,
	//THREEBYTHREE_WOODEN = 15,

	//WALL = 101,
	//BULLET_1 = 102,


	//enum ModelType{
		//blocks
	BasicCube = 100,
	CrystalCube = 101,
	GlowingCube = 102,
	WoodenCube = 103,
	BLACKCUBE = 104,

	//weapons
	BGun = 200,
	Mace = 201,
	Mallet = 202,
	Needle = 203,
	ALTNEEDLE = 204,
	ALTMACE = 205,
	Turrent = 206,
	Railgun = 207,

	//wheels
	WHEEL_BEGIN = 300,
	Discount = 301,
	Tire = 302,
	WoodenWheel = 303,
	AltTire = 304,
	StoneTire = 305,
	TronWheel = 306,
	WHEEL_END = 350,

	//bases
	BASES_BEGIN = 400,
	THREEBYTHREE_BASIC = 401,
	THREEBYTHREE_GLOWING = 402,
	THREEBYTHREE_WOODEN = 403,
	THREEBYTHREE_WHEEL_DISCOUNT = 404,
	THREEBYTHREE_WHEEL_TIRE = 405,
	THREEBYTHREE_WHEEL_WOODEN = 406,
	THREEBYTHREE_CRYSTAL = 407,
	THREEBYTHREE_BLACK = 408,
	BASES_END = 410,

	//templates
	TEMPLATE_BEGIN = 500,
	TEMPLATE_1 = 501,
	TEMPLATE_2 = 502,
	TEMPLATE_3 = 503,
	TEMPLATE_4 = 504,
	TEMPLATE_5 = 505,
	TEMPLATE_END = 510,

	//Environment
	TREE1 = 600,
	TREE2 = 601,
	TREE3 = 602,

	//Other
	BATTLEFIELD = 700,
	WALL = 701,
	BULLET_1 = 702,
	BULLET = 703,

	CUBEA = 751,
	CUBEB = 752,

	//super battlefield
	BATTLEFIELDINNER = 800,
	BATTLEFIELDOUTER = 801,
	DESERT = 802,

	HILL_PARTICLE = 1000,
	};


// collision type
enum COLLISION_TYPE{
	C_WALLS = 0,
	C_GROUND = 1,
	C_ROBOT = 2,
	C_ROBOT_PARTS = 3,
	C_PROJECTILE = 4,
	C_MELEE = 5,
	
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
	INIT_BATTLE = 15,
	SUICIDE = 16,
	BOOST = 17,
};

enum RANGE{
	MELEE = 0,
	MEDIUM_RANGED = 1,
	FAR_RANGED = 2,
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



#endif 