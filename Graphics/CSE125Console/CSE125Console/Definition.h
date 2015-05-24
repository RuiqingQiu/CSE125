#ifndef __ShaderSystemDef__
#define __ShaderSystemDef__

enum ModelType{
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
	BATTLEFIELD_SHADER = 8,
	MATERIAL_SHADER = 9,
	LIGHTS_SHADER= 10
};

enum TEventType{
	TEventDeath = 0,
	TEventParticle = 1,
	TEventTimer = 2,
	TEventScoreboard = 3,
	TEventUpdateHealth = 4,
	TEventCollisionHappen = 5,
	TEventWaiting = 6,
	TEventEmergency = 7,
	TEventHillUpdate = 8,
	TEventPlayerHillUpdate = 9,
	TEventDefault = -1
};
#endif