#ifndef __ShaderSystemDef__
#define __ShaderSystemDef__

enum ModelType{
	//blocks
	BasicCube = 0,
	CrystalCube = 1,
	GlowingCube = 2,
	WoodenCube = 3,

	//weapons
	BGun = 4,
	Mace = 5,
	Mallet = 6,
	Needle = 7,

	//wheels
	WHEEL_BEGIN = 8,
	Discount = 8,
	Tire = 9,
	WoodenWheel = 10,
	WHEEL_END = 11,

	//Other
	BATTLEFIELD = 12,

	BASES_BEGIN = 13,
	THREEBYTHREE_BASIC = 13,
	THREEBYTHREE_GLOWING = 14,
	THREEBYTHREE_WOODEN = 15,
	BASES_END = 16,

	THREEBYTHREE_WHEEL_DISCOUNT = 17,
	THREEBYTHREE_WHEEL_TIRE = 18,
	THREEBYTHREE_WHEEL_WOODEN = 19,

	TEMPLATE_BEGIN = 20,
	TEMPLATE_1 = 20,
	TEMPLATE_2 = 21,
	TEMPLATE_3 = 22,
	TEMPLATE_END = 22,

	//Environment
	TREE1 = 200,
	TREE2 = 201,
	TREE3 = 202,
	BLACKCUBE = 300,
	CUBEA = 301,
	CUBEB = 302,
	WALL = 101,
	BULLET_1 = 102,

	//super battlefield
	BATTLEFIELDINNER = 500,
	BATTLEFIELDOUTER = 501,
};

enum ShaderType{
	REGULAR_SHADER = 0,
	SKYBOX_SHADER = 1,
	REFLECTION_SHADER = 2,
	REFRACTION_SHADER = 3,
	GRASS_SHADER = 4,
	EDGE_SHADER = 5,
	NORMAL_SHADER = 6,
	BLUR_SHADER = 7,
};

enum TEventType{
	TEventDeath = 0,
	TEventParticle = 1,
	TEventTimer = 2,
	TEventScoreboard = 3,

};
#endif