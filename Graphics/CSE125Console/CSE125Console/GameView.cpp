#include "stdafx.h"
#include "GameView.h"
#include "SkyBox.h"
#include <algorithm>
#include "Window.h"

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

void GameView::setConstraints() {
	for (int i = 0; i < NodeList.size(); i++) {
		NodeList[i]->clearConstraints();
	}
}


bool pairCompare(const std::pair<float, GeoNode*>& firstElem, const std::pair<float, GeoNode*>& secondElem) {
	return firstElem.first < secondElem.first;
}

void GameView::blur_first_pass(){
	glBindFramebuffer(GL_FRAMEBUFFER, Window::shader_system->fb);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	glBindTexture(GL_TEXTURE_2D, 0);
	glEnable(GL_TEXTURE_2D);
	glViewport(0, 0, Window::width, Window::height);                                          //Set new viewport size
	glMatrixMode(GL_PROJECTION);                                     //Set the OpenGL matrix mode to Projection
	glLoadIdentity();                                                //Clear the projection matrix by loading the identity
	gluPerspective(90.0, double(Window::width) / (double)Window::height, 0.1, 1000.0); //Set perspective projection viewing frustum

	glEnable(GL_DEPTH_TEST);
	glDisable(GL_CULL_FACE);

	Window::shader_system->BindShader(BLUR_SHADER);
	glUniform1i(glGetUniformLocationARB(Window::shader_system->shader_ids[BLUR_SHADER], "pass"), 1);

	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	pViewCamera->setUpCamera();
	glPushMatrix();
	glTranslated(0, 0, -15);
	//glutSolidTeapot(1);
	glPopMatrix();
	//List of items that need edge highlight

	for each (GeoNode* node in NodeList){
		if (node->blur){
			node->VOnDraw();
		}
	}
	Window::shader_system->UnbindShader();
}
void GameView::blur_second_pass(){
	//Code below this is second pass
	glBindFramebuffer(GL_FRAMEBUFFER, 0);
	//Clear color and depth buffers
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	//Set the OpenGL matrix mode to ModelView

	glViewport(0, 0, Window::width, Window::height);                                          //Set new viewport size
	glMatrixMode(GL_PROJECTION);                                     //Set the OpenGL matrix mode to Projection
	glLoadIdentity();                                                //Clear the projection matrix by loading the identity
	gluPerspective(90.0, double(Window::width) / (double)Window::height, 0.1, 1000.0); //Set perspective projection viewing frustum

	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	pViewCamera->setUpCamera();

	glBindTexture(GL_TEXTURE_2D, Window::shader_system->color);
	Window::shader_system->BindShader(BLUR_SHADER);
	glUniform1f(glGetUniformLocationARB(Window::shader_system->shader_ids[BLUR_SHADER], "width"), Window::width);
	glUniform1f(glGetUniformLocationARB(Window::shader_system->shader_ids[BLUR_SHADER], "height"), Window::height);
	glUniform1i(glGetUniformLocationARB(Window::shader_system->shader_ids[BLUR_SHADER], "pass"), 2);
	glUniform1i(glGetUniformLocationARB(Window::shader_system->shader_ids[BLUR_SHADER], "RenderTex"), 0);

	glPushMatrix();
	glTranslated(0, 0, -15);
	//glutSolidTeapot(1);
	glPopMatrix();

	//List of items that need edge highlight
	for each (GeoNode* node in NodeList){
		if (node->blur){
			node->VOnDraw();
		}
	}
	Window::shader_system->UnbindShader();
}



void GameView::highlight_first_pass_build(){
	
	glBindFramebuffer(GL_FRAMEBUFFER, Window::shader_system->fb);
	
	glBindTexture(GL_TEXTURE_2D, 0);
	glEnable(GL_TEXTURE_2D);
	glViewport(0, 0, Window::width, Window::height);                                          //Set new viewport size
	glMatrixMode(GL_PROJECTION);                                     //Set the OpenGL matrix mode to Projection
	glLoadIdentity();                                                //Clear the projection matrix by loading the identity
	gluPerspective(90.0, double(Window::width) / (double)Window::height, 0.1, 1000.0); //Set perspective projection viewing frustum

	glEnable(GL_DEPTH_TEST);
	glDisable(GL_CULL_FACE);

	Window::shader_system->BindShader(EDGE_SHADER);
	glUniform1i(glGetUniformLocationARB(Window::shader_system->shader_ids[EDGE_SHADER], "pass"), 1);

	glMatrixMode(GL_MODELVIEW);

	if (currentNode != nullptr) currentNode->VOnDraw();
	//List of items that need edge highlight
	if (currentNode)
		currentNode->VOnDraw();
	Window::shader_system->UnbindShader();
}


