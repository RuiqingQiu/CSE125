#include "GameObj.h"

static unsigned int _totalId;

GameObj::GameObj()
{
	_totalId++;
	_id = _totalId;
}


GameObj::GameObj(double posX, double posY, double posZ)
{
	_totalId++;
	_id = _totalId;
	_x = posX;
	_y = posY;
	_z = posZ;
}

GameObj::~GameObj(){
};

double GameObj::getX(){
	return _x;
}

double GameObj::getY(){
	return _y;
}

double GameObj::getZ(){
	return _z;
}

unsigned int GameObj::getId(){
	return _id;
}


void GameObj::setX(double posX){
	_x = posX;
}

void GameObj::setY(double posX){
	_y = posX;
}

void GameObj::setZ(double posX){
	_z = posX;
}
