#pragma once
#include "stdafx.h"

#ifndef __Material__
#define __Material__
#include "Vector3.h"
enum Material_Type{
	Vacuum = 1,
	Air = 2,
	Glass = 3,
	Ice = 4,
	Diamond = 5,
	Water = 6,
	Ruby = 7,
	Emerald	= 8,
	Brass = 9,
	Bronze = 10,
	Polished_Bronze = 11,
	Chrome = 12,
	Copper = 13,
	Polished_Copper = 14,
	Gold = 15,
	Polished_Gold = 16,
	Pewter = 17,
	Sliver = 18,
	Polished_Silver = 19,
	Jade = 20,
	Obsidian = 21,
	Pearl = 22,
	Turquoise = 23,

};
class Materials
{
public:
	bool property_set = false;
	float index_of_refraction;
	Vector3 material_diffuse;
	Vector3 material_ambient;
	Vector3 material_specular;
	float Shininess;
	Materials();
	~Materials();
	void setIndex_Of_Refraction(int MaterialType);
	void setMaterial_Property(int MaterialType);
};
#endif

