#include "stdafx.h"
#include "blockDescriptions.h"


string blockDescriptions::textPath = "buttons/listItem/";
blockDescriptions::blockDescriptions() {
	addDescriptions(0, 0, 100, 100, false, true);
}

blockDescriptions::blockDescriptions(int x, int y) {
	addDescriptions(x, y, 100, 100, false, true);
}

blockDescriptions::blockDescriptions(int x, int y, bool f) {
	addDescriptions(x, y, 100, 100, f, f);
}

blockDescriptions::blockDescriptions(int x, int y, bool xf, bool yf) {
	addDescriptions(x, y, 100, 100, xf, yf);
}
blockDescriptions::blockDescriptions(int x, int y, int w, int h) {
	addDescriptions(x, y, w, h, false, true);
}

blockDescriptions::blockDescriptions(int x, int y, int w, int h, bool f) {
	addDescriptions(x, y, w, h, f, f);
}

blockDescriptions::blockDescriptions(int x, int y, int w, int h, bool xf, bool yf) {
	addDescriptions(x, y, w, h, xf, yf);
}

blockDescriptions::~blockDescriptions() {
}

void blockDescriptions::addDescriptions(int x, int y, int w, int h, bool xf, bool yf) {
	currDescription = -1;
	//blocks
	descriptions.insert(std::pair<int, guiItem*>(BasicCube, new guiItem(textPath + "blocks/basic_des.png", x, y, w, h, xf, yf)));
	descriptions.insert(std::pair<int, guiItem*>(BLACKCUBE, new guiItem(textPath + "blocks/black_des.png", x, y, w, h, xf, yf)));
	descriptions.insert(std::pair<int, guiItem*>(CrystalCube, new guiItem(textPath + "blocks/crystal_des.png", x, y, w, h, xf, yf)));
	descriptions.insert(std::pair<int, guiItem*>(GlowingCube, new guiItem(textPath + "blocks/glowing_des.png", x, y, w, h, xf, yf)));
	descriptions.insert(std::pair<int, guiItem*>(WoodenCube, new guiItem(textPath + "blocks/wooden_des.png", x, y, w, h, xf, yf)));
	//WEAPONS
	descriptions.insert(std::pair<int, guiItem*>(BGun, new guiItem(textPath + "weapons/bGun_des.png", x, y, w, h, xf, yf)));
	descriptions.insert(std::pair<int, guiItem*>(Mace, new guiItem(textPath + "weapons/mace_des.png", x, y, w, h, xf, yf)));
	//descriptions.insert(std::pair<int, guiItem*>(ALTMACE, new guiItem(textPath + "weapons/mace2_des.png", x, y, w, h, xf, yf) ) );
	descriptions.insert(std::pair<int, guiItem*>(Mallet, new guiItem(textPath + "weapons/mallet_des.png", x, y, w, h, xf, yf)));
	descriptions.insert(std::pair<int, guiItem*>(Needle, new guiItem(textPath + "weapons/needle_des.png", x, y, w, h, xf, yf)));
	//descriptions.insert(std::pair<int, guiItem*>(ALTNEEDLE, new guiItem(textPath + "weapons/needle2_des.png", x, y, w, h, xf, yf) ) );
	descriptions.insert(std::pair<int, guiItem*>(Railgun, new guiItem(textPath + "weapons/railgun_des.png", x, y, w, h, xf, yf)));
	descriptions.insert(std::pair<int, guiItem*>(Turrent, new guiItem(textPath + "weapons/turret_des.png", x, y, w, h, xf, yf)));

	//wheels
	descriptions.insert(std::pair<int, guiItem*>(Discount, new guiItem(textPath + "wheels/discount_des.png", x, y, w, h, xf, yf)));
	descriptions.insert(std::pair<int, guiItem*>(StoneTire, new guiItem(textPath + "wheels/stone_des.png", x, y, w, h, xf, yf)));
	//descriptions.insert(std::pair<int, guiItem*>(Tire, new guiItem(textPath + "wheels/tire_des.png", x, y, w, h, xf, yf) ) );
	descriptions.insert(std::pair<int, guiItem*>(AltTire, new guiItem(textPath + "wheels/tire_des.png", x, y, w, h, xf, yf)));
	descriptions.insert(std::pair<int, guiItem*>(TronWheel, new guiItem(textPath + "wheels/tron_des.png", x, y, w, h, xf, yf)));
	descriptions.insert(std::pair<int, guiItem*>(WoodenWheel, new guiItem(textPath + "wheels/wooden_des.png", x, y, w, h, xf, yf)));

	//bases
	descriptions.insert(std::pair<int, guiItem*>(THREEBYTHREE_BASIC, new guiItem(textPath + "bases/basic_des.png", x, y, w, h, xf, yf)));
	descriptions.insert(std::pair<int, guiItem*>(THREEBYTHREE_BLACK, new guiItem(textPath + "bases/black_des.png", x, y, w, h, xf, yf)));
	descriptions.insert(std::pair<int, guiItem*>(THREEBYTHREE_CRYSTAL, new guiItem(textPath + "bases/crystal_des.png", x, y, w, h, xf, yf)));
	descriptions.insert(std::pair<int, guiItem*>(THREEBYTHREE_GLOWING, new guiItem(textPath + "bases/glowing_des.png", x, y, w, h, xf, yf)));
	descriptions.insert(std::pair<int, guiItem*>(THREEBYTHREE_WOODEN, new guiItem(textPath + "bases/wooden_des.png", x, y, w, h, xf, yf)));

	//templates
	descriptions.insert(std::pair<int, guiItem*>(TEMPLATE_1, new guiItem(textPath + "templates/basic_des.png", x, y, w, h, xf, yf)));
	descriptions.insert(std::pair<int, guiItem*>(TEMPLATE_4, new guiItem(textPath + "templates/black_des.png", x, y, w, h, xf, yf)));
	descriptions.insert(std::pair<int, guiItem*>(TEMPLATE_5, new guiItem(textPath + "templates/crystal_des.png", x, y, w, h, xf, yf)));
	descriptions.insert(std::pair<int, guiItem*>(TEMPLATE_2, new guiItem(textPath + "templates/glowing_des.png", x, y, w, h, xf, yf)));
	descriptions.insert(std::pair<int, guiItem*>(TEMPLATE_3, new guiItem(textPath + "templates/wooden_des.png", x, y, w, h, xf, yf)));

}

void blockDescriptions::update() {
	for (std::map<int, guiItem*>::iterator it = descriptions.begin(); it != descriptions.end(); ++it) {
		it->second->update();
	}
}


void blockDescriptions::draw() {
	if (currDescription > MODELS_BEGIN) descriptions[currDescription]->draw();
}

void blockDescriptions::rePosition(int x, int y, int w, int h) {
	for (std::map<int, guiItem*>::iterator it = descriptions.begin(); it != descriptions.end(); ++it) {
		it->second->rePosition(x, y, w, h);
	}
}