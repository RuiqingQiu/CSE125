#include "stdafx.h"
#include "Model3DFactory.h"
static vector<RenderObject*> render_obj_lst;

Model3DFactory::Model3DFactory()
{
	//blocks
	render_obj_lst.push_back(new RenderObject("Assets/BasicCube/cube2.obj", "Assets/BasicCube/tex.png", "Assets/BasicCube/normals.png", "Assets/BasicCube/gloss.png", "Assets/BasicCube/metallic.png"));
	render_obj_lst.push_back(new RenderObject("Assets/WhiteCube/simplecube2.obj", "Assets/WhiteCube/tex.png", "Assets/WhiteCube/normals.png", "Assets/WhiteCube/gloss.png", "Assets/WhiteCube/metallic.png"));
	render_obj_lst.push_back(new RenderObject("Assets/WoodenCube/woodcube.obj", "Assets/WoodenCube/tex.png", "Assets/WoodenCube/normals.png", "Assets/WoodenCube/gloss.png", "Assets/WoodenCube/metallic.png"));

	//weapons
	render_obj_lst.push_back(new RenderObject("Assets/Mace/mace.obj", "Assets/Mace/tex.png", "Assets/Mace/normals.png", "Assets/Mace/gloss.png", "Assets/Mace/metallic.png"));
	render_obj_lst.push_back(new RenderObject("Assets/Hammer/Hammer.obj", "Assets/Hammer/tex.png", "Assets/Hammer/normals.png", "Assets/Hammer/gloss.png", "Assets/Hammer/metallic.png"));
	render_obj_lst.push_back(new RenderObject("Assets/Needle/needle.obj", "Assets/Needle/tex.png", "Assets/Needle/normals.png", "Assets/Needle/gloss.png", "Assets/Needle/metallic.png"));

	//wheels
	render_obj_lst.push_back(new RenderObject("Assets/MetalWheel/metalwheel.obj", "Assets/MetalWheel/tex.png", "Assets/MetalWheel/normals.png", "Assets/MetalWheel/gloss.png", "Assets/MetalWheel/metallic.png"));
	render_obj_lst.push_back(new RenderObject("Assets/Tire/tire.obj", "Assets/Tire/tex.png", "Assets/Tire/normals.png", "Assets/Tire/gloss.png", "Assets/Tire/metallic.png"));
	render_obj_lst.push_back(new RenderObject("Assets/WoodenWheel/woodwheel.obj", "Assets/WoodenWheel/tex.png", "Assets/WoodenWheel/normals.png", "Assets/WoodenWheel/gloss.png", "Assets/WoodenWheel/metallic.png"));
	render_obj_lst.push_back(new RenderObject("Assets/BattleField/battlefield.obj", "Assets/BattleField/tex.png", "Assets/BattleField/normals.png", "Assets/BattleField/gloss.png", "Assets/BattleField/metallic.png"));

}


Model3DFactory::~Model3DFactory()
{
}

Model3D* Model3DFactory::generateObjectWithType(int type){
	switch (type){
		case Mallet:{
			return new Model3D(render_obj_lst[type]);
			break;
		}
		case Mace:{
			return new Model3D(render_obj_lst[type]);
			break;
		}
		case Discount:{
			return new Model3D(render_obj_lst[type]);
			break;
		}
		case Needle:{
			return new Model3D(render_obj_lst[type]);
			break;
		}
		case BasicCube:{
			return new Model3D(render_obj_lst[type]);
			break;
		}
		case WoodenCube:{
			return new Model3D(render_obj_lst[type]);
			break;
		}
		case WoodenWheel:{
			return new Model3D(render_obj_lst[type]);
			break;
		}
		case Tire:{
			return new Model3D(render_obj_lst[type]);
			break;
		}
		case GlowingCube:{
			return new Model3D(render_obj_lst[type]);
			break;
		}
		case BATTLEFIELD:{
			cout << "here" << endl;
			return new Model3D(render_obj_lst[type]);
			break;
		}
		case WALL:{
					  break;
		}
		case BULLET_1:{
						  break;
		}

	}
}