void GameView::highlight_second_pass_build(){

	//Code below this is second pass
	glBindFramebuffer(GL_FRAMEBUFFER, 0);
	//Clear color and depth buffers
	//glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	//Set the OpenGL matrix mode to ModelView

	glViewport(0, 0, Window::width, Window::height);                                          //Set new viewport size
	glMatrixMode(GL_PROJECTION);                                     //Set the OpenGL matrix mode to Projection
	glLoadIdentity();                                                //Clear the projection matrix by loading the identity
	gluPerspective(90.0, double(Window::width) / (double)Window::height, 0.1, 1000.0); //Set perspective projection viewing frustum

	glMatrixMode(GL_MODELVIEW);

	glBindTexture(GL_TEXTURE_2D, Window::shader_system->color);

	Window::shader_system->BindShader(EDGE_SHADER);
	glUniform1f(glGetUniformLocationARB(Window::shader_system->shader_ids[EDGE_SHADER], "width"), Window::width);
	glUniform1f(glGetUniformLocationARB(Window::shader_system->shader_ids[EDGE_SHADER], "height"), Window::height);
	glUniform1i(glGetUniformLocationARB(Window::shader_system->shader_ids[EDGE_SHADER], "pass"), 2);
	glUniform1i(glGetUniformLocationARB(Window::shader_system->shader_ids[EDGE_SHADER], "RenderTex"), 0);

	if (currentNode != nullptr) currentNode->VOnDraw();
	//List of items that need edge highlight
	if (currentNode)
		currentNode->VOnDraw();
	Window::shader_system->UnbindShader();

}


void GameView::highlight_first_pass(){
	glBindFramebuffer(GL_FRAMEBUFFER, Window::shader_system->fb);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	glBindTexture(GL_TEXTURE_2D, 0);
	glEnable(GL_TEXTURE_2D);
	glViewport(0, 0, Window::width, Window::height);                                          //Set new viewport size
	glMatrixMode(GL_PROJECTION);                                     //Set the OpenGL matrix mode to Projection
	glLoadIdentity();                                                //Clear the projection matrix by loading the identity
	gluPerspective(90.0, double(Window::width) / (double)Window::height, 0.1, 1000.0); //Set perspective projection viewing frustum

	glEnable(GL_DEPTH_TEST);
	glDisable(GL_CULL_FACE);

	Window::shader_system->BindShader(EDGE_SHADER);
	glUniform1i(glGetUniformLocationARB(Window::shader_system->shader_ids[EDGE_SHADER], "pass"), 1);

	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	pViewCamera->setUpCamera();
	glPushMatrix();
	glTranslated(0, 0, -15);
	//glutSolidTeapot(1);
	glPopMatrix();

	if (currentNode != nullptr) currentNode->VOnDraw();
	//List of items that need edge highlight
	for each (GeoNode* node in NodeList){
		if (node->edge_highlight){
			node->VOnDraw();
		}
	}
	if (currentNode)
		currentNode->VOnDraw();
	Window::shader_system->UnbindShader();
}


