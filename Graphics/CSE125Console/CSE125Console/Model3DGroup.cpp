#include "stdafx.h"
#include "Model3DGroup.h"

static int counter = 0;

Model3DGroup::Model3DGroup()
{

}


Model3DGroup::~Model3DGroup()
{
}
void Model3DGroup::VOnClientUpdate(GameInfoPacket* pData){
	PlayerInfo* p = pData->get_player_info(this->identifier);
	if (p){

		localTransform.position.x = p->x;
		localTransform.position.y = p->y;
		localTransform.position.z = p->z;

		localTransform.rotation.x = p->rx;
		localTransform.rotation.y = p->ry;
		localTransform.rotation.z = p->rz;
		p->processed = true;
		this->isUpdated = true;
	}
	else{
		this->isUpdated = false;

	}
}

void Model3DGroup::VOnDraw(){
	//counter = (counter + 1) % 360;
	//localTransform.rotation.y = counter;
	glMatrixMode(GL_MODELVIEW);
	glPushMatrix();
	glMultMatrixd(localTransform.GetGLMatrix4().getPointer());
	for (int i = 0; i < objects.size(); i++){
		objects[i]->VOnDraw();
	}
	glPopMatrix();
}

void Model3DGroup::addObject(Model3D* object){
	objects.push_back(object);
}

void Model3DGroup::VOnUpdate(GameInfoPacket* pData){

}