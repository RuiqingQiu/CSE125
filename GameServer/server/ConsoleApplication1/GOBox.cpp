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

				double rbDepth = getDepth() / 2 + ((RangedWeapon *)w)->getPDepth()/2 + 0.6f;
				btTransform* rbTrans = &getRigidBody()->getWorldTransform();
				btVector3 relativeDisplacement = btVector3(0, 0, -rbDepth);
				btVector3 boxRot = rbTrans->getBasis()[2];
				boxRot.normalize();
				btVector3 correctedDisplacement = boxRot * -rbDepth; // /2
				double x = rbTrans->getOrigin().getX() + correctedDisplacement.getX();// + 0.5 - w->getPWidth();
				double y = rbTrans->getOrigin().getY() + correctedDisplacement.getY();
				double z = rbTrans->getOrigin().getZ() + correctedDisplacement.getZ();

				GameObj* proj = new Projectile(x, y, z, rbTrans->getRotation().getX(), rbTrans->getRotation().getY(), rbTrans->getRotation().getZ(), rbTrans->getRotation().getW(),
					((RangedWeapon *)w)->getPMass(), ((RangedWeapon *)w)->getPWidth(), ((RangedWeapon *)w)->getPHeight(), ((RangedWeapon *)w)->getPDepth());
				proj->setCollisionType(C_PROJECTILE);
				proj->setDamage(w->getDamage());
				proj->setBlockType(((RangedWeapon *)w)->getPBlockType());
				((RangedWeapon *)w)->setLastShot();
				((Projectile*)proj)->initForce = ((RangedWeapon *)w)->getPInitForce();

				//std::cout << "weapon x y z: " << rbTrans->getOrigin().getX() << " , " << rbTrans->getOrigin().getY() << "  , " << rbTrans->getOrigin().getZ() << std::endl;
				//std::cout << "weapon depth: " << getDepth() << std::endl;
				//std::cout << "weapon orientation x y z w:" << rbTrans->getRotation().getX() << " , " << rbTrans->getRotation().getY() << "  , " << rbTrans->getRotation().getZ() << " , " << rbTrans->getRotation().getW() << std::endl;
				//std::cout << "--------------------------------------------" << std::endl;
				//std::cout << "bullet x y z: " << x << " , " << y << "  , " << z << std::endl;
				//std::cout << "bullet depth: " << ((Projectile*)proj)->getDepth() << std::endl;
				//std::cout << "bullet orientation x y z w: " << proj->getqX() << " , " << proj->getqY() << "  , " << proj->getqZ() << " , " << proj->getqW() << std::endl;

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
