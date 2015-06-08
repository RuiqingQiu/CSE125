#include "Robot.h"
#include "GOBox.h"


Robot::Robot(int cid, char* name)
	:GameObj()
{
	_r_cid = cid;
	_name = name;
	setIsRobot(1);
	_state = PS_BUILD;
	setBelongTo(this);
	isSlowed = NULL;
	boostCD = NULL;
}


Robot::~Robot()
{
	//delete(vehicle);
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
int Robot::getJustBuilt()
{
	return justBuilt;
}
void Robot::setJustBuilt(int b)
{
	justBuilt = b;
}
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

void Robot::createVehicle(btDynamicsWorld* dynamicWorld, double width, double height, double depth)//, std::map< btCollisionObject*, GameObj*> * map)
{
	printf("%i %i %i\n", this->getCollisionType(), this->getIsRobot(), this->getState());
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
	btBoxShape* m_pBoxShape = new btBoxShape(btVector3(width/2.0f, height/2.0f, depth/2.0f));

	btTransform chassisLS;
	chassisLS.setIdentity();
	chassisLS.setOrigin(btVector3(x, y, z));

	btCompoundShape * m_pCompoundShape = new btCompoundShape();
	m_pCompoundShape->addChildShape(chassisLS, m_pBoxShape);


	btDefaultMotionState* pMotionState = new btDefaultMotionState(btTransform(btQuaternion(qX, qY, qZ, qW), btVector3(x, y, z)));
	btVector3 intertia(0, 0, 0);
	m_pBoxShape->calculateLocalInertia(mass, intertia);

	//btRigidBody::btRigidBodyConstructionInfo bodyInfo(mass, pMotionState, m_pCompoundShape, intertia);
	//bodyInfo.m_friction = 0.6f;
	//bodyInfo.m_restitution = 0.1f;
	//bodyInfo.m_linearDamping = 0.2f;
	//bodyInfo.m_angularDamping = 0.2f;

	btRigidBody::btRigidBodyConstructionInfo chassisInfo(mass, pMotionState, m_pBoxShape, intertia);
	chassisInfo.m_friction = 0.6f;
	chassisInfo.m_restitution = 0.1f;
	chassisInfo.m_linearDamping = 0.2f;
	chassisInfo.m_angularDamping = 0.2f;


	btRigidBody* m_chassis = new btRigidBody(chassisInfo);
	//btRigidBody* m_pBody = new btRigidBody(bodyInfo);
	m_chassis->setActivationState(DISABLE_DEACTIVATION);
	//m_pBody->setActivationState(DISABLE_DEACTIVATION);

	btRaycastVehicle::btVehicleTuning tuning;

	tuning.m_maxSuspensionTravelCm = 500.0f;
	tuning.m_suspensionCompression = 4.4f;
	tuning.m_suspensionDamping = 0.3f;
	tuning.m_frictionSlip = 1000.0f;
	tuning.m_suspensionStiffness = 5.0f;

	btDefaultVehicleRaycaster* m_pVehicleRaycaster = new btDefaultVehicleRaycaster(dynamicWorld);
	//btRaycastVehicle* m_pVehicle = new btRaycastVehicle(tuning, m_pBody, m_pVehicleRaycaster);
	btRaycastVehicle* m_pVehicle = new btRaycastVehicle(tuning, m_chassis, m_pVehicleRaycaster);



	this->vehicle = m_pVehicle;
	//dynamicWorld->addRigidBody(m_pBody, COL_PLAYER, playerCollisions);
	//dynamicWorld->addRigidBody(m_pBody);
	m_chassis->setUserPointer(this);
	m_chassis->setAngularFactor(btVector3(0, 1, 0));
	dynamicWorld->addRigidBody(m_chassis);
	//m_chassis->setAngularFactor(btVector3(0, 0, 0));
	dynamicWorld->addAction(m_pVehicle);
	//map->insert(std::pair<btCollisionObject*, GameObj*>(m_chassis, this));

	//map->insert(std::pair<btCollisionObject*, GameObj*>(m_pBody, this));
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

void Robot::createRigidBody()//std::map< btCollisionObject*, GameObj*> * map)
{
	return;
}

btRigidBody* Robot::getRigidBody()
{
	if (vehicle == nullptr) return nullptr;
	return this->vehicle->getRigidBody();
}





void Robot::shoot(std::vector<GameObj*>* projectiles)
{
	std::vector<GameObj*>::iterator it;
	for (it = parts.begin(); it != parts.end(); it++)
	{
			GameObj* g = (*it)->shoot();
			if (g != nullptr)
			{
				g->setBelongTo(this);

				//std::cout << "add bullet: " << (*it)->getIsWeapon()<< std::endl;
				//std::cout << "Weapon ID: " << (*it)->getId() << std::endl;

				projectiles->push_back(g);
			}
	}

}


void Robot::setBoostCD()
{
	if (boostCD == NULL)
	{
		boostCD = clock();
	}
}
int Robot::getBoostCD()
{
	if (boostCD == NULL)
	{
		return 1;
	}
	if ((((double)(clock() - boostCD) / CLOCKS_PER_SEC) > BOOST_DELAY))
	{
		boostCD = NULL;
		return 1;
	}
	return 0;
}

void Robot::applySlow(double slow)
{
	if (isSlowed == NULL)
	{
		isSlowed = clock();
		slowValue = slow;
	}
	
}
double Robot::getSlowValue()
{
	//if (isSlowed == NULL)
	//{
	//	return 0;
	//}
	//if ((((double)(clock() - isSlowed) / CLOCKS_PER_SEC) > SLOW_DELAY))
	//{
	//	isSlowed = NULL;
	//	slowValue = 0;
	//	return 0;
	//}
	//return slowValue;


	if (isSlowed == NULL)
	{
		return 1;
	}
	if ((((double)(clock() - isSlowed) / CLOCKS_PER_SEC) > SLOW_DELAY))
	{
		isSlowed = NULL;
		slowValue = 1;
		return 1;
	}
	return slowValue;
}


void Robot::nextState()
{
	_state = (_state + 1) % 2;
	//_state = (_state + 1) % 3;
}
int Robot::getState()
{
	return _state;
}

//void Robot::setState(int s)
//{
//	_state = s;
//}

void Robot::addPart(GameObj* g)
{
	parts.push_back(g);
}
std::vector<GameObj*> Robot::getParts()
{
	return parts;
}

void Robot::setWheelType(int w)
{
	_wheelType = w;
}
int Robot::getWheelType()
{
	return _wheelType;
}

void Robot::setDiedTo(Robot* r)
{
	if (diedTo == nullptr)
	diedTo = r;
}
Robot* Robot::getDiedTo()
{
	return diedTo;
}


void Robot::setCurrMoney(int m)
{
	currMoney = m;
}
int Robot::getCurrMoney()
{
	return currMoney;
}



void Robot::setParts(std::vector<GameObj*> p){
	parts = p;

}

GameObj* Robot::shoot(){ 
	return nullptr; }

