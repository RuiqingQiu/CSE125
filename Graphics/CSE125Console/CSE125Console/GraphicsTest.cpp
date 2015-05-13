#include "stdafx.h"
#include "GraphicsTest.h"


GraphicsTest::GraphicsTest()
{
}


GraphicsTest::~GraphicsTest()
{
}

void GraphicsTest::displayTest2(GameView* view){
	Model3D* object;
	object = Model3DFactory::generateObjectWithType(BasicCube);
	object->shader_type = REFLECTION_SHADER;
	object->localTransform.position = Vector3(0, 0, -20);
	object->localTransform.rotation = Vector3(0, 0, 0);
	object->identifier = -1;
	//object->auto_rotate = true;
	object->isUpdated = true;
	object->type = BGun;
	view->PushGeoNode(object);

	for (int i = 9; i < 24; i++){
		object = Model3DFactory::generateObjectWithType(BasicCube);
		object->shader_type = MATERIAL_SHADER;
		object->localTransform.position = Vector3(i*5 - 100, 0, -10);
		object->localTransform.rotation = Vector3(0, 0, 0);
		object->identifier = -1;
		//object->auto_rotate = true;
		object->isUpdated = true;
		object->type = BGun;
		view->PushGeoNode(object);
		object->material.setMaterial_Property(i);
	}
}


//
void GraphicsTest::displayTest1(GameView* view){
	Model3D* object;
	object = Model3DFactory::generateObjectWithType(BGun);
	object->shader_type = EDGE_SHADER;
	object->edge_highlight = true;
	object->localTransform.position = Vector3(0, 0, -25);
	object->localTransform.rotation = Vector3(0, 0, 0);
	object->identifier = -1;
	//object->auto_rotate = true;
	object->isUpdated = true;
	object->type = BGun;
	view->PushGeoNode(object);

	object = Model3DFactory::generateObjectWithType(BasicCube);
	object->shader_type = NORMAL_SHADER;
	object->localTransform.position = Vector3(-5, 0, -20);
	object->localTransform.rotation = Vector3(0, 0, 0);
	object->identifier = -1;
	//object->auto_rotate = true;
	object->isUpdated = true;
	object->type = BasicCube;
	view->PushGeoNode(object);

	object = Model3DFactory::generateObjectWithType(CrystalCube);
	object->shader_type = REFLECTION_SHADER;
	object->localTransform.position = Vector3(-3, 0, -20);
	object->localTransform.rotation = Vector3(0, 0, 0);
	object->identifier = -1;
	//object->auto_rotate = true;
	object->isUpdated = true;
	object->type = CrystalCube;
	view->PushGeoNode(object);

	object = Model3DFactory::generateObjectWithType(GlowingCube);
	object->shader_type = REGULAR_SHADER;
	object->localTransform.position = Vector3(3, 0, -20);
	object->localTransform.rotation = Vector3(0, 0, 0);
	object->identifier = -1;
	//object->auto_rotate = true;
	object->isUpdated = true;
	object->type = GlowingCube;
	view->PushGeoNode(object);

	object = Model3DFactory::generateObjectWithType(Mace);
	object->shader_type = BLUR_SHADER;
	object->blur = true;
	object->localTransform.position = Vector3(5, 0, -20);
	object->localTransform.rotation = Vector3(0, 0, 0);
	object->identifier = -1;
	//object->auto_rotate = true;
	object->isUpdated = true;
	object->type = Mace;
	view->PushGeoNode(object);

	for (int i = 6; i < 11; i++){
		object = Model3DFactory::generateObjectWithType(i);
		object->shader_type = REFRACTION_SHADER;
		object->blur = true;
		object->localTransform.position = Vector3(i*2, 0, -20);
		object->localTransform.rotation = Vector3(0, 0, 0);
		object->identifier = -1;
		//object->auto_rotate = true;
		object->isUpdated = true;
		object->type = i;
		view->PushGeoNode(object);
	}

	for (int i = 200; i < 203; i++){
		object = Model3DFactory::generateObjectWithType(i);
		object->shader_type = NORMAL_SHADER;
		object->blur = true;
		object->localTransform.position = Vector3((i-190)*2, 0, -20);
		object->localTransform.rotation = Vector3(0, 0, 0);
		object->identifier = -1;
		//object->auto_rotate = true;
		object->isUpdated = true;
		object->type = i;
		view->PushGeoNode(object);
	}

	for (int i = 300; i < 303; i++){
		object = Model3DFactory::generateObjectWithType(i);
		object->shader_type = NORMAL_SHADER;
		object->blur = true;
		object->localTransform.position = Vector3((i-280) * 5, 0, -20);
		object->localTransform.rotation = Vector3(0, 0, 0);
		object->identifier = -1;
		//object->auto_rotate = true;
		object->isUpdated = true;
		object->type = i;
		view->PushGeoNode(object);
	}
	
	object = Model3DFactory::generateObjectWithType(BULLET);
	object->shader_type = REGULAR_SHADER;
	object->localTransform.position = Vector3(0, 0, -20);
	object->localTransform.rotation = Vector3(0, 0, 0);
	object->identifier = -1;
	//object->auto_rotate = true;
	object->isUpdated = true;
	object->type = BULLET;
	view->PushGeoNode(object);

}


