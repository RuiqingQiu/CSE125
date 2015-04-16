#include "Constraint.h"


Constraint::Constraint()
{
}



void Constraint::addConstraint(GameObj* a, GameObj* b){

	//btGeneric6DofConstraint *joint6DOF;
	//btGeneric6DofSpringConstraint* joint6DOF;
	btTransform localA, localB, toground;

	bool useLinearReferenceFrameA = true;

	localA.setIdentity(); localB.setIdentity();


	localA.setOrigin(btVector3(0, 0, 0));

	localB.setOrigin(btVector3(0, 0, 0));
	//cout << "last is " << last << endl;
	//cout << "current is " << i << endl;
	btTransform frameInA;
	btTransform frameInB;
	a->getRigidBody()->getMotionState()->getWorldTransform(frameInA);
	b->getRigidBody()->getMotionState()->getWorldTransform(frameInB);

	joint6DOF = new btFixedConstraint(*(a->getRigidBody()), *(b->getRigidBody()), frameInA, frameInB);

		
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
	
}

Constraint::~Constraint()
{
}
