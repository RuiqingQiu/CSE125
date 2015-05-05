#ifndef __ShaderSystemDef__
#define __ShaderSystemDef__
enum ModelType{
	//blocks
	BasicCube = 0,
	GlowingCube = 1,
	WoodenCube = 2,

	//weapons
	BGun = 3,
	Mace = 4,
	Mallet = 5,
	Needle = 6,

	//wheels
	WHEEL_BEGIN = 7,
	Discount = 7,
	Tire = 8,
	WoodenWheel = 9,
	WHEEL_END = 9,

	//Other
	BATTLEFIELD = 10,

	BASES_BEGIN = 11,
	THREEBYTHREE_BASIC = 11,
	THREEBYTHREE_GLOWING = 12,
	THREEBYTHREE_WOODEN = 13,
	BASES_END = 13,

	THREEBYTHREE_WHEEL_DISCOUNT = 14,
	THREEBYTHREE_WHEEL_TIRE = 15,
	THREEBYTHREE_WHEEL_WOODEN = 16,

	TEMPLATE_BEGIN = 21,
	TEMPLATE_1 = 21,
	TEMPLATE_2 = 22,
	TEMPLATE_3 = 23,
	TEMPLATE_END = 23,

	WALL = 101,
	BULLET_1 = 102,

};

enum ShaderType{
	REGULAR_SHADER = 0,
	SKYBOX_SHADER = 1,
	REFLECTION_SHADER = 2,
	REFRACTION_SHADER = 3,
	GRASS_SHADER = 4,
	EDGE_SHADER = 5,
	NORMAL_SHADER = 6
};
#endif