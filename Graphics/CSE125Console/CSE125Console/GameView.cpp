#include "stdafx.h"
#include "GameView.h"


GameView::GameView()
{	
	pViewCamera = new Camera();
	currentNode = nullptr;
}


GameView::~GameView()
{
}

void GameView::VUpdate() {

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
			//this->pViewCamera->FollowingTarget = node;
		}
		
	}
	//Loop through the list to see anything that's not being processed. if so, create
	for (int i = 0; i < info->player_infos.size(); i++){
		if (!info->player_infos[i]->processed){
			cout << "create object" << endl;
			switch (info->player_infos[i]->type){
				cout << "data is not processed, need to create objects" << endl;
				//CUBE = 0
				
			case BasicCube:{
							   Model3D* object = Model3DFactory::generateObjectWithType(BasicCube);
							   object->identifier = info->player_infos[i]->id;
							   object->localTransform.position = Vector3(info->player_infos[i]->x, info->player_infos[i]->y, info->player_infos[i]->z);
							   object->localTransform.rotation = Vector3(info->player_infos[i]->rx, info->player_infos[i]->ry, info->player_infos[i]->rz);
							   NodeList.push_back(object);
					break;
				}
				//BATTLEFIELD = 1
			case GlowingCube:{
								 Model3D* object = Model3DFactory::generateObjectWithType(GlowingCube);
							   object->identifier = info->player_infos[i]->id;
							   object->localTransform.position = Vector3(info->player_infos[i]->x, info->player_infos[i]->y, info->player_infos[i]->z);
							   object->localTransform.rotation = Vector3(info->player_infos[i]->rx, info->player_infos[i]->ry, info->player_infos[i]->rz);
							   NodeList.push_back(object);
					break;
				}
				//WALL = 2
			case WoodenCube:{
								Model3D* object = Model3DFactory::generateObjectWithType(WoodenCube);							 
								object->identifier = info->player_infos[i]->id;

								object->localTransform.position = Vector3(info->player_infos[i]->x, info->player_infos[i]->y, info->player_infos[i]->z);
								object->localTransform.rotation = Vector3(info->player_infos[i]->rx, info->player_infos[i]->ry, info->player_infos[i]->rz);
								NodeList.push_back(object);
					break;
				}
				//CUBE3x3 = 3
			case Mace:{
						  Model3D* object = Model3DFactory::generateObjectWithType(Mace);
						  object->identifier = info->player_infos[i]->id;

						  object->localTransform.position = Vector3(info->player_infos[i]->x, info->player_infos[i]->y, info->player_infos[i]->z);
						  object->localTransform.rotation = Vector3(info->player_infos[i]->rx, info->player_infos[i]->ry, info->player_infos[i]->rz);
						  NodeList.push_back(object);
					break;
				}
			case Mallet:{
							Model3D* object = Model3DFactory::generateObjectWithType(Mallet);
							
							object->identifier = info->player_infos[i]->id;
							object->localTransform.position = Vector3(info->player_infos[i]->x, info->player_infos[i]->y, info->player_infos[i]->z);
							object->localTransform.rotation = Vector3(info->player_infos[i]->rx, info->player_infos[i]->ry, info->player_infos[i]->rz);
							NodeList.push_back(object);
						   break;
				}
			case Needle:{
							Model3D* object = Model3DFactory::generateObjectWithType(Needle);
							object->identifier = info->player_infos[i]->id;
							object->localTransform.position = Vector3(info->player_infos[i]->x, info->player_infos[i]->y, info->player_infos[i]->z);
							object->localTransform.rotation = Vector3(info->player_infos[i]->rx, info->player_infos[i]->ry, info->player_infos[i]->rz);
							NodeList.push_back(object);
							break;
			}
			case Discount:{
							  Model3D* object = Model3DFactory::generateObjectWithType(Discount);
								object->identifier = info->player_infos[i]->id;
								object->localTransform.position = Vector3(info->player_infos[i]->x, info->player_infos[i]->y, info->player_infos[i]->z);
								object->localTransform.rotation = Vector3(info->player_infos[i]->rx, info->player_infos[i]->ry, info->player_infos[i]->rz);
								NodeList.push_back(object);
							break;
			}
			case Tire:{
						  Model3D* object = Model3DFactory::generateObjectWithType(Tire);
						  object->identifier = info->player_infos[i]->id;
						  object->localTransform.position = Vector3(info->player_infos[i]->x, info->player_infos[i]->y, info->player_infos[i]->z);
						  object->localTransform.rotation = Vector3(info->player_infos[i]->rx, info->player_infos[i]->ry, info->player_infos[i]->rz);
						  NodeList.push_back(object);
							break;
			}
			case WoodenWheel:{
								 Model3D* object = Model3DFactory::generateObjectWithType(WoodenWheel); 
								 object->identifier = info->player_infos[i]->id;
								 object->localTransform.position = Vector3(info->player_infos[i]->x, info->player_infos[i]->y, info->player_infos[i]->z);
								 object->localTransform.rotation = Vector3(info->player_infos[i]->rx, info->player_infos[i]->ry, info->player_infos[i]->rz);
								 NodeList.push_back(object);
							break;
			}
			
			case BATTLEFIELD:{
								 cout << "create battle field" << endl;
								 Plane* p = new Plane(100);
								 p->localTransform.position = Vector3(info->player_infos[i]->x, info->player_infos[i]->y, info->player_infos[i]->z);
								 NodeList.push_back(p);
				break;
			}
			case WALL:{
								break;
			}
			case BULLET_1:{
							  break;
			}

				default:{
							//cout << "Should not go into here in gameview.cpp" << endl;
							break;
				}
			}
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
}

//added this method to check if a node is already in the list,
//used for checking whether or not we need to push up the skybox 
//when we change modes
bool GameView::FindGeoNode(GeoNode* m_node) {
	for (int i = 0; i < NodeList.size(); i++) {
		if (NodeList[i] == m_node)
		{
			return true;
		}
	}
	return false;
}

void GameView::passiveMouseFunc(int x, int y) {

}

viewType GameView::mouseClickFunc(int state, int x, int y) {
	return viewType::CONSOLE;
}

void GameView::keyPressFunc(unsigned char key, int x, int y) {

}
void GameView::specialKeyFunc(int key, int x, int y) {

}

Vector3 GameView::translateNode(Vector3 t, GeoNode * node) {
	node->localTransform.position = node->localTransform.position + t;
	return node->localTransform.position;
}