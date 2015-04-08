#include "stdafx.h"
#include "SOIL.h"
#include "Model3D.h"


Model3D::Model3D()
{

}
Model3D::Model3D(string filename){

	localTransform = Transform();

	std::string inputfile = filename;

	std::string err = tinyobj::LoadObj(shapes, materials, inputfile.c_str(), NULL);

	if (!err.empty()) {
		std::cerr << err << std::endl;
		exit(1);
	}

	std::cout << "# of shapes    : " << shapes.size() << std::endl;
	std::cout << "# of materials : " << materials.size() << std::endl;

	for (size_t i = 0; i < shapes.size(); i++) {
		printf("shape[%ld].name = %s\n", i, shapes[i].name.c_str());
		printf("Size of shape[%ld].indices: %ld\n", i, shapes[i].mesh.indices.size());
		printf("Size of shape[%ld].material_ids: %ld\n", i, shapes[i].mesh.material_ids.size());
		for (size_t f = 0; f < shapes[i].mesh.indices.size() / 3; f++) {
			printf("  idx[%ld] = %d, %d, %d. mat_id = %d\n", f, shapes[i].mesh.indices[3 * f + 0], shapes[i].mesh.indices[3 * f + 1], shapes[i].mesh.indices[3 * f + 2], shapes[i].mesh.material_ids[f]);
		}

		printf("shape[%ld].vertices: %ld\n", i, shapes[i].mesh.positions.size());
		for (size_t v = 0; v < shapes[i].mesh.positions.size() / 3; v++) {
			printf("  v[%ld] = (%f, %f, %f)\n", v,
				shapes[i].mesh.positions[3 * v + 0],
				shapes[i].mesh.positions[3 * v + 1],
				shapes[i].mesh.positions[3 * v + 2]);
		}
	}

	for (size_t i = 0; i < materials.size(); i++) {
		printf("material[%ld].name = %s\n", i, materials[i].name.c_str());
		printf("  material.Ka = (%f, %f ,%f)\n", materials[i].ambient[0], materials[i].ambient[1], materials[i].ambient[2]);
		printf("  material.Kd = (%f, %f ,%f)\n", materials[i].diffuse[0], materials[i].diffuse[1], materials[i].diffuse[2]);
		printf("  material.Ks = (%f, %f ,%f)\n", materials[i].specular[0], materials[i].specular[1], materials[i].specular[2]);
		printf("  material.Tr = (%f, %f ,%f)\n", materials[i].transmittance[0], materials[i].transmittance[1], materials[i].transmittance[2]);
		printf("  material.Ke = (%f, %f ,%f)\n", materials[i].emission[0], materials[i].emission[1], materials[i].emission[2]);
		printf("  material.Ns = %f\n", materials[i].shininess);
		printf("  material.Ni = %f\n", materials[i].ior);
		printf("  material.dissolve = %f\n", materials[i].dissolve);
		printf("  material.illum = %d\n", materials[i].illum);
		printf("  material.map_Ka = %s\n", materials[i].ambient_texname.c_str());
		printf("  material.map_Kd = %s\n", materials[i].diffuse_texname.c_str());
		printf("  material.map_Ks = %s\n", materials[i].specular_texname.c_str());
		printf("  material.map_Ns = %s\n", materials[i].normal_texname.c_str());
		std::map<std::string, std::string>::const_iterator it(materials[i].unknown_parameter.begin());
		std::map<std::string, std::string>::const_iterator itEnd(materials[i].unknown_parameter.end());
		for (; it != itEnd; it++) {
			printf("  material.%s = %s\n", it->first.c_str(), it->second.c_str());
		}
		printf("\n");


		if (materials[i].diffuse_texname.c_str())
		{
			GLuint tex_2d = SOIL_load_OGL_texture
				(
				//strcat(pre,name),
				//"Texture/mygod.tga",
			    materials[i].diffuse_texname.c_str(),
				SOIL_LOAD_AUTO,
				SOIL_CREATE_NEW_ID,
				SOIL_FLAG_INVERT_Y
				);

			/* check for an error during the load process */
			if (0 == tex_2d)
			{
				printf("SOIL loading error: '%s'\n", SOIL_last_result());
			}
			else{
				printf("SOIL loading success %i\n", tex_2d);
			}
		}
	}
}


Model3D::~Model3D()
{
}

