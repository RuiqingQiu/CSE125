#include "Robot.h"
#include "GOBox.h"


Robot::Robot(int cid, char* name)
	:GameObj()
{
	_r_cid = cid;
	_name = name;
	setIsRobot(1);
	setCollisionType(C_ROBOT);
	_state = PS_BUILD;
}


Robot::~Robot()
{
	delete(vehicle);
}


void Robot::setCID(int cid)
{
	_r_cid = cid;
}

void Robot::setTakeDowns(int takedowns)
{
	_takedowns = takedowns;
}

void Robot::setDeaths(int deaths){ }
void Robot::setName(char* name){ _name = name; }

int Robot::getCID(){ return _r_cid; }
int Robot::getTakeDowns(){ return _takedowns; }
int Robot::getDeaths(){ return _deaths; }
char* Robot::getName(){ return _name; }


btRaycastVehicle * Robot::getVehicle()
{
	return vehicle;
}

void Robot::setWidth(double w)
{
	_width = w;
}
void Robot::setHeight(double h)
{
	_height = h;
}
void Robot::setDepth(double d)
{
	_depth = d;
}

double Robot::getWidth()
{
	return _width;
}

double Robot::getHeight()
{
	return _height;
}
double Robot::getDepth()
{
	return _depth;
}

void Robot::createVehicle(btDynamicsWorld* dynamicWorld, double width, double height, double depth, std::map< btCollisionObject*, GameObj*> * map)
{

	//GOBox* boxShape = new GOBox( x,  y,  z,  qX,  qY,  qZ,  qW,  mass,  width,  height,  depth);
	double x = this->getX();
	double y= this->getY();
	double z= this->getZ();
	double qX= this->getqX();
	double qY= this->getqY();
	double qZ= this->getqZ();
	double qW= this->getqW();
	double mass = this->getMass();
	setWidth(width);
	setHeight(height);
	setDepth(depth);
	btBoxShape* m_pBoxShape = new btBoxShape(btVector3(width/2, height/2, depth/2));

	btTransform chassisLS;
	chassisLS.setIdentity();
	chassisLS.setOrigin(btVector3(x, y, z));

	btCompoundShape * m_pCompoundShape = new btCompoundShape();
	m_pCompoundShape->addChildShape(chassisLS, m_pBoxShape);
	


	btDefaultMotionState* pMotionState = new btDefaultMotionState(btTransform(btQuaternion(qX, qY, qZ, qW), btVector3(x, y, z)));
	btVector3 intertia(0, 0, 0);
	m_pBoxShape->calculateLocalInertia(mass, intertia);

	btRigidBody::btRigidBodyConstructionInfo bodyInfo(mass, pMotionState, m_pCompoundShape, intertia);
	bodyInfo.m_friction = 0.6f;
	bodyInfo.m_restitution = 0.1f;
	bodyInfo.m_linearDamping = 0.2f;
	bodyInfo.m_angularDamping = 0.2f;

	btRigidBody* m_pBody = new btRigidBody(bodyInfo);
	m_pBody->setActivationState(DISABLE_DEACTIVATION);

	btRaycastVehicle::btVehicleTuning tuning;

	tuning.m_maxSuspensionTravelCm = 500.0f;
	tuning.m_suspensionCompression = 4.4f;
	tuning.m_suspensionDamping = 0.3f;
	tuning.m_frictionSlip = 1000.0f;
	tuning.m_suspensionStiffness = 5.0f;

	btDefaultVehicleRaycaster* m_pVehicleRaycaster = new btDefaultVehicleRaycaster(dynamicWorld);
	btRaycastVehicle* m_pVehicle = new btRaycastVehicle(tuning, m_pBody, m_pVehicleRaycaster);

	this->vehicle = m_pVehicle;
	//dynamicWorld->addRigidBody(m_pBody, COL_PLAYER, playerCollisions);
	dynamicWorld->addRigidBody(m_pBody);
	dynamicWorld->addAction(m_pVehicle);
	map->insert(std::pair<btCollisionObject*, GameObj*>(m_pBody, this));
	//m_pBody->setLinearFactor(btVector3(0, 0, 0));
	//m_pBody->setAngularFactor(btVector3(0, 0, 0));
	m_pVehicle->setCoordinateSystem(0, 1, 2);

	btVector3 wheelDirectionCS0(0, -1, 0);
	btVector3 wheelAxleCS(-1, 0, 0);
	btScalar suspensionRestLength = 0.6f;
	btScalar wheelRadius = 0.5f;
	btScalar connectionHeight = 0.2f;

	{
		btVector3 connectionPointCS0((width / 2.0f - width/10.0f), connectionHeight, (depth / 2.0f - depth / 8.0f));
		m_pVehicle->addWheel(connectionPointCS0, wheelDirectionCS0, wheelAxleCS, suspensionRestLength, wheelRadius, tuning, true);
	}
{
	btVector3 connectionPointCS0(-(width / 2.0f - width / 10.0f), connectionHeight, (depth / 2.0f - depth / 8.0f));
	m_pVehicle->addWheel(connectionPointCS0, wheelDirectionCS0, wheelAxleCS, suspensionRestLength, wheelRadius, tuning, true);
}
{
	btVector3 connectionPointCS0((width / 2.0f - width / 10.0f), connectionHeight, -(depth / 2.0f - depth / 8.0f));
	m_pVehicle->addWheel(connectionPointCS0, wheelDirectionCS0, wheelAxleCS, suspensionRestLength, wheelRadius, tuning, false);
}
{
	btVector3 connectionPointCS0(-(width / 2.0f - width / 10.0f), connectionHeight, -(depth / 2.0f - depth / 8.0f));
	m_pVehicle->addWheel(connectionPointCS0, wheelDirectionCS0, wheelAxleCS, suspensionRestLength, wheelRadius, tuning, false);
}

int i;
for ( i = 0; i < m_pVehicle->getNumWheels(); ++i)
{
	btWheelInfo& rWheel = m_pVehicle->getWheelInfo(i);

	rWheel.m_suspensionStiffness = 100.0f;
	rWheel.m_frictionSlip = 1000.0f;
	rWheel.m_rollInfluence = 0.1f;
	rWheel.m_wheelsDampingCompression = 1.01f;
	rWheel.m_wheelsDampingRelaxation = 100.01f;
}


}

