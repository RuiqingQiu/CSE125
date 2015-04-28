#include "Robot.h"


Robot::Robot(int cid, char* name)
	:GameObj()
{
	_r_cid = cid;
	_name = name;
	setIsRobot(1);
	incOid(4);
}


Robot::~Robot()
{
}


void Robot::setID(int cid)
{
	_r_cid = cid;
}

void Robot::setTakeDowns(int takedowns)
{
	_takedowns = takedowns;
}

void Robot::setDeaths(int deaths){ }
void Robot::setName(char* name){ _name = name; }
void Robot::setWeapon1(Weapon* weapon){ _w1 = weapon; }
void Robot::setWeapon2(Weapon* weapon){ _w2 = weapon; }
void Robot::setWeapon3(Weapon* weapon){ _w3 = weapon; }

int Robot::getID(){ return _r_cid; }
int Robot::getTakeDowns(){ return _takedowns; }
int Robot::getDeaths(){ return _deaths; }
char* Robot::getName(){ return _name; }
Weapon* Robot::getWeapon1(){ return _w1; }
Weapon* Robot::getWeapon2(){ return _w2; }
Weapon* Robot::getWeapon3(){ return _w3; }

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
	btBoxShape* m_pBoxShape = new btBoxShape(btVector3(width, height, depth));

	btTransform chassisLS;
	chassisLS.setIdentity();
	chassisLS.setOrigin(btVector3(x, y, z));

	btCompoundShape * m_pCompoundShape = new btCompoundShape();
	m_pCompoundShape->addChildShape(chassisLS, m_pBoxShape);
	


	btDefaultMotionState* pMotionState = new btDefaultMotionState(btTransform(btQuaternion(qX, qY, qZ, qW), btVector3(0, y, 0)));
	btVector3 intertia;
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


	m_pVehicle->setCoordinateSystem(0, 1, 2);

	btVector3 wheelDirectionCS0(0, -1, 0);
	btVector3 wheelAxleCS(-1, 0, 0);
	btScalar suspensionRestLength = 0.6f;
	btScalar wheelRadius = 0.5f;
	btScalar connectionHeight = 0.2f;

	{
		btVector3 connectionPointCS0(1.5f, connectionHeight, 1.5f);
		m_pVehicle->addWheel(connectionPointCS0, wheelDirectionCS0, wheelAxleCS, suspensionRestLength, wheelRadius, tuning, true);
	}
{
	btVector3 connectionPointCS0(-1.5f, connectionHeight, 1.5f);
	m_pVehicle->addWheel(connectionPointCS0, wheelDirectionCS0, wheelAxleCS, suspensionRestLength, wheelRadius, tuning, true);
}
{
	btVector3 connectionPointCS0(1.5f, connectionHeight, -1.5f);
	m_pVehicle->addWheel(connectionPointCS0, wheelDirectionCS0, wheelAxleCS, suspensionRestLength, wheelRadius, tuning, false);
}
{
	btVector3 connectionPointCS0(-1.5f, connectionHeight, -1.5f);
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
	return this->vehicle->getRigidBody();
}
