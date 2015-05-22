#include "stdafx.h"
#include "GraphicsTest.h"


GraphicsTest::GraphicsTest()
{
}


GraphicsTest::~GraphicsTest()
{
}

void GraphicsTest::displayTest6(GameView* view){
	int x = -20;
	Model3D* object;
	for (int i = BasicCube; i <= BLACKCUBE; i++){
		object = Model3DFactory::generateObjectWithType(i);
		object->shader_type = LIGHTS_SHADER;
		object->localTransform.position = Vector3(x, 0, 0);
		x += 2;
		object->localTransform.rotation = Vector3(0, 0, 0);
		object->identifier = -1;
		object->isUpdated = true;
		object->type = i;
		view->PushEnvironmentNode(object);
	}
	for (int i = BGun; i <= Railgun; i++){
		object = Model3DFactory::generateObjectWithType(i);
		object->shader_type = LIGHTS_SHADER;
		object->localTransform.position = Vector3(x, 0, 0);
		x += 2;
		object->localTransform.rotation = Vector3(0, 0, 0);
		object->identifier = -1;
		object->isUpdated = true;
		object->type = i;
		view->PushEnvironmentNode(object);
	}
	for (int i = Discount; i <= TronWheel; i++){
		object = Model3DFactory::generateObjectWithType(i);
		object->shader_type = LIGHTS_SHADER;
		object->localTransform.position = Vector3(x, 0, 0);
		x += 2;
		object->localTransform.rotation = Vector3(0, 0, 0);
		object->identifier = -1;
		object->isUpdated = true;
		object->type = i;
		view->PushEnvironmentNode(object);
	}

}



void GraphicsTest::displayTest5(GameView* view){
	Model3D* object;
	object = Model3DFactory::generateObjectWithType(Turrent);
	object->shader_type = LIGHTS_SHADER;
	object->localTransform.position = Vector3(0, 0, 0);
	object->localTransform.rotation = Vector3(0, 0, 0);
	object->identifier = -1;
	object->isUpdated = true;
	object->type = Turrent;
	view->PushEnvironmentNode(object);

	object = Model3DFactory::generateObjectWithType(BGun);
	object->shader_type = LIGHTS_SHADER;
	object->localTransform.position = Vector3(5, 0, 0);
	object->localTransform.rotation = Vector3(0, 0, 0);
	object->identifier = -1;
	object->isUpdated = true;
	object->type = BGun;
	view->PushEnvironmentNode(object);

	object = Model3DFactory::generateObjectWithType(Needle);
	object->shader_type = LIGHTS_SHADER;
	object->localTransform.position = Vector3(-5, 0, 0);
	object->localTransform.rotation = Vector3(0, 0, 0);
	object->identifier = -1;
	object->isUpdated = true;
	object->type = Needle;
	view->PushEnvironmentNode(object);

	/*
	for (int i = 0; i < 1000; i++){
		object = Model3DFactory::generateObjectWithType(WoodenCube);
		object->auto_rotate = true;
		object->shader_type = NORMAL_SHADER;
		object->localTransform.position = Vector3(i, 0, 0);
		object->localTransform.rotation = Vector3(0, 0, 0);
		object->identifier = -1;
		object->isUpdated = true;
		object->type = WoodenCube;
		view->PushEnvironmentNode(object);
	}
	*/
}


void GraphicsTest::displayTest3(GameView* view){
	Model3D* object;
	object = Model3DFactory::generateObjectWithType(DESERT);
	object->shader_type = BATTLEFIELD_SHADER;
	object->localTransform.position = Vector3(0, -2, 0);
	object->localTransform.rotation = Vector3(0, 0, 0);
	object->identifier = -1;
	//object->auto_rotate = true;
	object->isUpdated = true;
	object->type = DESERT;
	view->PushEnvironmentNode(object);

	object = Model3DFactory::generateObjectWithType(ALTMACE);
	object->shader_type = NORMAL_SHADER;
	object->localTransform.position = Vector3(5, 2, 0);
	object->localTransform.rotation = Vector3(0, 0, 0);
	object->identifier = -1;
	//object->auto_rotate = true;
	object->isUpdated = true;
	object->type = ALTMACE;
	view->PushGeoNode(object);

	object = Model3DFactory::generateObjectWithType(ALTNEEDLE);
	object->shader_type = NORMAL_SHADER;
	object->localTransform.position = Vector3(-5, 2, 0);
	object->localTransform.rotation = Vector3(0, 0, 0);
	object->identifier = -1;
	//object->auto_rotate = true;
	object->isUpdated = true;
	object->type = ALTNEEDLE;
	view->PushGeoNode(object);
}