void Robot::createRigidBody(std::map< btCollisionObject*, GameObj*> * map)
{
	return;
}

btRigidBody* Robot::getRigidBody()
{
	if (vehicle == nullptr) return nullptr;
	return this->vehicle->getRigidBody();
}

std::vector<Weapon*> Robot::getWeapons()
{
	return weapons;
}


void Robot::addWeapon(Weapon * w)
{
	weapons.push_back(w);
}



void Robot::shoot(std::vector<std::pair<GameObj*, double>>* projectiles)
{
	std::vector<Weapon*>::iterator it;
	for (it = weapons.begin(); it != weapons.end(); it++)
	{
		if((*it)->getRange() != MELEE)
		{
			RangedWeapon* w = (RangedWeapon*)(*it);
			if (w->readyToShoot())
			{
				double rbDepth = ((GOBox*)w->getGameObj())->getDepth()/2 + w->getPDepth() / 2 + 0.6f;
				btTransform rbTrans = w->getGameObj()->getRigidBody()->getWorldTransform();
				btVector3 relativeDisplacement = btVector3(0, 0, -rbDepth);
				btVector3 boxRot = rbTrans.getBasis()[2];
				boxRot.normalize();
				btVector3 correctedDisplacement = boxRot * -rbDepth; // /2
				double x = rbTrans.getOrigin().getX() + correctedDisplacement.getX();
				double y = rbTrans.getOrigin().getY() + correctedDisplacement.getY();
				double z = rbTrans.getOrigin().getZ() + correctedDisplacement.getZ();

				GameObj* proj = new GOBox(x, y, z, rbTrans.getRotation().getX(), rbTrans.getRotation().getY(), rbTrans.getRotation().getZ(), rbTrans.getRotation().getW(),
					w->getPMass(), w->getPWidth(), w->getPHeight(), w->getPDepth());
				proj->setCollisionType(C_PROJECTILE);
				proj->setDamage(w->getDamage());
				proj->setBelongTo(this);
				proj->setBlockType(w->getPBlockType());
				projectiles->push_back(std::make_pair(proj, w->getPInitForce()));
				w->setLastShot();
			}
		}
	}
}

void Robot::clearWeapons()
{
	weapons.clear();
}

void Robot::setWeapons(std::vector<Weapon*> w)
{
	weapons = w;
}

void Robot::setHealth(double h)
{
	_health = h;
}
void Robot::setMaxHealth(double h)
{
	_maxHealth = h;
	_health = h;
}
double Robot::getHealth()
{
	return _health;
}
double Robot::getMaxHealth()
{
	return _maxHealth;
}
double Robot::applyDamage(double h){
	_health -= h;
	return _health;
}

void Robot::nextState()
{
	_state = (_state + 1) % 3;
}
int Robot::getState()
{
	return _state;
}

void Robot::setState(int s)
{
	_state = s;
}