#include "GOBox.h"

GOBox::GOBox(double x, double y, double z, double qX, double qY, double qZ, double qW, double mass, double width, double height, double depth)
	:GameObj(x, y, z, qX, qY, qZ, qW, BOX, mass)
{
	_width = width;
	_height = height;
	_depth = depth;
}

GOBox::~GOBox()
{

}
GameObj* GOBox::shoot()
{
	if (getIsWeapon())
	{
		Weapon* w = getWeapon();

		if (getIsRangedWeapon()){
			
			if (((RangedWeapon *)w)->readyToShoot())
			{
				double rbDepth = getDepth() / 2 + ((RangedWeapon *)w)->getPDepth()/1.5 + 0.6f;
				btTransform* rbTrans = &getRigidBody()->getWorldTransform();
				btVector3 boxRot = rbTrans->getBasis()[2];
				boxRot.normalize();
				btVector3 correctedDisplacement = boxRot * -rbDepth; // /2
				double x = rbTrans->getOrigin().getX();// + 0.5 - w->getPWidth();
				double y = rbTrans->getOrigin().getY();
				double z = rbTrans->getOrigin().getZ() + correctedDisplacement.getZ();

				GameObj* proj = new Projectile(x, y, z, rbTrans->getRotation().getX(), rbTrans->getRotation().getY(), rbTrans->getRotation().getZ(), rbTrans->getRotation().getW(),
					((RangedWeapon *)w)->getPMass(), ((RangedWeapon *)w)->getPWidth(), ((RangedWeapon *)w)->getPHeight(), ((RangedWeapon *)w)->getPDepth());
				proj->setDamage(w->getDamage());
				proj->setBlockType(((RangedWeapon *)w)->getPBlockType());
				((RangedWeapon *)w)->setLastShot();
				((Projectile*)proj)->initForce = ((RangedWeapon *)w)->getPInitForce();


				return proj;
			}

		}

	}
	return nullptr;
}
void GOBox::setWidth(double width)
{
	_width = width;
}
void GOBox::setHeight(double height)
{
	_height = height;
}
void GOBox::setDepth(double depth)
{
	_depth = depth;
}
double GOBox::getWidth()
{
	return _width;
}
double GOBox::getHeight()
{
	return _height;
}
double GOBox::getDepth()
{
	return _depth;
}

btRigidBody* GOBox::getRigidBody()
{
	return getRB();
}


void GOBox::createRigidBody()//std::map< btCollisionObject*, GameObj*> * map)
{
	btCollisionShape* fallShape = new btBoxShape(btVector3(this->getWidth()/2, this->getHeight()/2, this->getDepth()/2));
	btDefaultMotionState* fallMotionState =
		new btDefaultMotionState(btTransform(btQuaternion(this->getqX(), this->getqY(), this->getqZ(), this->getqW()), btVector3(this->getX(), this->getY(), this->getZ())));
	btScalar mass = this->getMass();
	btVector3 fallInertia(0, 0, 0);
	fallShape->calculateLocalInertia(mass, fallInertia);
	btRigidBody::btRigidBodyConstructionInfo fallRigidBodyCI(mass, fallMotionState, fallShape, fallInertia);
	fallRigidBodyCI.m_friction = 0.0f;
	fallRigidBodyCI.m_restitution = 0.0f;
	fallRigidBodyCI.m_linearDamping = 0.2f;
	fallRigidBodyCI.m_angularDamping = 0.1f;
	btRigidBody* rb = new btRigidBody(fallRigidBodyCI);
	//map->insert(std::pair<btCollisionObject*, GameObj*> (rb, this));
	rb->setUserPointer(this);
	this->setRigidBody(rb);
}
void GOBox::addDoT(double d, int c){
	DoT += d / DMG_SCALAR;
	DoTTick = (double)DoT / (double)10;
	DoTFrom = c;
}
double GOBox::applyDamage(double h){
	_health -= h / DMG_SCALAR;
	if (_health > _maxHealth){
		_health = _maxHealth;
	}
	return _health;
}