void GameView::highlight_second_pass(){

	//Code below this is second pass
	glBindFramebuffer(GL_FRAMEBUFFER, 0);
	//Clear color and depth buffers
	//glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	//Set the OpenGL matrix mode to ModelView

	glViewport(0, 0, Window::width, Window::height);                                          //Set new viewport size
	glMatrixMode(GL_PROJECTION);                                     //Set the OpenGL matrix mode to Projection
	glLoadIdentity();                                                //Clear the projection matrix by loading the identity
	gluPerspective(90.0, double(Window::width) / (double)Window::height, 0.1, 1000.0); //Set perspective projection viewing frustum

	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	Window::light_sytem->setCameraOffset(pViewCamera->position->x, pViewCamera->position->y, pViewCamera->position->z);
	pViewCamera->setUpCamera();
	glBindTexture(GL_TEXTURE_2D, Window::shader_system->color);
	Window::shader_system->BindShader(EDGE_SHADER);
	glUniform1f(glGetUniformLocationARB(Window::shader_system->shader_ids[EDGE_SHADER], "width"), Window::width);
	glUniform1f(glGetUniformLocationARB(Window::shader_system->shader_ids[EDGE_SHADER], "height"), Window::height);
	glUniform1i(glGetUniformLocationARB(Window::shader_system->shader_ids[EDGE_SHADER], "pass"), 2);
	glUniform1i(glGetUniformLocationARB(Window::shader_system->shader_ids[EDGE_SHADER], "RenderTex"), 0);
	
	glPushMatrix();
	glTranslated(0, 0, -15);
	//glutSolidTeapot(1);
	// activate and specify pointer to vertex array
	glPopMatrix();

	if (currentNode != nullptr) currentNode->VOnDraw();
	//List of items that need edge highlight
	for each (GeoNode* node in NodeList){
		if (node->edge_highlight){
			node->VOnDraw();
		}
	}
	if (currentNode)
		currentNode->VOnDraw();
	Window::shader_system->UnbindShader();

	//glPushMatrix();
	//glLoadMatrixd(pViewCamera->GetCameraGLMatrix().getPointer());
	//sort Z before draw
	float ptr[16];
	glGetFloatv(GL_MODELVIEW_MATRIX, ptr);
	Matrix4 modelview;
	modelview.m[0][0] = ptr[0];
	modelview.m[0][1] = ptr[1];
	modelview.m[0][2] = ptr[2];
	modelview.m[0][3] = ptr[3];

	modelview.m[1][0] = ptr[4];
	modelview.m[1][1] = ptr[5];
	modelview.m[1][2] = ptr[6];
	modelview.m[1][3] = ptr[7];

	modelview.m[2][0] = ptr[8];
	modelview.m[2][1] = ptr[9];
	modelview.m[2][2] = ptr[10];
	modelview.m[2][3] = ptr[11];

	modelview.m[3][0] = ptr[12];
	modelview.m[3][1] = ptr[13];
	modelview.m[3][2] = ptr[14];
	modelview.m[3][3] = ptr[15];

	modelview.transpose();

	vector<pair<float, GeoNode*>> nodedepthvec;
	for each (GeoNode* node in NodeList)
	{
		if (typeid(*node) == typeid(SkyBox) || node->static_object == true)
		{
			pair<float, GeoNode*> p = make_pair(999, node);
			nodedepthvec.push_back(p);
		}
		if (pViewCamera->sphereInFrustum(node->localTransform.position, 1) != Camera::OUTSIDE)
		{
			Vector4 localpos = Vector4(node->localTransform.position.x, node->localTransform.position.y, node->localTransform.position.z, 1);
			Vector4 position = modelview * (localpos);
			float z = -position.z;

			pair<float, GeoNode*> p = make_pair(z, node);
			nodedepthvec.push_back(p);
		}
	}

	sort(nodedepthvec.begin(), nodedepthvec.end(), pairCompare);


	for each (pair<float, GeoNode*> p in nodedepthvec)
	{
		//Don't draw if it uses 2 pass
		if (p.second->edge_highlight || p.second->blur){

		}
		else{
			p.second->VOnDraw();
		}
	}

	vector<pair<float, GeoNode*>> depthvec;
	for each (GeoNode* node in GrassList)
	{
		if (pViewCamera->sphereInFrustum(node->localTransform.position, 1) != Camera::OUTSIDE)
		{
			Vector4 localpos = Vector4(node->localTransform.position.x, node->localTransform.position.y, node->localTransform.position.z, 1);
			Vector4 position = modelview * (localpos);
			float z = position.z;

			pair<float, GeoNode*> p = make_pair(z, node);
			depthvec.push_back(p);
		}
	}

	sort(depthvec.begin(), depthvec.end(), pairCompare);

	//Draw environment
	for each (GeoNode* node in EnvironmentList){
		node->VOnDraw();
	}
	for (int i = 0; i < EnvironmentList.size(); i++){
		GeoNode* node = EnvironmentList[i];
		//printf("size of particle is %i\n", EnvironmentList.size());

		if (node->isDead)
		{
			EnvironmentList.erase(EnvironmentList.begin() + i);
		}
	}
	//grass
	for each (pair<float, GeoNode*> p in depthvec)
	{
		p.second->VOnDraw();
	}
	
	//draw last frmae
	Window::shader_system->BindShader(BLUR_SHADER);
	glUniform1f(glGetUniformLocationARB(Window::shader_system->shader_ids[BLUR_SHADER], "width"), Window::width);
	glUniform1f(glGetUniformLocationARB(Window::shader_system->shader_ids[BLUR_SHADER], "height"), Window::height);
	glUniform1i(glGetUniformLocationARB(Window::shader_system->shader_ids[BLUR_SHADER], "pass"), 2);
	glUniform1i(glGetUniformLocationARB(Window::shader_system->shader_ids[BLUR_SHADER], "RenderTex"), lastFrame);
	glBindTexture(GL_TEXTURE_2D, lastFrame);
	glPushMatrix();
	glBegin(GL_QUADS);
	glTexCoord2i(0, 0); glVertex2i(0, 0);
	glTexCoord2i(1, 0); glVertex2i(Window::width, 0);
	glTexCoord2i(1, 1); glVertex2i(Window::width, Window::height);
	glTexCoord2i(0, 1); glVertex2i(0, Window::height);
	glEnd();
	glPopMatrix();
	Window::shader_system->UnbindShader();

}



