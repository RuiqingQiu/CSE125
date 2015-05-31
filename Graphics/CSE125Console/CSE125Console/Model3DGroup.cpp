#include "stdafx.h"
#include "Model3DGroup.h"

static int counter = 0;

Model3DGroup::Model3DGroup()
{
	localTransform = Transform();
	shader_type = NORMAL_SHADER;
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
	float halfWidth = 3.0 / 2.0;
	float halfHeight = 1.0 / 2.0;

	//Set the OpenGL Matrix mode to ModelView (used when drawing geometry)
	glMatrixMode(GL_MODELVIEW);
	glPushMatrix();
	glDisable(GL_CULL_FACE);
	//Apply local transformation
	glMultMatrixd(localTransform.GetGLMatrix4().getPointer());
	//glMultMatrixf(mat);

	for (int i = 0; i < (int)objects.size(); i++){
		//Set all children's shader to be the parent's
		objects[i]->shader_type = this->shader_type;
		objects[i]->identifier = this->identifier;
		objects[i]->VOnDraw();
	}

	glPopMatrix();
}

void Model3DGroup::addObject(Model3D* object){
	objects.push_back(object);
}

void Model3DGroup::VOnUpdate(GameInfoPacket* pData){

}

bool Model3DGroup::intersect(Vector3 pos) {
	if (pos.equals(localTransform.position)) return true;

	float halfHeight = height / 2.0;
	float halfWidth = width / 2.0;

	Vector3 temp = localTransform.position;
	if ((pos.x > temp.x - halfWidth && pos.x < temp.x + halfWidth)
		&& (pos.y > temp.y - halfHeight && pos.y < temp.y + halfHeight)
		&& (pos.z > temp.z - halfWidth && pos.z < temp.z + halfWidth)
		)
		return true;

	return false;

}