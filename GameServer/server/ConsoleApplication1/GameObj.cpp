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
	

		localA.setOrigin(btVector3(0, 0, 0));
	
		localB.setOrigin(btVector3(0, 0, 0));
		//cout << "last is " << last << endl;
		//cout << "current is " << i << endl;
		btTransform frameInA;
		btTransform frameInB;

		this->getRigidBody()->getMotionState()->getWorldTransform(frameInA);
		o->getRigidBody()->getMotionState()->getWorldTransform(frameInB);
	
		joint6DOF = new btFixedConstraint(*(this->getRigidBody()), *(o->getRigidBody()), frameInA, frameInB);

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