void GameView::highlight_third_pass_build(){
	glEnable(GL_TEXTURE_2D);
	glGenTextures(1, &lastFrame);
	glBindTexture(GL_TEXTURE_2D, lastFrame);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
	//NULL means reserve texture memory, but texels are undefined
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA8, 256, 256, 0, GL_BGRA, GL_UNSIGNED_BYTE, NULL);
	//-------------------------
	glGenFramebuffersEXT(1, &lastFb);
	glBindFramebufferEXT(GL_FRAMEBUFFER_EXT, lastFb);
	//Attach 2D texture to this FBO
	glFramebufferTexture2DEXT(GL_FRAMEBUFFER_EXT, GL_COLOR_ATTACHMENT0_EXT, GL_TEXTURE_2D, lastFrame, 0);
	//-------------------------
	glGenRenderbuffersEXT(1, &lastDepth);
	glBindRenderbufferEXT(GL_RENDERBUFFER_EXT, lastDepth);
	glRenderbufferStorageEXT(GL_RENDERBUFFER_EXT, GL_DEPTH_COMPONENT24, 256, 256);
	//-------------------------
	//Attach depth buffer to FBO
	glFramebufferRenderbufferEXT(GL_FRAMEBUFFER_EXT, GL_DEPTH_ATTACHMENT_EXT, GL_RENDERBUFFER_EXT, lastDepth);
	//-------------------------
	//Does the GPU support current FBO configuration?
	GLenum status;
	status = glCheckFramebufferStatusEXT(GL_FRAMEBUFFER_EXT);

	//-------------------------
	//and now you can render to GL_TEXTURE_2D
	glBindFramebufferEXT(GL_FRAMEBUFFER_EXT, lastFb);
	glClearColor(0.0, 0.0, 0.0, 0.0);
	glClearDepth(1.0f);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	//-------------------------	
	glViewport(0, 0, Window::width, Window::height);                                          //Set new viewport size
	
	glMatrixMode(GL_PROJECTION);                                     //Set the OpenGL matrix mode to Projection
	glLoadIdentity();                                                //Clear the projection matrix by loading the identity
	gluPerspective(90.0, double(Window::width) / (double)Window::height, 0.1, 1000.0); //Set perspective projection viewing frustum

	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	Window::light_sytem->setCameraOffset(pViewCamera->position->x, pViewCamera->position->y, pViewCamera->position->z);
	pViewCamera->setUpCamera();
	glBindTexture(GL_TEXTURE_2D, Window::shader_system->color);
	Window::shader_system->BindShader(EDGE_SHADER);
	glUniform1f(glGetUniformLocationARB(Window::shader_system->shader_ids[EDGE_SHADER], "width"), Window::width);
	glUniform1f(glGetUniformLocationARB(Window::shader_system->shader_ids[EDGE_SHADER], "height"), Window::height);
	glUniform1i(glGetUniformLocationARB(Window::shader_system->shader_ids[EDGE_SHADER], "pass"), 2);
	glUniform1i(glGetUniformLocationARB(Window::shader_system->shader_ids[EDGE_SHADER], "RenderTex"), 0);

	glPushMatrix();
	glTranslated(0, 0, -15);
	//glutSolidTeapot(1);
	// activate and specify pointer to vertex array
	glPopMatrix();

	if (currentNode != nullptr) currentNode->VOnDraw();
	//List of items that need edge highlight
	for each (GeoNode* node in NodeList){
		if (node->edge_highlight){
			node->VOnDraw();
		}
	}
	if (currentNode)
		currentNode->VOnDraw();
	Window::shader_system->UnbindShader();

	//glPushMatrix();
	//glLoadMatrixd(pViewCamera->GetCameraGLMatrix().getPointer());
	//sort Z before draw
	float ptr[16];
	glGetFloatv(GL_MODELVIEW_MATRIX, ptr);
	Matrix4 modelview;
	modelview.m[0][0] = ptr[0];
	modelview.m[0][1] = ptr[1];
	modelview.m[0][2] = ptr[2];
	modelview.m[0][3] = ptr[3];

	modelview.m[1][0] = ptr[4];
	modelview.m[1][1] = ptr[5];
	modelview.m[1][2] = ptr[6];
	modelview.m[1][3] = ptr[7];

	modelview.m[2][0] = ptr[8];
	modelview.m[2][1] = ptr[9];
	modelview.m[2][2] = ptr[10];
	modelview.m[2][3] = ptr[11];

	modelview.m[3][0] = ptr[12];
	modelview.m[3][1] = ptr[13];
	modelview.m[3][2] = ptr[14];
	modelview.m[3][3] = ptr[15];

	modelview.transpose();

	vector<pair<float, GeoNode*>> nodedepthvec;
	for each (GeoNode* node in NodeList)
	{
		if (typeid(*node) == typeid(SkyBox) || node->static_object == true)
		{
			pair<float, GeoNode*> p = make_pair(999, node);
			nodedepthvec.push_back(p);
		}
		if (pViewCamera->sphereInFrustum(node->localTransform.position, 1) != Camera::OUTSIDE)
		{
			Vector4 localpos = Vector4(node->localTransform.position.x, node->localTransform.position.y, node->localTransform.position.z, 1);
			Vector4 position = modelview * (localpos);
			float z = -position.z;

			pair<float, GeoNode*> p = make_pair(z, node);
			nodedepthvec.push_back(p);
		}
	}

	sort(nodedepthvec.begin(), nodedepthvec.end(), pairCompare);


	for each (pair<float, GeoNode*> p in nodedepthvec)
	{
		//Don't draw if it uses 2 pass
		if (p.second->edge_highlight || p.second->blur){

		}
		else{
			p.second->VOnDraw();
		}
	}
	vector<pair<float, GeoNode*>> depthvec;
	for each (GeoNode* node in GrassList)
	{
		if (pViewCamera->sphereInFrustum(node->localTransform.position, 1) != Camera::OUTSIDE)
		{
			Vector4 localpos = Vector4(node->localTransform.position.x, node->localTransform.position.y, node->localTransform.position.z, 1);
			Vector4 position = modelview * (localpos);
			float z = position.z;

			pair<float, GeoNode*> p = make_pair(z, node);
			depthvec.push_back(p);
		}
	}

	sort(depthvec.begin(), depthvec.end(), pairCompare);

	//Draw environment
	for each (GeoNode* node in EnvironmentList){
		node->VOnDraw();
	}
	for (int i = 0; i < EnvironmentList.size(); i++){
		GeoNode* node = EnvironmentList[i];
		//printf("size of particle is %i\n", EnvironmentList.size());

		if (node->isDead)
		{
			EnvironmentList.erase(EnvironmentList.begin() + i);
		}
	}
	//grass
	for each (pair<float, GeoNode*> p in depthvec)
	{
		p.second->VOnDraw();
	}

	glBindFramebuffer(GL_FRAMEBUFFER, 0);
}

