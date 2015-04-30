#ifndef __ShaderSystemDef__
#define __ShaderSystemDef__
enum ModelType{
	//blocks
	BasicCube = 0,
	GlowingCube = 1,
	WoodenCube = 2,

	//weapons
	Mace = 3,
	Mallet = 4,
	Needle = 5,

	//wheels
	Discount = 6,
	Tire = 7,
	WoodenWheel = 8,

	//Other
	BATTLEFIELD = 9,
	
	//new
	PORTAL = 10,

	THREEBYTHREE_BASIC=20,
	THREEBYTHREE_GLOWING=21,
	THREEBYTHREE_WOODEN=22,
	THREEBYTHREE_WHEEL_DISCOUNT=23,
	THREEBYTHREE_WHEEL_TIRE = 24,
	THREEBYTHREE_WHEEL_WOODEN = 25,


	WALL = 101,
	BULLET_1 = 102,

};

enum ShaderType{
	REGULAR_SHADER = 0,
};
#endif