void Model3D::VOnClientUpdate(GameInfoPacket* pData){

}
/*
typedef struct {
std::vector<float> positions;
std::vector<float> normals;
std::vector<float> texcoords;
std::vector<unsigned int> indices;
std::vector<int> material_ids; // per-mesh material ID
} mesh_t;

typedef struct {
std::string name;
mesh_t mesh;
} shape_t;

typedef struct {
std::string name;

float ambient[3];
float diffuse[3];
float specular[3];
float transmittance[3];
float emission[3];
float shininess;
float ior;      // index of refraction
float dissolve; // 1 == opaque; 0 == fully transparent
// illumination model (see http://www.fileformat.info/format/material/)
int illum;

std::string ambient_texname;
std::string diffuse_texname;
std::string specular_texname;
std::string normal_texname;
std::map<std::string, std::string> unknown_parameter;
} material_t;

*/
void Model3D::VOnDraw(){
	//Set the OpenGL Matrix mode to ModelView (used when drawing geometry)
	glMatrixMode(GL_MODELVIEW);
	glPushMatrix();
	glMultMatrixd(localTransform.GetGLMatrix4().getPointer());
	glColor3f(1, 1, 1);
	for (size_t i = 0; i < shapes.size(); i++) {
		
		for (size_t f = 0; f < shapes[i].mesh.indices.size() / 3; f++) {
			int i1 = shapes[i].mesh.indices[3 * f + 0];
			int i2 = shapes[i].mesh.indices[3 * f + 1];
			int i3 = shapes[i].mesh.indices[3 * f + 2];
			int m1 = shapes[i].mesh.material_ids[f];
			
			//material goes here
			//glMaterialfv(GL_FRONT_AND_BACK, GL_SPECULAR, whiteSpecularMaterial);
			//glMaterialfv(GL_FRONT_AND_BACK, GL_SHININESS, mShininess);
			glBindTexture(GL_TEXTURE_2D, m1+1);
			// Make sure no bytes are padded:
			glPixelStorei(GL_UNPACK_ALIGNMENT, 1);

			// Select GL_MODULATE to mix texture with polygon color for shading:
			glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_MODULATE);

			// Use bilinear interpolation:
			glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
			glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
			glEnable(GL_TEXTURE_2D);

			glMaterialfv(GL_FRONT, GL_AMBIENT, materials[m1].ambient);
			glMaterialfv(GL_FRONT, GL_DIFFUSE, materials[m1].diffuse);
			glMaterialfv(GL_FRONT, GL_SPECULAR, materials[m1].specular);
			glMaterialfv(GL_FRONT, GL_SHININESS, &materials[m1].shininess);

			//!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
			//THIS LINE OF CODE MUST BE AFTER THE TEXTURE LOADING CODE
			//!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
			glBegin(GL_TRIANGLES);
			//!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
			//DONT MODIFY IF YOU DONT KNOW WHAT IT IS
			//!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!

			//texture
			glTexCoord2f(shapes[i].mesh.texcoords[2 * i1 + 0], shapes[i].mesh.texcoords[2 * i1 + 1]);
			
			//avg normal goes here
			glNormal3f(shapes[i].mesh.normals[3 * i1 + 0],
				       shapes[i].mesh.normals[3 * i1 + 1],
					   shapes[i].mesh.normals[3 * i1 + 2]
					  );
			glVertex3f(shapes[i].mesh.positions[3 * i1 + 0], shapes[i].mesh.positions[3 * i1 + 1], shapes[i].mesh.positions[3 * i1 + 2]);

			//texture
			glTexCoord2f(shapes[i].mesh.texcoords[2 * i2 + 0], shapes[i].mesh.texcoords[2 * i2 + 1]);
			//avg normal goes here
			glNormal3f(shapes[i].mesh.normals[3 * i2 + 0],
				shapes[i].mesh.normals[3 * i2 + 1],
				shapes[i].mesh.normals[3 * i2 + 2]
				);
			glVertex3f(shapes[i].mesh.positions[3 * i2 + 0], shapes[i].mesh.positions[3 * i2 + 1], shapes[i].mesh.positions[3 * i2 + 2]);

			//texture
			glTexCoord2f(shapes[i].mesh.texcoords[2 * i3 + 0], shapes[i].mesh.texcoords[2 * i3 + 1]);
			//avg normal goes here
			glNormal3f(shapes[i].mesh.normals[3 * i3 + 0],
				shapes[i].mesh.normals[3 * i3 + 1],
				shapes[i].mesh.normals[3 * i3 + 2]
				);
			glVertex3f(shapes[i].mesh.positions[3 * i3 + 0], shapes[i].mesh.positions[3 * i3 + 1], shapes[i].mesh.positions[3 * i3 + 2]);

			glEnd();

			glBindTexture(GL_TEXTURE_2D, 0);
			glDisable(GL_TEXTURE_2D);

		}

	}

	glPopMatrix();
}
void Model3D::VOnUpdate(GameInfoPacket* pData){

}