void GameView::VOnRender()
{
	blur_first_pass();
	blur_second_pass();
	
	highlight_first_pass();
	highlight_second_pass();	
	//highlight_third_pass_build();

}

void GameView::VOnClientUpdate(GameInfoPacket* info)
{
	//cout << "node list size is " << NodeList.size() << endl;
	for each (GeoNode* node in NodeList)
	{
		node->VOnClientUpdate(info);
		//printf("id: %i player: %i\n", node->identifier, pPlayer->playerid);
		if (node->identifier == pPlayer->playerid ){
			 this->pViewCamera->FollowingTarget = node;
		}
	}
	//Loop through the list to see anything that's not being processed. if so, create
	for (int i = 0; i < info->player_infos.size(); i++)
	{
		if (!info->player_infos[i]->processed){
			//cout << "create object" << endl;
			switch (info->player_infos[i]->type){
				cout << "data is not processed, need to create objects" << endl;
				//CUBE = 0

			case BasicCube:{
							   Model3D* object = Model3DFactory::generateObjectWithType(BasicCube);
							   object->isUpdated = true;
							   object->identifier = info->player_infos[i]->id;
							   object->localTransform.position = Vector3(info->player_infos[i]->x, info->player_infos[i]->y, info->player_infos[i]->z);
							   object->localTransform.rotation = Vector3(info->player_infos[i]->rx, info->player_infos[i]->ry, info->player_infos[i]->rz);
							   NodeList.push_back(object);
							   info->player_infos[i]->processed = true;
							   break;
			}
				//BATTLEFIELD = 1
			case GlowingCube:{
								 Model3D* object = Model3DFactory::generateObjectWithType(GlowingCube);
								 object->identifier = info->player_infos[i]->id;							   object->isUpdated = true;

								 object->localTransform.position = Vector3(info->player_infos[i]->x, info->player_infos[i]->y, info->player_infos[i]->z);
								 object->localTransform.rotation = Vector3(info->player_infos[i]->rx, info->player_infos[i]->ry, info->player_infos[i]->rz);
								 NodeList.push_back(object);
								 info->player_infos[i]->processed = true;

								 break;
			}
				//WALL = 2
			case WoodenCube:{
								Model3D* object = Model3DFactory::generateObjectWithType(WoodenCube);
								object->identifier = info->player_infos[i]->id;
								object->isUpdated = true;

								object->localTransform.position = Vector3(info->player_infos[i]->x, info->player_infos[i]->y, info->player_infos[i]->z);
								object->localTransform.rotation = Vector3(info->player_infos[i]->rx, info->player_infos[i]->ry, info->player_infos[i]->rz);
								NodeList.push_back(object);
								info->player_infos[i]->processed = true;

								break;
			}
			case BGun:{
						  Model3D* object = Model3DFactory::generateObjectWithType(BGun);							   
						  object->isUpdated = true;
							object->identifier = info->player_infos[i]->id;
							object->localTransform.position = Vector3(info->player_infos[i]->x, info->player_infos[i]->y, info->player_infos[i]->z);
							object->localTransform.rotation = Vector3(info->player_infos[i]->rx, info->player_infos[i]->ry, info->player_infos[i]->rz);
							NodeList.push_back(object);
							info->player_infos[i]->processed = true;
							break;
			}
				//CUBE3x3 = 3
			case Mace:{
						  Model3D* object = Model3DFactory::generateObjectWithType(Mace);
						  object->identifier = info->player_infos[i]->id;
						  object->isUpdated = true;

						  object->localTransform.position = Vector3(info->player_infos[i]->x, info->player_infos[i]->y, info->player_infos[i]->z);
						  object->localTransform.rotation = Vector3(info->player_infos[i]->rx, info->player_infos[i]->ry, info->player_infos[i]->rz);
						  NodeList.push_back(object);
						  info->player_infos[i]->processed = true;

						  break;
			}
			case Mallet:{
							Model3D* object = Model3DFactory::generateObjectWithType(Mallet);
							object->isUpdated = true;

							object->identifier = info->player_infos[i]->id;
							object->localTransform.position = Vector3(info->player_infos[i]->x, info->player_infos[i]->y, info->player_infos[i]->z);
							object->localTransform.rotation = Vector3(info->player_infos[i]->rx, info->player_infos[i]->ry, info->player_infos[i]->rz);
							NodeList.push_back(object);
							info->player_infos[i]->processed = true;

							break;
			}
			case Needle:{
							Model3D* object = Model3DFactory::generateObjectWithType(Needle);							   object->isUpdated = true;

							object->identifier = info->player_infos[i]->id;
							object->localTransform.position = Vector3(info->player_infos[i]->x, info->player_infos[i]->y, info->player_infos[i]->z);
							object->localTransform.rotation = Vector3(info->player_infos[i]->rx, info->player_infos[i]->ry, info->player_infos[i]->rz);
							NodeList.push_back(object);
							info->player_infos[i]->processed = true;

							break;
			}
			case Discount:{
							  
							  Model3D* object = Model3DFactory::generateObjectWithType(Discount);							   object->isUpdated = true;

							  object->identifier = info->player_infos[i]->id;
							  object->localTransform.position = Vector3(info->player_infos[i]->x, info->player_infos[i]->y, info->player_infos[i]->z);
							  object->localTransform.rotation = Vector3(info->player_infos[i]->rx, info->player_infos[i]->ry, info->player_infos[i]->rz);
							  NodeList.push_back(object);
							  info->player_infos[i]->processed = true;
							  
							  break;
			}
			case Railgun:{
							 Model3D* object = Model3DFactory::generateObjectWithType(Railgun);							   object->isUpdated = true;
							 object->identifier = info->player_infos[i]->id;
							 object->localTransform.position = Vector3(info->player_infos[i]->x, info->player_infos[i]->y, info->player_infos[i]->z);
							 object->localTransform.rotation = Vector3(info->player_infos[i]->rx, info->player_infos[i]->ry, info->player_infos[i]->rz);
							 NodeList.push_back(object);
							 info->player_infos[i]->processed = true;
							 break;
			}
			case Tire:{
						  
						  Model3D* object = Model3DFactory::generateObjectWithType(Tire);							   object->isUpdated = true;

						  object->identifier = info->player_infos[i]->id;
						  object->localTransform.position = Vector3(info->player_infos[i]->x, info->player_infos[i]->y, info->player_infos[i]->z);
						  object->localTransform.rotation = Vector3(info->player_infos[i]->rx, info->player_infos[i]->ry, info->player_infos[i]->rz);
						  NodeList.push_back(object);
						  info->player_infos[i]->processed = true;
						  
						  break;
			}
			case WoodenWheel:{
								 
								 Model3D* object = Model3DFactory::generateObjectWithType(WoodenWheel);
								 object->isUpdated = true;
								 object->identifier = info->player_infos[i]->id;
								 object->localTransform.position = Vector3(info->player_infos[i]->x, info->player_infos[i]->y, info->player_infos[i]->z);
								 object->localTransform.rotation = Vector3(info->player_infos[i]->rx, info->player_infos[i]->ry, info->player_infos[i]->rz);
								 NodeList.push_back(object);
								 info->player_infos[i]->processed = true;
								 
								 break;
			}
			case CrystalCube:{
								 Model3D* object = Model3DFactory::generateObjectWithType(CrystalCube);
								 object->isUpdated = true;
								 object->shader_type = NORMAL_SHADER;
								 object->identifier = info->player_infos[i]->id;
								 object->localTransform.position = Vector3(info->player_infos[i]->x, info->player_infos[i]->y, info->player_infos[i]->z);
								 object->localTransform.rotation = Vector3(info->player_infos[i]->rx, info->player_infos[i]->ry, info->player_infos[i]->rz);
								 NodeList.push_back(object);
								 info->player_infos[i]->processed = true;
								 break;
			}
			case BATTLEFIELD:{
								 /*
								 //cout << "enter here" << endl;
								 Model3D* object = Model3DFactory::generateObjectWithType(BATTLEFIELD);
								 object->identifier = info->player_infos[i]->id;
								 object->localTransform.position = Vector3(info->player_infos[i]->x, info->player_infos[i]->y-2, info->player_infos[i]->z);
								 object->localTransform.rotation = Vector3(info->player_infos[i]->rx, info->player_infos[i]->ry, info->player_infos[i]->rz);
								 object->localTransform.scale = Vector3(1, 1, 1);
								 NodeList.push_back(object);
								 info->player_infos[i]->processed = true;
								 */
								 break;
			}
			//Fix this
			case THREEBYTHREE_BASIC:{
										
				Model3D* object = Model3DFactory::generateObjectWithType(THREEBYTHREE_BASIC);
				object->isUpdated = true;
				object->identifier = info->player_infos[i]->id;
				object->localTransform.position = Vector3(info->player_infos[i]->x, info->player_infos[i]->y, info->player_infos[i]->z);
				object->localTransform.rotation = Vector3(info->player_infos[i]->rx, info->player_infos[i]->ry, info->player_infos[i]->rz);
				object->localTransform.scale = Vector3(1, 1, 1);
				NodeList.push_back(object);
				info->player_infos[i]->processed = true;
				break;

			}

			case THREEBYTHREE_GLOWING:{
				Model3D* object = Model3DFactory::generateObjectWithType(THREEBYTHREE_GLOWING);
				object->isUpdated = true;
				object->identifier = info->player_infos[i]->id;
				object->localTransform.position = Vector3(info->player_infos[i]->x, info->player_infos[i]->y, info->player_infos[i]->z);
				object->localTransform.rotation = Vector3(info->player_infos[i]->rx, info->player_infos[i]->ry, info->player_infos[i]->rz);
				object->localTransform.scale = Vector3(1, 1, 1);
				NodeList.push_back(object);
				info->player_infos[i]->processed = true;
				break;
			}
			case THREEBYTHREE_WOODEN:{
				Model3D* object = Model3DFactory::generateObjectWithType(THREEBYTHREE_WOODEN);
				object->isUpdated = true;
				object->identifier = info->player_infos[i]->id;
				object->localTransform.position = Vector3(info->player_infos[i]->x, info->player_infos[i]->y, info->player_infos[i]->z);
				object->localTransform.rotation = Vector3(info->player_infos[i]->rx, info->player_infos[i]->ry, info->player_infos[i]->rz);
				object->localTransform.scale = Vector3(1, 1, 1);
				NodeList.push_back(object);
				info->player_infos[i]->processed = true;
				break;

			}

			case BLACKCUBE:{
							   Model3D* object = Model3DFactory::generateObjectWithType(BLACKCUBE);
							   object->isUpdated = true;
							   object->identifier = info->player_infos[i]->id;
							   object->localTransform.position = Vector3(info->player_infos[i]->x, info->player_infos[i]->y, info->player_infos[i]->z);
							   object->localTransform.rotation = Vector3(info->player_infos[i]->rx, info->player_infos[i]->ry, info->player_infos[i]->rz);
							   object->localTransform.scale = Vector3(1, 1, 1);
							   NodeList.push_back(object);
							   info->player_infos[i]->processed = true;
							   break;
			}
			case CUBEA:{
						   Model3D* object = Model3DFactory::generateObjectWithType(CUBEA);
						   object->isUpdated = true;
						   object->identifier = info->player_infos[i]->id;
						   object->localTransform.position = Vector3(info->player_infos[i]->x, info->player_infos[i]->y, info->player_infos[i]->z);
						   object->localTransform.rotation = Vector3(info->player_infos[i]->rx, info->player_infos[i]->ry, info->player_infos[i]->rz);
						   object->localTransform.scale = Vector3(1, 1, 1);
						   NodeList.push_back(object);
						   info->player_infos[i]->processed = true;
						   break;
			}
			case CUBEB:{
						   Model3D* object = Model3DFactory::generateObjectWithType(CUBEB);
						   object->isUpdated = true;
						   object->identifier = info->player_infos[i]->id;
						   object->localTransform.position = Vector3(info->player_infos[i]->x, info->player_infos[i]->y, info->player_infos[i]->z);
						   object->localTransform.rotation = Vector3(info->player_infos[i]->rx, info->player_infos[i]->ry, info->player_infos[i]->rz);
						   object->localTransform.scale = Vector3(1, 1, 1);
						   NodeList.push_back(object);
						   info->player_infos[i]->processed = true;
						   break;
			}


			case WALL:{
								break;
			}
			case BULLET_1:{
							  break;
			}
			case BULLET:{
							Model3D* object = Model3DFactory::generateObjectWithType(BULLET);
							object->isUpdated = true;
							object->identifier = info->player_infos[i]->id;
							object->localTransform.position = Vector3(info->player_infos[i]->x, info->player_infos[i]->y, info->player_infos[i]->z);
							object->localTransform.rotation = Vector3(info->player_infos[i]->rx, info->player_infos[i]->ry, info->player_infos[i]->rz);
							object->localTransform.scale = Vector3(1, 1, 1);
							NodeList.push_back(object);
							info->player_infos[i]->processed = true;
							break;
			}

			default:{
							//cout << "Should not go into here in gameview.cpp" << endl;
							break;
				}
			}
		}
	}
	//Loop through the list and delete anything 
	//Make a tmp list to store everything we want to render at the next pass
	/*
	for (int i = 0; i < NodeListBuffer.size(); i++){
		delete NodeListBuffer[i];
	}*/
	NodeListBuffer.clear();
	for (int i = 0; i < NodeList.size(); i++)
	{
		//Skybox is an exception
		if (!NodeList[i]->isUpdated && typeid(*NodeList[i]) != typeid(SkyBox))
		{
			//int index = NodeList.
		}
		else{
			NodeListBuffer.push_back(NodeList[i]);
		}
		NodeList[i]->isUpdated = false;
	}
	NodeList = NodeListBuffer;
}

void GameView::PushGeoNode(GeoNode* node)
{
	NodeList.push_back(node);
}

void GameView::PushGrassNode(GeoNode* node)
{
	GrassList.push_back(node);
}

void GameView::PushEnvironmentNode(GeoNode* node){
	EnvironmentList.push_back(node);
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