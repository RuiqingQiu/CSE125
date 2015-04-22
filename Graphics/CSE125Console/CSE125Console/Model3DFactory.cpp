#include "stdafx.h"
#include "Model3DFactory.h"
static vector<RenderObject*> render_obj_lst;

Model3DFactory::Model3DFactory()
{
	render_obj_lst.push_back(new RenderObject("Assets/Hammer/Hammer.obj"));
	render_obj_lst.push_back(new RenderObject("Assets/Mace/mace.obj"));

	render_obj_lst.push_back(new RenderObject("Assets/MetalWheel/metalwheel.obj"));

	render_obj_lst.push_back(new RenderObject("Assets/Needle/needle.obj"));	

	render_obj_lst.push_back(new RenderObject("Assets/BasicCube/cube2.obj"));

	render_obj_lst.push_back(new RenderObject("Assets/WoodenCube/woodcube.obj"));

	render_obj_lst.push_back(new RenderObject("Assets/WoodenWheel/woodwheel.obj"));

	render_obj_lst.push_back(new RenderObject("Assets/Tire/tire.obj"));
	render_obj_lst.push_back(new RenderObject("Assets/WhiteCube/simplecube2.obj"));
}


Model3DFactory::~Model3DFactory()
{
}

Model3D* Model3DFactory::generateObjectWithType(int type){
	switch (type){
		case Hammer:{
			return new Model3D(render_obj_lst[type], "Assets/Hammer/tex.png", "Assets/Hammer/normals.png", "Assets/Hammer/gloss.png", "Assets/Hammer/metallic.png");
			break;
		}
		case Mace:{
			return new Model3D(render_obj_lst[type], "Assets/Mace/tex.png", "Assets/Mace/normals.png", "Assets/Mace/gloss.png", "Assets/Mace/metallic.png");
			break;
		}
		case MetalWheel:{
			return new Model3D(render_obj_lst[type], "Assets/MetalWheel/tex.png", "Assets/MetalWheel/normals.png", "Assets/MetalWheel/gloss.png", "Assets/MetalWheel/metallic.png");
			break;
		}
		case Needle:{
			return new Model3D(render_obj_lst[type], "Assets/Needle/tex.png", "Assets/Needle/normals.png", "Assets/Needle/gloss.png", "Assets/Needle/metallic.png");
			break;
		}
		case BasicCube:{
			return new Model3D(render_obj_lst[type], "Assets/BasicCube/tex.png", "Assets/BasicCube/normals.png", "Assets/BasicCube/gloss.png", "Assets/BasicCube/metallic.png");
			break;
		}
		case WoodenCube:{
			return new Model3D(render_obj_lst[type], "Assets/WoodenCube/tex.png", "Assets/WoodenCube/normals.png", "Assets/WoodenCube/gloss.png", "Assets/WoodenCube/metallic.png");
			break;
		}
		case WoodenWheel:{
			return new Model3D(render_obj_lst[type], "Assets/WoodenWheel/tex.png", "Assets/WoodenWheel/normals.png", "Assets/WoodenWheel/gloss.png", "Assets/WoodenWheel/metallic.png");
			break;
		}
		case Tire:{
			return new Model3D(render_obj_lst[type], "Assets/Tire/tex.png", "Assets/Tire/normals.png", "Assets/Tire/gloss.png", "Assets/Tire/metallic.png");
			break;
		}
		case WhiteCube:{
			return new Model3D(render_obj_lst[type], "Assets/WhiteCube/tex.png", "Assets/WhiteCube/normals.png", "Assets/WhiteCube/gloss.png", "Assets/WhiteCube/metallic.png");
			break;
		}
	}
}

