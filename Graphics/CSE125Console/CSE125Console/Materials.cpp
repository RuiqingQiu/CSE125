#include "stdafx.h"
#include "Materials.h"


Materials::Materials()
{
}


Materials::~Materials()
{
}

void Materials::setIndex_Of_Refraction(int MaterialType){
	switch (MaterialType){
	case Vacuum:
		index_of_refraction = 1;
		break;
	case Air:
		index_of_refraction = 1;
		break;
	case Glass:
		index_of_refraction = 1.5;
		break;
	case Ice:
		index_of_refraction = 1.3;
		break;
	case Diamond:
		index_of_refraction = 2.42;
		break;
	case Water:
		index_of_refraction = 1.33;
		break;
	case Ruby:
		index_of_refraction = 1.77;
		break;
	case Emerald:
		index_of_refraction = 1.57;
		break;
	}
	
}



void Materials::setMaterial_Property(int MaterialType){

	switch (MaterialType){
		case Brass:
			material_ambient = Vector3(0.329412, 0.223529, 0.027451);
			material_diffuse = Vector3(0.780392, 0.568627, 0.113725);
			material_specular = Vector3(0.992157, 0.941176,0.807843);
			Shininess = 27.8974;
			property_set = true;
			break;
		case Bronze:
			material_ambient = Vector3(0.2125,0.1275,0.054);
			material_diffuse = Vector3(0.714,0.4284,0.18144);
			material_specular = Vector3(0.393548,0.271906,0.166721);
			Shininess = 25.6;
			property_set = true;

			break;
		case Polished_Bronze:
			material_ambient = Vector3(0.25, 0.148, 0.06475);
			material_diffuse = Vector3(0.4, 0.2368, 0.1036);
			material_specular = Vector3(0.774597, 0.458561, 0.200621);
			Shininess = 76.8;
			property_set = true;

			break;
		case Chrome:
			material_ambient = Vector3(0.25, 0.25, 0.25);
			material_diffuse = Vector3(0.4, 0.4, 0.4);
			material_specular = Vector3(0.774597, 0.774597, 0.774597);
			Shininess = 76.8;
			property_set = true;

			break;
		case Copper:
			material_ambient = Vector3(0.19125, 0.0735, 0.0225);
			material_diffuse = Vector3(0.7038, 0.27048, 0.0828);
			material_specular = Vector3(0.256777, 0.137622, 0.086014);
			Shininess = 12.8;
			property_set = true;

			break;
		case Polished_Copper:
			material_ambient = Vector3(0.2295, 0.08825, 0.0275);
			material_diffuse = Vector3(0.5508, 0.2118, 0.066);
			material_specular = Vector3(0.580594, 0.223257, 0.0695701);
			Shininess = 51.2;
			property_set = true;

			break;
		case Gold:
			material_ambient = Vector3(0.24725, 0.1995, 0.0745);
			material_diffuse = Vector3(0.75164, 0.60648, 0.22648);
			material_specular = Vector3(0.628281, 0.555802, 0.366065);
			Shininess = 51.2;
			property_set = true;

			break;
		case Polished_Gold:
			material_ambient = Vector3(0.24725, 0.2245, 0.0645);
			material_diffuse = Vector3(0.34615, 0.3143, 0.0903);
			material_specular = Vector3(0.797357, 0.723991, 0.208006);
			Shininess = 83.2;
			property_set = true;

			break;
		case Pewter:
			material_ambient = Vector3(0.105882, 0.058824, 0.113725);
			material_diffuse = Vector3(0.427451, 0.470588, 0.541176);
			material_specular = Vector3(0.333333, 0.333333, 0.521569);
			Shininess = 9.84615;
			property_set = true;

			break;
		case Sliver:
			material_ambient = Vector3(0.19225, 0.19225, 0.19225);
			material_diffuse = Vector3(0.50754, 0.50754, 0.50754);
			material_specular = Vector3(0.508273, 0.508273, 0.508273);
			Shininess = 51.2;
			property_set = true;

			break;
		case Polished_Silver:
			material_ambient = Vector3(0.23125, 0.23125, 0.23125);
			material_diffuse = Vector3(0.2775, 0.2775, 0.2775);
			material_specular = Vector3(0.773911, 0.773911, 0.773911);
			Shininess = 89.6;
			property_set = true;

			break;
		case Emerald:
			material_ambient = Vector3(0.0215, 0.1745, 0.0215);
			material_diffuse = Vector3(0.07568, 0.61424, 0.07568);
			material_specular = Vector3(0.633, 0.727811, 0.633);
			Shininess = 76.8;
			property_set = true;

			break;
		case Jade:
			material_ambient = Vector3(0.135, 0.2225, 0.1575);
			material_diffuse = Vector3(0.54, 0.89, 0.63);
			material_specular = Vector3(0.316228, 0.316228, 0.316228);
			Shininess = 12.8;
			property_set = true;

			break;
		case Obsidian:
			material_ambient = Vector3(0.05375, 0.05, 0.06625);
			material_diffuse = Vector3(0.18275, 0.17, 0.22525);
			material_specular = Vector3(0.332741, 0.328634, 0.346435);
			Shininess = 38.4;
			property_set = true;

			break;
		case Pearl:
			material_ambient = Vector3(0.25, 0.20725, 0.20725);
			material_diffuse = Vector3(1, 0.829, 0.829);
			material_specular = Vector3(0.296648, 0.296648, 0.296648);
			Shininess = 11.264;
			property_set = true;

			break;
		case Ruby:
			material_ambient = Vector3(0.1745, 0.01175, 0.01175);
			material_diffuse = Vector3(0.61424, 0.04136, 0.04136);
			material_specular = Vector3(0.727811, 0.626959, 0.626959);
			Shininess = 76.8;
			property_set = true;

			break;
		case Turquoise:
			material_ambient = Vector3(0.1, 0.18725, 0.1745);
			material_diffuse = Vector3(0.396, 0.74151, 0.6910);
			material_specular = Vector3(0.297254, 0.30829, 0.306678);
			Shininess = 12.8;
			property_set = true;

			break;
		case Common:
			material_ambient = Vector3(0.0, 0.0, 0.0);
			material_diffuse = Vector3(0.64, 0.64, 0.64);
			material_specular = Vector3(0.4, 0.4, 0.4);
			Shininess = 8;
			property_set = true;
			break;
		default:
			cout << "material property default" << endl;
			property_set = false;
			break;
	}

}

