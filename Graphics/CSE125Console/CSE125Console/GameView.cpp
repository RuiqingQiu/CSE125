#include "stdafx.h"
#include "GameView.h"


GameView::GameView()
{
	pViewCamera = new Camera();


}


GameView::~GameView()
{
}


void GameView::VOnRender()
{
	//Clear color and depth buffers
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	//Set the OpenGL matrix mode to ModelView
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	
	pViewCamera->setUpCamera();

	//glPushMatrix();
	//glLoadMatrixd(pViewCamera->GetCameraGLMatrix().getPointer());

	for each (GeoNode* node in NodeList)
	{
		node->VOnDraw();
	}

	
}

void GameView::VOnClientUpdate(GameInfoPacket* info)
{
	for each (GeoNode* node in NodeList)
	{
	    node->VOnClientUpdate(info);
		
		if (node->identifier == pPlayer->playerid ){
			//this node is our lovely player and we do want to update our camera to follow
			/*
			Matrix4 trans = node->localTransform.GetMatrix4();
			Vector4 forward = Vector4(0, 0, -1, 1);
			Vector4 direction = trans*forward;
			float distanceToPlayer = 5;
			pViewCamera->position = new Vector3(node->localTransform.position.x-direction.x*distanceToPlayer, node->localTransform.position.y-direction.y*distanceToPlayer, node->localTransform.position.z-direction.z*distanceToPlayer);
			pViewCamera->rotation = new Vector3(node->localTransform.rotation);
			*/
			/*
			Matrix4 trans = node->localTransform.GetRotMatrix4();
			Vector4 forward = Vector4(0, 0, -1, 1);
			Vector4 direction_temp = trans*forward;
			Vector3 direction = Vector3(direction_temp.get_x(), direction_temp.get_y(), direction_temp.get_z());
			direction.normalize();
			printf("direction : %f %f %f\n", direction.x, direction.y, direction.z);
			float distanceToPlayer = 5;
			pViewCamera->position = new Vector3(node->localTransform.position.x - direction.x*distanceToPlayer, node->localTransform.position.y - direction.y*distanceToPlayer, node->localTransform.position.z - direction.z*distanceToPlayer);
			pViewCamera->rotation = new Vector3(-node->localTransform.rotation.x, -node->localTransform.rotation.y, -node->localTransform.rotation.z);
			*/
		}
		
	}
	//Loop through the list to see anything that's not being processed. if so, create
	for (int i = 0; i < info->player_infos.size(); i++){
		if (!info->player_infos[i]->processed){
			double x = info->player_infos[i]->x;
			double y = info->player_infos[i]->y;
			double z = info->player_infos[i]->z;
			cout << "data is not processed, need to create objects" << endl;
			Cube* cube = new Cube(1);
			cube->localTransform.position = Vector3(x, y, z);
			cube->identifier = info->player_infos[i]->id;
			NodeList.push_back(cube);
		}
	}
}

void GameView::PushGeoNode(GeoNode* node)
{
	NodeList.push_back(node);
}

void GameView::PopGeoNode(GeoNode* m_node)
{
	for (int i = 0; i < NodeList.size(); i++)
	{
		if (NodeList[i] == m_node)
		{
			NodeList.erase(NodeList.begin() + i);
		}
	}
}//added this method to check if a node is already in the list,
//used for checking whether or not we need to push up the skybox 
//when we change modes
bool GameView::FindGeoNode(GeoNode* m_node) {
	for (int i = 0; i < NodeList.size(); i++)
	{
		if (NodeList[i] == m_node)
		{
			return true;
		}
	}
	return false;
}