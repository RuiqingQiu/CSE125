#include "GameObj.h"

unsigned int GameObj::_totalId;

GameObj::GameObj()
{
	_id = _totalId;

	_totalId++;
}

// x, y, z, qX, qY, qZ, qW, type, mass
GameObj::GameObj(double posX, double posY, double posZ, double qX, double qY, double qZ, double qW, int type, double mass)
{

	_id = _totalId;
	_totalId++;
	_x = posX;
	_y = posY;
	_z = posZ;
	_qX = qX;
	_qY = qY;
	_qZ = qZ;
	_qW = qW;
	_type = type;
	_mass = mass;
	_isRobot = 0;
	deleted = 0;
}

GameObj::~GameObj(){
	delete rigidBody;

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

double GameObj::getRotX(){
	return _rotX;
}

double GameObj::getRotY(){
	return _rotY;
}

double GameObj::getRotZ(){
	return _rotZ;
}

double GameObj::getqX(){
	return _qX;
}

double GameObj::getqY(){
	return _qY;
}

double GameObj::getqZ(){
	return _qZ;
}

double GameObj::getqW(){
	return _qW;
}

unsigned int GameObj::getId(){
	return _id;
}


void GameObj::setX(double posX){
	_x = posX;
}

void GameObj::setY(double posY){
	_y = posY;
}

void GameObj::setZ(double posZ){
	_z = posZ;
}

void GameObj::setRotX(double rotX){
	_rotX = rotX;
}

void GameObj::setRotY(double rotY){
	_rotY = rotY;
}

void GameObj::setRotZ(double rotZ){
	_rotZ = rotZ;
}

void GameObj::setqX(double qX){
	_qX = qX;
}

void GameObj::setqY(double qY){
	_qY = qY;
}

void GameObj::setqZ(double qZ){
	_qZ = qZ;
}

void GameObj::setqW(double qW){
	_qW = qW;
}

int GameObj::getType()
{
	return _type;
}

void GameObj::setType(int type)
{
	_type = type;
}

double GameObj::getMass(){
	return _mass;
}


void GameObj::setMass(double mass){
	_mass = mass;
}

void GameObj::setRigidBody(btRigidBody* RB)
{
	rigidBody = RB;
}

int GameObj::getBlockType()
{
	return _blockType;
}

void GameObj::setBlockType(int bType)
{
	_blockType = bType;
}

void GameObj::setIsRobot(int b)
{
	_isRobot = b;
}

int GameObj::getIsRobot()
{
	return _isRobot;
}

void GameObj::setBelongTo(GameObj* r)
{
	_belongTo = r;
}

GameObj* GameObj::getBelongTo()
{
	return _belongTo;
}


void GameObj::addConstraint(GameObj* o)
{
	    btFixedConstraint *joint6DOF;
		btTransform localA, localB, toground;
	
		bool useLinearReferenceFrameA = true;
	
		localA.setIdentity(); localB.setIdentity();
	
		double centerX = (this->getX() + o->getX())/2;
		double centerY = (this->getY() + o->getY()) / 2;
		double centerZ = (this->getZ() + o->getZ()) / 2;

		localA.setOrigin(btVector3(this->getX() - centerX, this->getY() - centerY, this->getZ() - centerZ));

		localB.setOrigin(btVector3(o->getX() - centerX, o->getY() - centerY, o->getZ() - centerZ));
		btTransform frameInA;
		btTransform frameInB;

		this->getRigidBody()->getMotionState()->getWorldTransform(frameInA);
		o->getRigidBody()->getMotionState()->getWorldTransform(frameInB);
	
		//joint6DOF = new btFixedConstraint(*(this->getRigidBody()), *(o->getRigidBody()), frameInA, frameInB);
		joint6DOF = new btFixedConstraint(*(this->getRigidBody()), *(o->getRigidBody()), localB, localA);
		/*joint6DOF->setParam(BT_CONSTRAINT_STOP_CFM, 1, 0);
		joint6DOF->setParam(BT_CONSTRAINT_STOP_CFM, 1, 1);
		joint6DOF->setParam(BT_CONSTRAINT_STOP_CFM, 1, 2);
		joint6DOF->setParam(BT_CONSTRAINT_STOP_CFM, 1, 3);
		joint6DOF->setParam(BT_CONSTRAINT_STOP_CFM, 1, 4);
		joint6DOF->setParam(BT_CONSTRAINT_STOP_CFM, 1, 5);
	
		joint6DOF->setParam(BT_CONSTRAINT_STOP_ERP, 0.5f, 0);
		joint6DOF->setParam(BT_CONSTRAINT_STOP_ERP, 0.5f, 1);
	
		joint6DOF->setParam(BT_CONSTRAINT_STOP_ERP, 0.5f, 2);
	
		joint6DOF->setParam(BT_CONSTRAINT_STOP_ERP, 0.5f, 3);
	
		joint6DOF->setParam(BT_CONSTRAINT_STOP_ERP, 0.5f, 4);
	
		joint6DOF->setParam(BT_CONSTRAINT_STOP_ERP, 0.5f, 5);*/
		Constraint* c = new Constraint();
		c->_joint6DOF = joint6DOF;
		constraints.push_back(c);
		c = new Constraint();
		c->_joint6DOF = joint6DOF;
		o->getConstraints()->push_back(c);
}

void GameObj::deleteConstraints(std::map< btCollisionObject*, GameObj*>* pair)
{
	std::vector<Constraint*>::iterator it;
	for (it = constraints.begin(); it != constraints.end(); it++)
	{
		Constraint* c = (*it);
		GameObj* other;
		if (&c->_joint6DOF->getRigidBodyA() == this->getRigidBody())
		{
			other = pair->find(&c->_joint6DOF->getRigidBodyB())->second;
		}
		else
		{
			other = pair->find(&c->_joint6DOF->getRigidBodyA())->second;
		}

		//delete(c->_joint6DOF);
		c->_joint6DOF = nullptr;
		other->deleteInvalidConstraints();
	}
	constraints.clear();
}

void GameObj::deleteInvalidConstraints()
{
	std::vector<Constraint*>::iterator it;
	std::vector<Constraint*> new_constraints;
	for (it = constraints.begin(); it != constraints.end(); it++)
	{
		Constraint* c = (*it);
		if (c->_joint6DOF == nullptr)
		{
			delete(c);
		}
		else
		{
			new_constraints.push_back(c);
		}
	}
	constraints = new_constraints;
}

btRigidBody* GameObj::getRB()
{
	return rigidBody;
}

std::vector<Constraint *>* GameObj::getConstraints()
{
	return &constraints;
}

void GameObj::setCollisionType(int t)
{
	_collisionType = t;
}
int GameObj::getCollisionType()
{
	return _collisionType;
}
void GameObj::setDeleted()
{
	deleted = 1;
}
int GameObj::getDeleted()
{
	return deleted;
}

void GameObj::setIsWeapon()
{
	_isWeapon = 1;
}

int GameObj::getIsWeapon()
{
	return _isWeapon;
}

void GameObj::setDamage(double d )
{
	_damage = d;
}
double GameObj::getDamage()
{
	return _damage;
}

void GameObj::setHealth(double h)
{
	_health = h;
}
void GameObj::setMaxHealth(double h)
{
	_maxHealth = h;
	_health = h;
}
double GameObj::getHealth()
{
	return _health;
}
double GameObj::getMaxHealth()
{
	return _maxHealth;
}
double GameObj::applyDamage(double h){
	_health -= h;
	return _health;
}


void GameObj::setLeftID(int i){ left_id = i; }
void GameObj::setRightID(int i){ right_id = i; }
void GameObj::setFrontID(int i){ front_id = i; }
void GameObj::setBackID(int i){ back_id = i; }
void GameObj::setBelowID(int i){ below_id = i; }


int GameObj::getLeftID(){ return left_id; }
int GameObj::getRightID(){ return right_id; }
int GameObj::getFrontID(){ return front_id; }
int GameObj::getBackID(){ return back_id; }
int GameObj::getBelowID(){ return below_id; }

void GameObj::setBuildID(int i)
{
	buildObj_id = i;
}


int GameObj::getBuildID()
{
	return buildObj_id;
}