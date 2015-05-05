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

	BLOCKYGUN = 9,
	//Other
	BATTLEFIELD = 10,

	THREEBYTHREE_BASIC = 11,
	THREEBYTHREE_GLOWING = 12,
	THREEBYTHREE_WOODEN = 13,
	THREEBYTHREE_WHEEL_DISCOUNT = 14,
	THREEBYTHREE_WHEEL_TIRE = 15,
	THREEBYTHREE_WHEEL_WOODEN = 16,

	TEMPLATE_1 = 21,
	TEMPLATE_2 = 22,
	TEMPLATE_3 = 23,

	WALL = 101,
	BULLET_1 = 102,

};

enum ShaderType{
	REGULAR_SHADER = 0,
	SKYBOX_SHADER = 1,
	REFLECTION_SHADER = 2,
	REFRACTION_SHADER = 3,
	GRASS_SHADER = 4,
	EDGE_SHADER = 5
};
#endif