void GraphicsTest::displayTest4(GameView* view){
	cout << "enter test 4" << endl;
	/*
	for (int i = 0; i < 10; i++){
		if (i == 1 || i == 4 || i == BATTLEFIELD_SHADER)
			continue;
		Model3D* object;
		object = Model3DFactory::generateObjectWithType(BasicCube);
		object->shader_type = i;
		object->localTransform.position = Vector3(0, 0, -20);
		object->localTransform.rotation = Vector3(0, 0, 0);
		object->identifier = -1;
		//object->auto_rotate = true;
		object->isUpdated = true;
		object->type = BasicCube;
		cout << "here" << endl;
		view->PushGeoNode(object);
	}
	*/
	Model3D* object;
	object = Model3DFactory::generateObjectWithType(BGun);
	object->shader_type = REGULAR_SHADER;
	object->localTransform.position = Vector3(10, 0, -20);
	object->localTransform.rotation = Vector3(0, 0, 0);
	object->identifier = -1;
	//object->auto_rotate = true;
	object->isUpdated = true;
	object->type = BGun;
	cout << "here" << endl;
	view->PushGeoNode(object);

	object = Model3DFactory::generateObjectWithType(BGun);
	object->shader_type = REFLECTION_SHADER;
	object->localTransform.position = Vector3(-5, 0, -20);
	object->localTransform.rotation = Vector3(0, 0, 0);
	object->identifier = -1;
	//object->auto_rotate = true;
	object->isUpdated = true;
	object->type = BGun;
	cout << "here" << endl;
	view->PushGeoNode(object);

	object = Model3DFactory::generateObjectWithType(BGun);
	object->shader_type = REFRACTION_SHADER;
	object->localTransform.position = Vector3(6, 0, -20);
	object->localTransform.rotation = Vector3(0, 0, 0);
	object->identifier = -1;
	//object->auto_rotate = true;
	object->isUpdated = true;
	object->type = BGun;
	cout << "here" << endl;
	view->PushGeoNode(object);

	object = Model3DFactory::generateObjectWithType(BGun);
	object->shader_type = NORMAL_SHADER;
	object->localTransform.position = Vector3(4, 0, -20);
	object->localTransform.rotation = Vector3(0, 0, 0);
	object->identifier = -1;
	//object->auto_rotate = true;
	object->isUpdated = true;
	object->type = BGun;
	cout << "here" << endl;
	view->PushGeoNode(object);

	object = Model3DFactory::generateObjectWithType(BGun);
	object->shader_type = EDGE_SHADER;
	object->edge_highlight = true;
	object->localTransform.position = Vector3(2, 0, -20);
	object->localTransform.rotation = Vector3(0, 0, 0);
	object->identifier = -1;
	//object->auto_rotate = true;
	object->isUpdated = true;
	object->type = BGun;
	cout << "here" << endl;
	view->PushGeoNode(object);

	object = Model3DFactory::generateObjectWithType(BGun);
	object->shader_type = BLUR_SHADER;
	object->blur = true;
	object->localTransform.position = Vector3(0, 0, -20);
	object->localTransform.rotation = Vector3(0, 0, 0);
	object->identifier = -1;
	//object->auto_rotate = true;
	object->isUpdated = true;
	object->type = BGun;
	cout << "here" << endl;
	view->PushGeoNode(object);

	object = Model3DFactory::generateObjectWithType(AltTire);
	object->shader_type = NORMAL_SHADER;
	object->localTransform.position = Vector3(-5, 0, -10);
	object->localTransform.rotation = Vector3(0, 0, 0);
	object->identifier = -1;
	//object->auto_rotate = true;
	object->isUpdated = true;
	object->type = AltTire;
	view->PushGeoNode(object);

	object = Model3DFactory::generateObjectWithType(StoneTire);
	object->shader_type = NORMAL_SHADER;
	object->localTransform.position = Vector3(-3, 0, -10);
	object->localTransform.rotation = Vector3(0, 0, 0);
	object->identifier = -1;
	//object->auto_rotate = true;
	object->isUpdated = true;
	object->type = StoneTire;
	view->PushGeoNode(object);

	object = Model3DFactory::generateObjectWithType(TronWheel);
	object->shader_type = NORMAL_SHADER;
	object->localTransform.position = Vector3(-1, 0, -10);
	object->localTransform.rotation = Vector3(0, 0, 0);
	object->identifier = -1;
	//object->auto_rotate = true;
	object->isUpdated = true;
	object->type = TronWheel;
	view->PushGeoNode(object);

	object = Model3DFactory::generateObjectWithType(Turrent);
	object->shader_type = NORMAL_SHADER;
	object->localTransform.position = Vector3(1, 0, -10);
	object->localTransform.rotation = Vector3(0, 0, 0);
	object->identifier = -1;
	//object->auto_rotate = true;
	object->isUpdated = true;
	object->type = Turrent;
	view->PushGeoNode(object);

	object = Model3DFactory::generateObjectWithType(Railgun);
	object->shader_type = NORMAL_SHADER;
	object->localTransform.position = Vector3(3, 0, -10);
	object->localTransform.rotation = Vector3(0, 0, 0);
	object->identifier = -1;
	//object->auto_rotate = true;
	object->isUpdated = true;
	object->type = Railgun;
	view->PushGeoNode(object);
}

//This is for testing materials
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
		object = Model3DFactory::generateObjectWithType(BGun);
		object->shader_type = MATERIAL_SHADER;
		object->localTransform.position = Vector3(i*5 - 100, 0, 0);
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
	
	object = Model3DFactory::generateObjectWithType(Mallet);
	object->shader_type = REFRACTION_SHADER;
	object->blur = true;
	object->localTransform.position = Vector3(7, 0, -20);
	object->localTransform.rotation = Vector3(0, 0, 0);
	object->identifier = -1;
	//object->auto_rotate = true;
	object->isUpdated = true;
	object->type = Mallet;

	view->PushGeoNode(object);
	for (int i = 8; i < 11; i++){
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

	for (int i = 0; i < 10; i++){
		object = Model3DFactory::generateObjectWithType(BGun);
		object->shader_type = NORMAL_SHADER;
		object->localTransform.position = Vector3(i, 0, -10);
		object->localTransform.rotation = Vector3(0, 0, 0);
		object->identifier = -1;
		//object->auto_rotate = true;
		object->isUpdated = true;
		object->type = BGun;
		view->PushGeoNode(object);
	}
}


