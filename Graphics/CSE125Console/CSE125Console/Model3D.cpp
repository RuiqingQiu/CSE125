#include "stdafx.h"
#include "Window.h"

#include "SOIL.h"
#include "Model3D.h"
static int counter = 0;
Model3D::Model3D()
{
}
void Model3D::setTextureMap(string pathname){
	texture_map = pathname;
}
void Model3D::setNormalMap(string pathname){
	normal_map = pathname;
}
void Model3D::setGlossMap(string pathname){
	gloss_map = pathname;
}
void Model3D::setMetallicMap(string pathname){
	metallic_map = pathname;
}
void Model3D::setVertexShader(string pathname){
	vertex_shader = pathname;
}
void Model3D::setFragmentShader(string pathname){
	fragment_shader = pathname;
}





Model3D::Model3D(RenderObject* r){
	render_obj = r;
	isTextured = true;
	localTransform = Transform();
}


Model3D::~Model3D()
{
}

void Model3D::VOnClientUpdate(GameInfoPacket* pData){
	PlayerInfo* p = pData->get_player_info(this->identifier);
	if (p){

		localTransform.position.x = p->x;
		localTransform.position.y = p->y;
		localTransform.position.z = p->z;

		localTransform.rotation.x = p->rx;
		localTransform.rotation.y = p->ry;
		localTransform.rotation.z = p->rz;
		p->processed = true;
		this->isUpdated = true;
	}
	else{
		this->isUpdated = false;

	}
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
	counter = (counter + 1) % 360;
	//localTransform.rotation.y = counter;
	//glLoadIdentity();
	glMultMatrixd(localTransform.GetGLMatrix4().getPointer());
	
	glColor3f(1, 1, 1);
	for (size_t i = 0; i < render_obj->shapes.size(); i++) {
		
		for (size_t f = 0; f < render_obj->shapes[i].mesh.indices.size() / 3; f++) {
			int i1 = render_obj->shapes[i].mesh.indices[3 * f + 0];
			int i2 = render_obj->shapes[i].mesh.indices[3 * f + 1];
			int i3 = render_obj->shapes[i].mesh.indices[3 * f + 2];
			int m1 = render_obj->shapes[i].mesh.material_ids[f];
			
			if (isTextured){
				//material goes here
				//glMaterialfv(GL_FRONT_AND_BACK, GL_SPECULAR, whiteSpecularMaterial);
				//glMaterialfv(GL_FRONT_AND_BACK, GL_SHININESS, mShininess);
				Window::shader_system->BindShader(REGULAR_SHADER);
				glActiveTexture(GL_TEXTURE0);
				glBindTexture(GL_TEXTURE_2D, render_obj->texturaID[0]);

				glActiveTexture(GL_TEXTURE1);
				glBindTexture(GL_TEXTURE_2D, render_obj->texturaID[1]);


				glActiveTexture(GL_TEXTURE2);
				glBindTexture(GL_TEXTURE_2D, render_obj->texturaID[2]);

				glActiveTexture(GL_TEXTURE3);
				glBindTexture(GL_TEXTURE_2D, render_obj->texturaID[3]);

				glUniform1i(glGetUniformLocation(render_obj->shader_id, "tex"), 0);
				glUniform1i(glGetUniformLocation(render_obj->shader_id, "norm"), 1);
				glUniform1i(glGetUniformLocation(render_obj->shader_id, "gloss"), 2);
				glUniform1i(glGetUniformLocation(render_obj->shader_id, "metallic"), 3);

				float value[4] = { float(render_obj->shapes[i].mesh.tangent[f].x),
					float(render_obj->shapes[i].mesh.tangent[f].y),
					float(render_obj->shapes[i].mesh.tangent[f].z),
					float(render_obj->shapes[i].mesh.tangent[f].w) };
				glUniform4fv(glGetUniformLocationARB(render_obj->shader_id, "VertexTangent"), 1, value);
				

				GLint l_x = glGetUniformLocation(render_obj->shader_id, "light_x");
				GLint l_y = glGetUniformLocation(render_obj->shader_id, "light_y");
				GLint l_z = glGetUniformLocation(render_obj->shader_id, "light_z");
				glUniform1f(l_x, g_pCore->light->localTransform.position.x);
				glUniform1f(l_y, g_pCore->light->localTransform.position.y);
				glUniform1f(l_z, g_pCore->light->localTransform.position.z);
				// Make sure no bytes are padded:
				glPixelStorei(GL_UNPACK_ALIGNMENT, 1);

				// Select GL_MODULATE to mix texture with polygon color for shading:
				glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_MODULATE);

				// Use bilinear interpolation:
				glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
				glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
				//glEnable(GL_TEXTURE_2D);
				
				//glMaterialfv(GL_FRONT, GL_AMBIENT, materials[m1].ambient);
				//glMaterialfv(GL_FRONT, GL_DIFFUSE, materials[m1].diffuse);
				//glMaterialfv(GL_FRONT, GL_SPECULAR, materials[m1].specular);
				//glMaterialfv(GL_FRONT, GL_SHININESS, &materials[m1].shininess);
			}
			//!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
			//THIS LINE OF CODE MUST BE AFTER THE TEXTURE LOADING CODE
			//!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
			glBegin(GL_TRIANGLES);
			//!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
			//DONT MODIFY IF YOU DONT KNOW WHAT IT IS
			//!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
			if (isTextured){
				//texture
				glTexCoord2f(render_obj->shapes[i].mesh.texcoords[2 * i1 + 0], render_obj->shapes[i].mesh.texcoords[2 * i1 + 1]);
			}
			//avg normal goes here
			glNormal3f(render_obj->shapes[i].mesh.normals[3 * i1 + 0],
				render_obj->shapes[i].mesh.normals[3 * i1 + 1],
				render_obj->shapes[i].mesh.normals[3 * i1 + 2]
					  );
			glVertex3f(render_obj->shapes[i].mesh.positions[3 * i1 + 0], render_obj->shapes[i].mesh.positions[3 * i1 + 1], render_obj->shapes[i].mesh.positions[3 * i1 + 2]);

			if (isTextured){
				//texture
				glTexCoord2f(render_obj->shapes[i].mesh.texcoords[2 * i2 + 0], render_obj->shapes[i].mesh.texcoords[2 * i2 + 1]);
			}
			//avg normal goes here

			glNormal3f(render_obj->shapes[i].mesh.normals[3 * i2 + 0],
				render_obj->shapes[i].mesh.normals[3 * i2 + 1],
				render_obj->shapes[i].mesh.normals[3 * i2 + 2]
				);
			glVertex3f(render_obj->shapes[i].mesh.positions[3 * i2 + 0], render_obj->shapes[i].mesh.positions[3 * i2 + 1], render_obj->shapes[i].mesh.positions[3 * i2 + 2]);

			if (isTextured){
				//texture
				glTexCoord2f(render_obj->shapes[i].mesh.texcoords[2 * i3 + 0], render_obj->shapes[i].mesh.texcoords[2 * i3 + 1]);
			}
			//avg normal goes here
			glNormal3f(render_obj->shapes[i].mesh.normals[3 * i3 + 0],
				render_obj->shapes[i].mesh.normals[3 * i3 + 1],
				render_obj->shapes[i].mesh.normals[3 * i3 + 2]
				);
			glVertex3f(render_obj->shapes[i].mesh.positions[3 * i3 + 0], render_obj->shapes[i].mesh.positions[3 * i3 + 1], render_obj->shapes[i].mesh.positions[3 * i3 + 2]);

			glEnd();

			if (isTextured){
				glBindTexture(GL_TEXTURE_2D, 0);
				glDisable(GL_TEXTURE_2D);
			}




		}

	}
	
	Window::shader_system->UnbindShader();

	glActiveTexture(GL_TEXTURE0);
	glPopMatrix();

	
}
void Model3D::VOnUpdate(GameInfoPacket* pData){
	
}