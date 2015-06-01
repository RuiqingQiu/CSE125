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
	_id = _totalId+5;
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
	deathTimer = NULL;
	setBelongTo(nullptr);
	_deathSent = 0;
}

GameObj::~GameObj(){
	//delete rigidBody;
}

double GameObj::getX(){
	return _x;
}

double GameObj::getHealing()
{
	return blockHealing;
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

void GameObj::setSpeedMultiplier(double s)
{
	speedMultiplier = s;
}
double GameObj::getSpeedMultiplier()
{
	return speedMultiplier;
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

void GameObj::setId(unsigned int i)
{
	_id = i;
}


int GameObj::getIsWheel()
{
	return _isWheel;
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
	switch (bType){
	case BasicCube:
	{
			  _mass = 15;
			  _health = 370;
			  _collisionType = C_ROBOT_PARTS;
			  break;
	}
	case GlowingCube:
	{
						_mass = 17;
						_health = 250;
						blockForce = 300;
						_collisionType = C_ROBOT_PARTS;
					  break;
	}
	case WoodenCube:
	{
					   _mass = 10;
					   _health = 150;
					   _collisionType = C_ROBOT_PARTS;
					  break;
	}


	case CrystalCube:
	{
					   _mass = 15;
					   _health = 220;
					   blockHealing = 40;
					   _collisionType = C_ROBOT_PARTS;
					   break;
	}
	case BLACKCUBE:
	{
						_mass = 17;
						_health = 250;
						blockForce = -300;
						_collisionType = C_ROBOT_PARTS;
						break;
	}


	case BGun:{
		_isWeapon = 1;
		_isRanged = 1;
		_health = 200;
		_mass = 30;
		_collisionType = C_ROBOT_PARTS;
		break;

	}
	case Railgun:
	{
				 _isWeapon = 1;
				 _isRanged = 1;
				 _health = 240;
				 _mass = 35;
				 _collisionType = C_ROBOT_PARTS;
					  break;
	}
	case Mace:
	{
				 _isWeapon = 1;
				 _mass = 35;
				 _health = 300;
				 _collisionType = C_MELEE;
					  break;
	}
	case Mallet:
	{
				   _isWeapon = 1;
				   _mass = 40;
				   _health = 325;
				   _collisionType = C_MELEE;
					  break;
	}
	case Needle:
	{
				   _isWeapon = 1;
				   _health = 250;
				   _mass = 8;
				   _collisionType = C_MELEE;
					  break;
	}
	case StoneTire:
	{
					  _isWheel = 1;
					  speedMultiplier = 1;
					  break;
	}
	case WoodenWheel:
	{
						_isWheel = 1;
						speedMultiplier = 2;
						break;
	}
	case Discount:
	{
						  _isWheel = 1;
						  speedMultiplier = 4;
						  break;
	}

	case AltTire:
	{
				 std::cout << " in tire " << std::endl;
				 _isWheel = 1;
				 speedMultiplier = 7;
						  break;
	}
	case Tire:
	{
					std::cout << " in tire alt" << std::endl;
					_isWheel = 1;
					_blockType = AltTire;
					speedMultiplier = 7;
					break;
	}
	case TronWheel:
	{
					 _isWheel = 1;
					 speedMultiplier = 10;
					 break;
	}

	case THREEBYTHREE_BASIC:
	{
							   _mass = 135;
							   _health = 3330;
							   _collisionType = C_ROBOT;
						  break;
	}
	case THREEBYTHREE_GLOWING:
	{
								 _mass = 153;
								 _health = 2250;
								 blockForce = 2700;
								 _collisionType = C_ROBOT;
							   break;
	}
	case THREEBYTHREE_WOODEN:
	{
								_mass = 90;
								_health = 1350;
								_collisionType = C_ROBOT;
							   break;
	}

	case THREEBYTHREE_BLACK:
	{
								_mass = 153;
								_health = 2250;
								blockForce = -2700;
								_collisionType = C_ROBOT;
								break;
	}

	case THREEBYTHREE_CRYSTAL:
	{
								_mass = 135;
								_health = 1980;
								blockHealing = 360;
								_collisionType = C_ROBOT;
								break;
	}

	case WALL:
	{
				 _collisionType = C_WALLS;
		break;
	}
	case BATTLEFIELD:
	{
		_collisionType = C_GROUND;
		break;
	}
	case BULLET_1:
	{
		_collisionType = C_PROJECTILE;
		break;
	}
	case BULLET:
	{
		_collisionType = C_PROJECTILE;
		blockSlow = 0.1;
		//CHANGE THIS VALUE, it is set to 1 for testing purposes right now
		break;
	}

	default:{
		std::cout << "WRONG BLOCK TYPE " << bType << std::endl;

		_mass = 10;
		_health = 200;
		_collisionType = C_ROBOT_PARTS;
		break;
	}
	}
}
double GameObj::getBlockForce()
{
	return blockForce;
}
void GameObj::setIsRobot(int b)
{
	_isRobot = b;
}

double GameObj::getBlockSlow()
{
	return blockSlow;
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

int GameObj::getIsRangedWeapon()
{
	return _isRanged;
}

Constraint* GameObj::addConstraint(GameObj* o)
{
	    btFixedConstraint *joint6DOF;
		btTransform localA, localB, toground;
	
		bool useLinearReferenceFrameA = true;
	
		localA.setIdentity(); localB.setIdentity();
	
		double centerX = (this->getX() + o->getX())/2;
		double centerY = (this->getY() + o->getY()) / 2;
		double centerZ = (this->getZ() + o->getZ()) / 2;
		
		
		//********************CONSTRAINTS ROTATION NEED TO BE FIXED!!!!!!!!!!!!!!**********************************//
		btTransform frameInA;
		btTransform frameInB;


		this->getRigidBody()->getMotionState()->getWorldTransform(frameInA);
		o->getRigidBody()->getMotionState()->getWorldTransform(frameInB);

		btVector3 vA = frameInA.getOrigin();
		btTransform globalTrans;
		globalTrans.setIdentity();
		globalTrans.setOrigin(vA);


		localA = frameInA.inverse() * globalTrans;
		localB = frameInB.inverse() * globalTrans;
		/*btScalar yawA, pA, rA, yawB, pB, rB;
		frameInA.getBasis().getEulerZYX(yawA, pA, rA);
		frameInB.getBasis().getEulerZYX(yawB, pB, rB);
		localA.getBasis().setEulerZYX(yawA, pA, rA);
		localB.getBasis().setEulerZYX(yawB, pB, rB);
		localA.setRotation(frameInA.getRotation());
		*/
		//localA.setOrigin(frameInA.getOrigin());
		//localB.setOrigin(frameInB.getOrigin());
		//a
		//btMatrix3x3 matrix;
		//matrix.setEulerZYX(-az, -ay, -ax);
		//localA.setOrigin(matrix*localpointinA);

		//b
		//btMatrix3x3 matrix;
		//matrix.setEulerZYX(-bz, -by, -bx);
		//localA.setOrigin(matrix*localpointinA);
		//
		//localA.setOrigin(btVector3(this->getX() - centerX, this->getY() - centerY, this->getZ() - centerZ));

		//localB.setOrigin(btVector3(o->getX() - centerX, o->getY() - centerY, o->getZ() - centerZ));
		
		//localA.setRotation(frameInA.getRotation());
		//localB.setRotation(frameInB.getRotation());


		//joint6DOF = new btFixedConstraint(*(this->getRigidBody()), *(o->getRigidBody()), frameInA, frameInB);
		joint6DOF = new btFixedConstraint(*(this->getRigidBody()), *(o->getRigidBody()), localA , localB);


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
		o->getConstraints()->push_back(c);
		return c;
}

int GameObj::deleteConstraints()
{
    std::vector<Constraint*> deleted;
	std::vector<Constraint*>::iterator it;
	for (it = constraints.begin(); it != constraints.end(); it++)
	{
		Constraint* c = (*it);
		GameObj* other;
		if (&c->_joint6DOF->getRigidBodyA() == this->getRigidBody())
		{
			other = (GameObj*)(&(c->_joint6DOF->getRigidBodyB()))->getUserPointer();
		}
		else
		{
			other = (GameObj*) (&(c->_joint6DOF->getRigidBodyA()))->getUserPointer();
		}

		c->_joint6DOF = nullptr;
		other->deleteInvalidConstraints();
		deleted.push_back(c);
	}
	constraints.clear();

	if (!getIsRobot())
	{
		setDeleted();
	}

	for (it = deleted.begin(); it != deleted.end(); it++)
	{
		delete(*it);
	}
	return 0;
}

int GameObj::deleteInvalidConstraints()
{
	std::vector<Constraint*>::iterator it;
	std::vector<Constraint*> new_constraints;

	for (it = constraints.begin(); it != constraints.end(); it++)
	{
		Constraint* c = (*it);
		if (c->_joint6DOF != nullptr)
		{
			new_constraints.push_back(c);
		}
	}
	constraints = new_constraints;
	return 0;
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
	if (deathTimer == NULL)
	deathTimer = clock();
}

void GameObj::setImmediateDeleted()
{
	if (deathTimer == NULL)
		deathTimer = clock() - DEATH_DELAY * CLOCKS_PER_SEC;
}

int GameObj::getHasDeleted()
{
	return (deathTimer == NULL) ? 0 : 1;
}

int GameObj::getDeleted()
{
	//return (deathTimer != NULL);
	//bugs overthere 
	//ConsoleApplication1.exe!GameObj::getDeleted() Line 491	C++
	//ConsoleApplication1.exe!GameLogic::cleanDataStructures() Line 693	C++
	//ConsoleApplication1.exe!GameLogic::postPhyLogic() Line 618	C++
	//ConsoleApplication1.exe!GameLogic::gameLoop() Line 330	C++
	if (deathTimer == NULL)
	{
		return 0;
	}
	return (((double)(clock() - deathTimer) / CLOCKS_PER_SEC) > DEATH_DELAY);
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

double GameObj::getDoT()
{
	return DoT;
}
double GameObj::getHealth()
{
	return (_health < 0) ? 0 : _health;
}
double GameObj::getMaxHealth()
{
	return _maxHealth;
}




int GameObj::applyDotDamage(){
	if (DoT <= 0){
		DoTTick = 0;
		DoT = 0;
		DoTFrom = -1;
	}
	applyDamage(DoTTick);
	DoT -= DoTTick;
	return DoTFrom;
	
}

int GameObj::getDoTFrom()
{
	return DoTFrom;
}

double GameObj::getDoTTick(){
	return DoTTick;
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


Weapon* GameObj::getWeapon(){
	return weapon;
}


void GameObj::setWeapon(int mor, int weapontype)
{
	if (mor == MELEE)
	{
		weapon = new MeleeWeapon(weapontype);
		this->setDamage(weapon->getDamage());
	}
	else
	{
		weapon = new RangedWeapon(weapontype);
		
	}
	setIsWeapon();
}

void GameObj::setInitForce(double d)
{
	_initForce = d;
}
double GameObj::getInitForce()
{
	return _initForce;
}

void GameObj::addSpeedMultipler(double s)
{
	speedMultiplier += s;
}