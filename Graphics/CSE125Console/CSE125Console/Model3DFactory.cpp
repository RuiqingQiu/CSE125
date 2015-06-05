#include "stdafx.h"
#include "Model3DFactory.h"
#include "Model3DGroup.h"

static vector<RenderObject*> render_obj_lst;
static map<int, RenderObject*> render_obj_map;

Model3DFactory::Model3DFactory()
{
	cout << "Model3DFactory loading" << endl;
	
	//blocks
	render_obj_map.insert(std::pair<int, RenderObject*>(BasicCube, new RenderObject("Assets/BasicCube/cube2.obj", "Assets/BasicCube/tex.png", "Assets/BasicCube/normals.png", "Assets/BasicCube/gloss.png", "Assets/BasicCube/metallic.png")));

	
	render_obj_map.insert(std::pair<int, RenderObject*>(CrystalCube, new RenderObject("Assets/CrystalMethCube/cubeofmeth.obj", "Assets/CrystalMethCube/tex.png", "Assets/CrystalMethCube/normals.png", "Assets/CrystalMethCube/gloss.png", "Assets/CrystalMethCube/metallic.png")));
	render_obj_map.insert(std::pair<int, RenderObject*>(GlowingCube, new RenderObject("Assets/WhiteCube/simplecube2.obj", "Assets/WhiteCube/tex.png", "Assets/WhiteCube/normals.png", "Assets/WhiteCube/gloss.png", "Assets/WhiteCube/metallic.png")));
	render_obj_map.insert(std::pair<int, RenderObject*>(WoodenCube, new RenderObject("Assets/WoodenCube/woodcube.obj", "Assets/WoodenCube/tex.png", "Assets/WoodenCube/normals.png", "Assets/WoodenCube/gloss.png", "Assets/WoodenCube/metallic.png")));
	render_obj_map.insert(std::pair<int, RenderObject*>(BLACKCUBE, new RenderObject("Assets/BlackCube/blackcube.obj", "Assets/BlackCube/tex.png", "Assets/BlackCube/normals.png", "Assets/BlackCube/gloss.png", "Assets/BlackCube/metallic.png")));
	//render_obj_map.insert(std::pair<int, RenderObject*>(CUBEA, new RenderObject("Assets/CubeA/cubea.obj", "Assets/CubeA/tex.png", "Assets/CubeA/normals.png", "Assets/CubeA/gloss.png", "Assets/CubeA/metallic.png")));
	//render_obj_map.insert(std::pair<int, RenderObject*>(CUBEB, new RenderObject("Assets/CubeB/cubeb.obj", "Assets/CubeB/tex.png", "Assets/CubeB/normals.png", "Assets/CubeB/gloss.png", "Assets/CubeB/metallic.png")));
	
	//weapons
	render_obj_map.insert(std::pair<int, RenderObject*>(BGun, new RenderObject("Assets/BlockyGun/gat.obj", "Assets/BlockyGun/tex.png", "Assets/BlockyGun/normals.png", "Assets/BlockyGun/gloss.png", "Assets/BlockyGun/metallic.png")));
	render_obj_map.insert(std::pair<int, RenderObject*>(Mace, new RenderObject("Assets/Mace/mace.obj", "Assets/Mace/tex.png", "Assets/Mace/normals.png", "Assets/Mace/gloss.png", "Assets/Mace/metallic.png")));
	render_obj_map.insert(std::pair<int, RenderObject*>(Mallet, new RenderObject("Assets/Hammer/Hammer.obj", "Assets/Hammer/tex.png", "Assets/Hammer/normals.png", "Assets/Hammer/gloss.png", "Assets/Hammer/metallic.png")));
	render_obj_map.insert(std::pair<int, RenderObject*>(Needle, new RenderObject("Assets/Needle/needle.obj", "Assets/Needle/tex.png", "Assets/Needle/normals.png", "Assets/Needle/gloss.png", "Assets/Needle/metallic.png")));
	//render_obj_map.insert(std::pair<int, RenderObject*>(ALTNEEDLE, new RenderObject("Assets/AltNeedle/altneedle.obj", "Assets/AltNeedle/tex.png", "Assets/AltNeedle/normals.png", "Assets/AltNeedle/gloss.png", "Assets/AltNeedle/metallic.png")));
	//render_obj_map.insert(std::pair<int, RenderObject*>(ALTMACE, new RenderObject("Assets/AltMace/final.obj", "Assets/AltMace/tex.png", "Assets/AltMace/normals.png", "Assets/AltMace/gloss.png", "Assets/AltMace/metallic.png")));
	render_obj_map.insert(std::pair<int, RenderObject*>(Turrent, new RenderObject("Assets/PirateCannon/cannon.obj", "Assets/PirateCannon/tex.png", "Assets/PirateCannon/normals.png", "Assets/PirateCannon/gloss.png", "Assets/PirateCannon/metallic.png")));
	render_obj_map.insert(std::pair<int, RenderObject*>(Railgun, new RenderObject("Assets/Railgun/railgun.obj", "Assets/Railgun/tex.png", "Assets/Railgun/normals.png", "Assets/Railgun/gloss.png", "Assets/Railgun/metallic.png")));

	//wheels
	render_obj_map.insert(std::pair<int, RenderObject*>(Discount, new RenderObject("Assets/MetalWheel/metalwheel.obj", "Assets/MetalWheel/tex.png", "Assets/MetalWheel/normals.png", "Assets/MetalWheel/gloss.png", "Assets/MetalWheel/metallic.png")));
	//render_obj_map.insert(std::pair<int, RenderObject*>(Tire, new RenderObject("Assets/Tire/tire.obj", "Assets/Tire/tex.png", "Assets/Tire/normals.png", "Assets/Tire/gloss.png", "Assets/Tire/metallic.png")));
	render_obj_map.insert(std::pair<int, RenderObject*>(WoodenWheel, new RenderObject("Assets/WoodenWheel/woodwheel.obj", "Assets/WoodenWheel/tex.png", "Assets/WoodenWheel/normals.png", "Assets/WoodenWheel/gloss.png", "Assets/WoodenWheel/metallic.png")));
	render_obj_map.insert(std::pair<int, RenderObject*>(AltTire, new RenderObject("Assets/AltTire/alt-tire.obj", "Assets/AltTire/tex.png", "Assets/AltTire/normals.png", "Assets/AltTire/gloss.png", "Assets/AltTire/metallic.png")));
	render_obj_map.insert(std::pair<int, RenderObject*>(StoneTire, new RenderObject("Assets/StoneTire/crackedstone.obj", "Assets/StoneTire/tex.png", "Assets/StoneTire/normals.png", "Assets/StoneTire/gloss.png", "Assets/StoneTire/metallic.png")));
	render_obj_map.insert(std::pair<int, RenderObject*>(TronWheel, new RenderObject("Assets/TronWheel/tron.obj", "Assets/TronWheel/tex.png", "Assets/TronWheel/normals.png", "Assets/TronWheel/gloss.png", "Assets/TronWheel/metallic.png")));

	//other
	//render_obj_map.insert(std::pair<int, RenderObject*>(BATTLEFIELD, new RenderObject("Assets/BattleField/checkerboard.obj", "Assets/BattleField/tex.png", "Assets/BattleField/normals.png", "Assets/BattleField/gloss.png", "Assets/BattleField/metallic.png")));
	//render_obj_map.insert(std::pair<int, RenderObject*>(TREE1, new RenderObject("Assets/Tree1/tree.obj", "Assets/Tree1/tex.png", "Assets/Tree1/normals.png", "Assets/Tree1/gloss.png", "Assets/Tree1/metallic.png")));
	//render_obj_map.insert(std::pair<int, RenderObject*>(TREE2, new RenderObject("Assets/Tree2/tree.obj", "Assets/Tree2/tex.png", "Assets/Tree2/normals.png", "Assets/Tree2/gloss.png", "Assets/Tree2/metallic.png")));
	//render_obj_map.insert(std::pair<int, RenderObject*>(TREE3, new RenderObject("Assets/Tree3/tree.obj", "Assets/Tree3/tex.png", "Assets/Tree3/normals.png", "Assets/Tree3/gloss.png", "Assets/Tree3/metallic.png")));
	
	//super battlefield
	//render_obj_map.insert(std::pair<int, RenderObject*>(BATTLEFIELDINNER, new RenderObject("Assets/BattleFieldInner/inner.obj", "Assets/BattleFieldInner/tex.png", "Assets/BattleFieldInner/normals.png", "Assets/BattleFieldInner/gloss.png", "Assets/BattleFieldInner/metallic.png")));
	//render_obj_map.insert(std::pair<int, RenderObject*>(BATTLEFIELDOUTER, new RenderObject("Assets/BattleFieldOuter/plane.obj", "Assets/BattleFieldOuter/tex.png", "Assets/BattleFieldOuter/normals.png", "Assets/BattleFieldOuter/gloss.png", "Assets/BattleFieldOuter/metallic.png")));
	render_obj_map.insert(std::pair<int, RenderObject*>(BULLET, new RenderObject("Assets/Bullet/bullet.obj", "Assets/Bullet/tex.png", "Assets/Bullet/normals.png", "Assets/Bullet/gloss.png", "Assets/Bullet/metallic.png")));
	render_obj_map.insert(std::pair<int, RenderObject*>(CANNONBALL, new RenderObject("Assets/Cannonball/cannonball.obj", "Assets/Cannonball/tex.png", "Assets/Cannonball/normals.png", "Assets/Cannonball/gloss.png", "Assets/Cannonball/metallic.png")));

	//Newly added 5/26/15
	render_obj_map.insert(std::pair<int, RenderObject*>(BORDER, new RenderObject("Assets/Border/border.obj", "Assets/Border/tex.png", "Assets/Border/normals.png", "Assets/Border/gloss.png", "Assets/Border/metallic.png")));
	render_obj_map.insert(std::pair<int, RenderObject*>(CHESSBOARD, new RenderObject("Assets/Chessboard/chessboard.obj", "Assets/Chessboard/tex.png", "Assets/Chessboard/normals.png", "Assets/Chessboard/gloss.png", "Assets/Chessboard/metallic.png")));
	render_obj_map.insert(std::pair<int, RenderObject*>(FLOOR_COMPLEX, new RenderObject("Assets/FloorComplex/floor2.obj", "Assets/FloorComplex/tex.png", "Assets/FloorComplex/normals.png", "Assets/FloorComplex/gloss.png", "Assets/FloorComplex/metallic.png")));
	render_obj_map.insert(std::pair<int, RenderObject*>(FLOOR_SIMPLE, new RenderObject("Assets/FloorSimple/floor1.obj", "Assets/FloorSimple/tex.png", "Assets/FloorSimple/normals.png", "Assets/FloorSimple/gloss.png", "Assets/FloorSimple/metallic.png")));
	render_obj_map.insert(std::pair<int, RenderObject*>(STONEHENGE, new RenderObject("Assets/Stonehenge/sandhenge.obj", "Assets/Stonehenge/tex.png", "Assets/Stonehenge/normals.png", "Assets/Stonehenge/gloss.png", "Assets/Stonehenge/metallic.png")));
	
	//Building is gone
	//render_obj_map.insert(std::pair<int, RenderObject*>(BUILDING, new RenderObject("Assets/Building/sandruins.obj", "Assets/Building/tex.png", "Assets/Building/normals.png", "Assets/Building/gloss.png", "Assets/Building/metallic.png")));
	
	render_obj_map.insert(std::pair<int, RenderObject*>(DESERT, new RenderObject("Assets/Desert/desert.obj", "Assets/Desert/tex.png", "Assets/Desert/normals.png", "Assets/Desert/gloss.png", "Assets/Desert/metallic.png")));
	render_obj_map.insert(std::pair<int, RenderObject*>(LEGO, new RenderObject("Assets/legoblock/legoblock.obj", "Assets/legoblock/tex.png", "Assets/legoblock/normals.png", "Assets/legoblock/gloss.png", "Assets/legoblock/metallic.png")));

	//Moneyzone obbjects
	render_obj_map.insert(std::pair<int, RenderObject*>(DOLLAR, new RenderObject("Assets/MoneyZone/DollarSign/dollar.obj", "Assets/MoneyZone/DollarSign/tex.png", "Assets/MoneyZone/DollarSign/normals.png", "Assets/MoneyZone/DollarSign/gloss.png", "Assets/MoneyZone/DollarSign/metallic.png")));
	render_obj_map.insert(std::pair<int, RenderObject*>(CROWN, new RenderObject("Assets/Crown/crown.obj", "Assets/Crown/tex.png", "Assets/Crown/normals.png", "Assets/Crown/gloss.png", "Assets/Crown/metallic.png")));
	
	render_obj_map.insert(std::pair<int, RenderObject*>(LASER, new RenderObject("Assets/Laserbeam/laserbeam.obj", "Assets/Laserbeam/tex.png", "Assets/Laserbeam/normals.png", "Assets/Laserbeam/gloss.png", "Assets/Laserbeam/metallic.png")));

	cout << "Model3DFactory loading done" << endl;

}


Model3DFactory::~Model3DFactory()
{
}

Model3D* Model3DFactory::generateDefault() {
	cout << "model is not there, using BasicCube" << endl;
	Model3D * returnModel = new Model3D(render_obj_map[BasicCube]);
	returnModel->type = BasicCube;
	returnModel->cost = 10;
	return returnModel;
}

Model3D* Model3DFactory::generateObjectWithType(int type){
	switch (type){
	case LASER:{
				   if (render_obj_map[type] == nullptr){
					   cout << "model is not there, using BasicCube" << endl;
					   Model3D * returnModel = new Model3D(render_obj_map[BasicCube]);
					   returnModel->type = BasicCube;
					   return returnModel;
				   }
				   Model3D * returnModel = new Model3D(render_obj_map[type]);
				   returnModel->type = Mallet;
				   returnModel->damageStat = 1;
				   returnModel->cost = 1;
				   return returnModel;
				   break;
	}
	case CANNONBALL:{
						if (render_obj_map[type] == nullptr){
							cout << "model is not there, using BasicCube" << endl;
							Model3D * returnModel = new Model3D(render_obj_map[BasicCube]);
							returnModel->type = BasicCube;
							return returnModel;
						}
						Model3D * returnModel = new Model3D(render_obj_map[type]);
						returnModel->type = Mallet;
						returnModel->damageStat = 1;
						returnModel->cost = 1;
						return returnModel;
						break;
	}
	case LEGO:{
				  if (render_obj_map[type] == nullptr){
					  cout << "model is not there, using BasicCube" << endl;
					  Model3D * returnModel = new Model3D(render_obj_map[BasicCube]);
					  returnModel->type = BasicCube;
					  return returnModel;
				  }
				  Model3D * returnModel = new Model3D(render_obj_map[type]);
				  returnModel->type = Mallet;
				  returnModel->damageStat = 1;
				  returnModel->cost = 1;
				  return returnModel;
				  break;
	}
	/////////////////////////////WEAPONS//////////////////////////////
	case BGun:{
				  if (render_obj_map[type] == nullptr) {
					  return generateDefault();
				  }
				  Model3D * returnModel = new Model3D(render_obj_map[type]);
				  returnModel->healthStat = 1;
				  returnModel->type = BGun;
				  returnModel->cost = 25;
				  return returnModel;
				  break;
	}
	case Mace: {
				   if (render_obj_map[type] == nullptr) {
					   return generateDefault();
				   }
				  Model3D * returnModel = new Model3D(render_obj_map[type]);
				  returnModel->damageStat = 1;
				  returnModel->type = Mace;
				  returnModel->cost = 20;
				  return returnModel;
				  break;
	}
	case Mallet: {
					 if (render_obj_map[type] == nullptr) {
						 return generateDefault();
					 }
					Model3D * returnModel = new Model3D(render_obj_map[type]);
					returnModel->type = Mallet;
					returnModel->damageStat = 1;
					returnModel->cost = 20;
					return returnModel;
					break;
	}
	case Needle:{
					if (render_obj_map[type] == nullptr) {
						return generateDefault();
					}
					Model3D * returnModel = new Model3D(render_obj_map[type]);
					returnModel->damageStat = 1;
					returnModel->type = Needle;
					returnModel->cost = 12;
					return returnModel;
					break;
	}
	case Railgun:{
					 if (render_obj_map[type] == nullptr) {
						 return generateDefault();
					 }
					 Model3D * returnModel = new Model3D(render_obj_map[type]);
					 returnModel->type = Railgun;
					 returnModel->cost = 35;
					 return returnModel;
					 break;

	}
	case Turrent:{
					 if (render_obj_map[type] == nullptr) {
						 return generateDefault();
					 }
					 Model3D * returnModel = new Model3D(render_obj_map[type]);
					 returnModel->type = Turrent;
					 returnModel->cost = 30;
					 return returnModel;
					 break;
	}
		/*
	case ALTMACE:{
					Model3D * returnModel = new Model3D(render_obj_map[type]);
					returnModel->type = ALTMACE;
					returnModel->cost = 1;
					return returnModel;
					break;
	}
	case ALTNEEDLE:{
					Model3D * returnModel = new Model3D(render_obj_map[type]);
					returnModel->type = ALTNEEDLE;
					returnModel->cost = 1;
					return returnModel;
					break;
	}
		*/

/////////////////////////////CUBES//////////////////////////////
	case BasicCube:{
					   Model3D * returnModel = new Model3D(render_obj_map[type]);
					   returnModel->healthStat = 1;
					   returnModel->cost = 10;
					   returnModel->type = BasicCube;
					   return returnModel;
					   break;
	}
	case WoodenCube:{
						if (render_obj_map[type] == nullptr) {
							return generateDefault();
						}
						Model3D * returnModel = new Model3D(render_obj_map[type]);
						returnModel->type = WoodenCube;
						returnModel->cost = 0;
						returnModel->healthStat = 1;
						return returnModel;
						break;
	}
	case BLACKCUBE:{
					   if (render_obj_map[type] == nullptr) {
						   return generateDefault();
					   }
					   Model3D * returnModel = new Model3D(render_obj_map[type]);
					   returnModel->type = BLACKCUBE;
					   returnModel->healthStat = 1;
					   returnModel->cost = 20;
					   return returnModel;
					   break;
	}
	case GlowingCube:{
						 if (render_obj_map[type] == nullptr) {
							 return generateDefault();
						 }
						 Model3D * returnModel = new Model3D(render_obj_map[type]);
						 returnModel->healthStat = 1;
						 returnModel->type = GlowingCube;
						 returnModel->cost = 20;
						 return returnModel;
						 break;
	}
	case CrystalCube:{
						 if (render_obj_map[type] == nullptr) {
							 return generateDefault();
						 }
						 Model3D * returnModel = new Model3D(render_obj_map[type]);
						 returnModel->type = CrystalCube;
						 returnModel->cost = 15;
						 return returnModel;
						 break;
	}
	/*
	case CUBEA:{
	if (render_obj_map[type] == nullptr) {
	return generateDefault();
	}
				   Model3D * returnModel = new Model3D(render_obj_map[type]);
				   returnModel->type = CUBEA;
				   returnModel->healthStat = 1;
				   returnModel->cost = 1;
				   return returnModel;
				   break;
	}
	case CUBEB:{
	if (render_obj_map[type] == nullptr) {
	return generateDefault();
	}
				   Model3D * returnModel = new Model3D(render_obj_map[type]);
				   returnModel->type = CUBEB;
				   returnModel->healthStat = 1;
				   returnModel->cost = 1;
				   return returnModel;
				   break;
	}
	*/
	/////////////////////////////WHEELS//////////////////////////////
	case Discount:{
					  if (render_obj_map[type] == nullptr) {
						  return generateDefault();
					  }
					  Model3D * returnModel = new Model3D(render_obj_map[type]);
					  returnModel->speedStat = 1;
					  returnModel->type = Discount;
					  returnModel->cost = 20;
					  return returnModel;
					  break;
	}

	case WoodenWheel:{
						 if (render_obj_map[type] == nullptr) {
							 return generateDefault();
						 }
						 Model3D * returnModel = new Model3D(render_obj_map[type]);
						 returnModel->speedStat = 1;
						 returnModel->cost = 10;
						 returnModel->type = WoodenWheel;
						 return returnModel;
						 break;
	}
	/*
	case Tire:{
				  Model3D * returnModel = new Model3D(render_obj_map[type]);
				  returnModel->speedStat = 1;
				  returnModel->cost = 3;
				  returnModel->type = Tire;
				  return returnModel;
				  break;
	} 
	*/
	case AltTire:{
					 if (render_obj_map[type] == nullptr) {
						 return generateDefault();
					 }
					 Model3D * returnModel = new Model3D(render_obj_map[type]);
					 returnModel->type = AltTire;
					 returnModel->cost = 30;
					 return returnModel;
					 break;
	}
	case StoneTire:{
					   if (render_obj_map[type] == nullptr) {
						   return generateDefault();
					   }
					   Model3D * returnModel = new Model3D(render_obj_map[type]);
					   returnModel->type = StoneTire;
					   returnModel->cost = 0;
					   return returnModel;
					   break;
	}
	case TronWheel:{
					   if (render_obj_map[type] == nullptr) {
						   return generateDefault();
					   }
					   Model3D * returnModel = new Model3D(render_obj_map[type]);
					   returnModel->type = TronWheel;
					   returnModel->cost = 40;
					   return returnModel;
					   break;
	}
	/////////////////////////////MODEL GROUPS//////////////////////////////
	case THREEBYTHREE_BASIC:{
								Model3DGroup* group = new Model3DGroup();
								for (int i = -1; i < 2; i++){
									for (int j = -1; j < 2; j++){
										Model3D * returnModel = Model3DFactory::generateObjectWithType(BasicCube);
										returnModel->localTransform.position = Vector3(i, 0, j);
										returnModel->localTransform.scale = Vector3(1, 1, 1);
										returnModel->localTransform.rotation = Vector3(0, 0, 0);
										group->addObject(returnModel);
									}
								}
								group->width = 3;
								group->height = 1;
								group->cost = 80;
								return group;
								break;
	}
	case THREEBYTHREE_GLOWING:{
								  Model3DGroup* group = new Model3DGroup();
								  for (int i = -1; i < 2; i++){
									  for (int j = -1; j < 2; j++){
										  Model3D * returnModel = Model3DFactory::generateObjectWithType(GlowingCube);
										  returnModel->localTransform.position = Vector3(i, 0, j);
										  returnModel->localTransform.scale = Vector3(1, 1, 1);
										  returnModel->localTransform.rotation = Vector3(0, 0, 0);
										  group->addObject(returnModel);
									  }
								  }
								  group->width = 3;
								  group->height = 1;
								  group->cost = 160;
								  return group;
								  break;
	}
	case THREEBYTHREE_WOODEN:{
								 Model3DGroup* group = new Model3DGroup();
								 for (int i = -1; i < 2; i++){
									 for (int j = -1; j < 2; j++){
										 Model3D * returnModel = Model3DFactory::generateObjectWithType(WoodenCube);
										 returnModel->localTransform.position = Vector3(i, 0, j);
										 returnModel->localTransform.scale = Vector3(1, 1, 1);
										 returnModel->localTransform.rotation = Vector3(0, 0, 0);
										 group->addObject(returnModel);
									 }
								 }
								 group->cost = 0;
								 group->width = 3;
								 group->height = 1;
								 return group;
								 break;
	}
	case THREEBYTHREE_CRYSTAL:{
								  Model3DGroup* group = new Model3DGroup();
								  for (int i = -1; i < 2; i++){
									  for (int j = -1; j < 2; j++){
										  Model3D * returnModel = Model3DFactory::generateObjectWithType(CrystalCube);
										  returnModel->localTransform.position = Vector3(i, 0, j);
										  returnModel->localTransform.scale = Vector3(1, 1, 1);
										  returnModel->localTransform.rotation = Vector3(0, 0, 0);
										  group->addObject(returnModel);
									  }
								  }
								  group->width = 3;
								  group->height = 1;
								  group->cost = 120;
								  return group;
								  break;
	}
	case THREEBYTHREE_BLACK:{
								  Model3DGroup* group = new Model3DGroup();
								  for (int i = -1; i < 2; i++){
									  for (int j = -1; j < 2; j++){
										  Model3D * returnModel = Model3DFactory::generateObjectWithType(BLACKCUBE);
										  returnModel->localTransform.position = Vector3(i, 0, j);
										  returnModel->localTransform.scale = Vector3(1, 1, 1);
										  returnModel->localTransform.rotation = Vector3(0, 0, 0);
										  group->addObject(returnModel);
									  }
								  }
								  group->width = 3;
								  group->height = 1;
								  group->cost = 160;
								  return group;
								  break;
	}
/*
	case THREEBYTHREE_WHEEL_DISCOUNT:{
										 Model3DGroup* group = new Model3DGroup();
										 Model3D * returnModel = Model3DFactory::generateObjectWithType(Discount);
										 returnModel->localTransform.position = Vector3(-2, 0, -1);
										 returnModel->localTransform.scale = Vector3(1, 1, 1);
										 returnModel->localTransform.rotation = Vector3(0, 0, 0);
										 group->addObject(returnModel);
										 returnModel = Model3DFactory::generateObjectWithType(Discount);
										 returnModel->localTransform.position = Vector3(-2, 0, 1);
										 returnModel->localTransform.scale = Vector3(1, 1, 1);
										 returnModel->localTransform.rotation = Vector3(0, 0, 0);
										 group->addObject(returnModel);

										 returnModel = Model3DFactory::generateObjectWithType(Discount);
										 returnModel->localTransform.position = Vector3(2, 0, -1);
										 returnModel->localTransform.scale = Vector3(1, 1, 1);
										 returnModel->localTransform.rotation = Vector3(0, 0, 0);
										 group->addObject(returnModel);

										 returnModel = Model3DFactory::generateObjectWithType(Discount);
										 returnModel->localTransform.position = Vector3(2, 0, 1);
										 returnModel->localTransform.scale = Vector3(1, 1, 1);
										 returnModel->localTransform.rotation = Vector3(0, 0, 0);
										 group->addObject(returnModel);

										 return group;
										 break;
	}
	case THREEBYTHREE_WHEEL_TIRE:{
									 Model3DGroup* group = new Model3DGroup();
									 Model3D * returnModel = Model3DFactory::generateObjectWithType(Tire);
									 returnModel->localTransform.position = Vector3(-2, 0, -1);
									 returnModel->localTransform.scale = Vector3(1, 1, 1);
									 returnModel->localTransform.rotation = Vector3(0, 0, 0);
									 group->addObject(returnModel);
									 returnModel = Model3DFactory::generateObjectWithType(Tire);
									 returnModel->localTransform.position = Vector3(-2, 0, 1);
									 returnModel->localTransform.scale = Vector3(1, 1, 1);
									 returnModel->localTransform.rotation = Vector3(0, 0, 0);
									 group->addObject(returnModel);

									 returnModel = Model3DFactory::generateObjectWithType(Tire);
									 returnModel->localTransform.position = Vector3(2, 0, -1);
									 returnModel->localTransform.scale = Vector3(1, 1, 1);
									 returnModel->localTransform.rotation = Vector3(0, 0, 0);
									 group->addObject(returnModel);

									 returnModel = Model3DFactory::generateObjectWithType(Tire);
									 returnModel->localTransform.position = Vector3(2, 0, 1);
									 returnModel->localTransform.scale = Vector3(1, 1, 1);
									 returnModel->localTransform.rotation = Vector3(0, 0, 0);
									 group->addObject(returnModel);

									 return group;
									 break;
	}
	case THREEBYTHREE_WHEEL_WOODEN:{
									   Model3DGroup* group = new Model3DGroup();
									   Model3D * returnModel = Model3DFactory::generateObjectWithType(WoodenWheel);
									   returnModel->localTransform.position = Vector3(-2, 0, -1);
									   returnModel->localTransform.scale = Vector3(1, 1, 1);
									   returnModel->localTransform.rotation = Vector3(0, 0, 0);
									   group->addObject(returnModel);
									   returnModel = Model3DFactory::generateObjectWithType(WoodenWheel);
									   returnModel->localTransform.position = Vector3(-2, 0, 1);
									   returnModel->localTransform.scale = Vector3(1, 1, 1);
									   returnModel->localTransform.rotation = Vector3(0, 0, 0);
									   group->addObject(returnModel);

									   returnModel = Model3DFactory::generateObjectWithType(WoodenWheel);
									   returnModel->localTransform.position = Vector3(2, 0, -1);
									   returnModel->localTransform.scale = Vector3(1, 1, 1);
									   returnModel->localTransform.rotation = Vector3(0, 0, 0);
									   group->addObject(returnModel);

									   returnModel = Model3DFactory::generateObjectWithType(WoodenWheel);
									   returnModel->localTransform.position = Vector3(2, 0, 1);
									   returnModel->localTransform.scale = Vector3(1, 1, 1);
									   returnModel->localTransform.rotation = Vector3(0, 0, 0);
									   group->addObject(returnModel);

									   return group;
									   break;
	}
	*/
	/////////////////////////////ENVIRONMENT OBJECTS//////////////////////////////
	case BATTLEFIELD:{
						 if (render_obj_map[type] == nullptr) {
							 return generateDefault();
						 }
						 Model3D * returnModel = new Model3D(render_obj_map[type]);
						 returnModel->type = BATTLEFIELD;
						 return returnModel;
						 break;
	}
	case TREE1:{
				   if (render_obj_map[type] == nullptr) {
					   return generateDefault();
				   }
				   Model3D * returnModel = new Model3D(render_obj_map[type]);
				   returnModel->type = TREE1;
				   return returnModel;
				   break;
	}
	case TREE2:{
				   if (render_obj_map[type] == nullptr) {
					   return generateDefault();
				   }
				   Model3D * returnModel = new Model3D(render_obj_map[type]);
				   returnModel->type = TREE2;
				   return returnModel;
				   break;
	}
	case TREE3:{
				   if (render_obj_map[type] == nullptr) {
					   return generateDefault();
				   }
				   Model3D * returnModel = new Model3D(render_obj_map[type]);
				   returnModel->type = TREE3;
				   return returnModel;
				   break;
	}
	case WALL:{
				  break;
	}
	case BULLET:{
					if (render_obj_map[type] == nullptr) {
						return generateDefault();
					}
					Model3D * returnModel = new Model3D(render_obj_map[type]);
					returnModel->type = BULLET;
					return returnModel;
					break;
	}
	case BATTLEFIELDINNER:{
							  if (render_obj_map[type] == nullptr) {
								  return generateDefault();
							  }
							  Model3D * returnModel = new Model3D(render_obj_map[type]);
							  returnModel->type = BATTLEFIELDINNER;
							  return returnModel;
							  break;
	}
	case BATTLEFIELDOUTER:{
							  if (render_obj_map[type] == nullptr) {
								  return generateDefault();
							  }
							  Model3D * returnModel = new Model3D(render_obj_map[type]);
							  returnModel->type = BATTLEFIELDOUTER;
							  return returnModel;
							  break;
	}
	case DESERT:{
					if (render_obj_map[type] == nullptr) {
						return generateDefault();
					}
					Model3D * returnModel = new Model3D(render_obj_map[type]);
					returnModel->type = DESERT;
					return returnModel;
					break;
	}
	case BUILDING:{
					  if (render_obj_map[type] == nullptr) {
						  return generateDefault();
					  }
					  Model3D * returnModel = new Model3D(render_obj_map[type]);
					  returnModel->type = BUILDING;
					  return returnModel;
					  break;
	}
	case BORDER:{
					if (render_obj_map[type] == nullptr) {
						return generateDefault();
					}
					Model3D * returnModel = new Model3D(render_obj_map[type]);
					returnModel->type = BORDER;
					return returnModel;
					break;
	}
	case CHESSBOARD:{
						if (render_obj_map[type] == nullptr) {
							return generateDefault();
						}
						Model3D * returnModel = new Model3D(render_obj_map[type]);
						returnModel->type = CHESSBOARD;
						return returnModel;
						break;
	}
	case FLOOR_COMPLEX:{
						   if (render_obj_map[type] == nullptr) {
							   return generateDefault();
						   }
						   Model3D * returnModel = new Model3D(render_obj_map[type]);
						   returnModel->type = FLOOR_COMPLEX;
						   return returnModel;
						   break;
	}
	case FLOOR_SIMPLE:{
						  if (render_obj_map[type] == nullptr) {
							  return generateDefault();
						  }
						  Model3D * returnModel = new Model3D(render_obj_map[type]);
						  returnModel->type = FLOOR_SIMPLE;
						  return returnModel;
						  break;
	}
	case STONEHENGE:{
						if (render_obj_map[type] == nullptr) {
							return generateDefault();
						}
						Model3D * returnModel = new Model3D(render_obj_map[type]);
						returnModel->type = STONEHENGE;
						return returnModel;
						break;
	}
	case DOLLAR:{
						if (render_obj_map[type] == nullptr) {
							return generateDefault();
						}
						Model3D * returnModel = new Model3D(render_obj_map[type]);
						returnModel->localTransform.scale = Vector3(3, 3, 3);
						returnModel->type = DOLLAR;
						return returnModel;
						break;
	}
	case CROWN:{
				   if (render_obj_map[type] == nullptr) {
					   return generateDefault();
				   }
				   Model3D * returnModel = new Model3D(render_obj_map[type]);
				   returnModel->type = CROWN;
				   return returnModel;
				   break;
	}
	default: {
				 cout << "type " << type << " is not recognized" << endl;
				 Model3D * returnModel = new Model3D(render_obj_map[BasicCube]);
				 returnModel->type = BasicCube;
				 returnModel->cost = 10;
				 return returnModel;
	}
	}

	Model3D * returnModel = new Model3D(render_obj_map[BasicCube]);
	returnModel->type = BasicCube;
	returnModel->cost = 10;
	return returnModel;
}
