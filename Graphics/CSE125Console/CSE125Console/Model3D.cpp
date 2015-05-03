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


Model3D::Model3D(RenderObject* r){
	render_obj = r;
	isTextured = true;
	localTransform = Transform();
	shader_type = REGULAR_SHADER;
}

void Model3D::setShaderType(int type){
	shader_type = type;
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
	if (auto_rotate){
		counter = (counter + 1) % 360;
		localTransform.rotation.y = counter;
	}

	if (two_pass_draw){

	}
	else{
		//glLoadIdentity();
		glMultMatrixd(localTransform.GetGLMatrix4().getPointer());

		glColor3f(1, 1, 1);
		Window::shader_system->BindShader(shader_type);
		glUniformMatrix4fv(glGetUniformLocation(Window::shader_system->shader_ids[shader_type], "ModelView"), 1, true,
			localTransform.GetGLMatrix4().getFloatPointer());

		//Passing four maps
		glActiveTexture(GL_TEXTURE0);
		glBindTexture(GL_TEXTURE_2D, render_obj->texturaID[0]);

		glActiveTexture(GL_TEXTURE1);
		glBindTexture(GL_TEXTURE_2D, render_obj->texturaID[1]);


		glActiveTexture(GL_TEXTURE2);
		glBindTexture(GL_TEXTURE_2D, render_obj->texturaID[2]);

		glActiveTexture(GL_TEXTURE3);
		glBindTexture(GL_TEXTURE_2D, render_obj->texturaID[3]);

		glUniform1i(glGetUniformLocation(Window::shader_system->shader_ids[shader_type], "tex"), 0);
		glUniform1i(glGetUniformLocation(Window::shader_system->shader_ids[shader_type], "norm"), 1);
		glUniform1i(glGetUniformLocation(Window::shader_system->shader_ids[shader_type], "gloss"), 2);
		glUniform1i(glGetUniformLocation(Window::shader_system->shader_ids[shader_type], "metallic"), 3);
		// Make sure no bytes are padded:
		glPixelStorei(GL_UNPACK_ALIGNMENT, 1);

		// Select GL_MODULATE to mix texture with polygon color for shading:
		glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_MODULATE);

		// Use bilinear interpolation:
		glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
		glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

		for (size_t i = 0; i < render_obj->shapes.size(); i++) {

			for (size_t f = 0; f < render_obj->shapes[i].mesh.indices.size() / 3; f++) {
				int i1 = render_obj->shapes[i].mesh.indices[3 * f + 0];
				int i2 = render_obj->shapes[i].mesh.indices[3 * f + 1];
				int i3 = render_obj->shapes[i].mesh.indices[3 * f + 2];
				int m1 = render_obj->shapes[i].mesh.material_ids[f];

				//THIS LINE OF CODE MUST BE AFTER THE TEXTURE LOADING CODE
				//!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
				glBegin(GL_TRIANGLES);
				//!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
				//DONT MODIFY IF YOU DONT KNOW WHAT IT IS
				//!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
				float * tmp;
				tmp = &render_obj->shapes[i].mesh.texcoords[2 * i1 + 0];
				glTexCoord2f(*tmp, *(tmp + 1));
				//avg normal goes here
				tmp = &render_obj->shapes[i].mesh.normals[3 * i1 + 0];
				glNormal3f(*tmp, *(tmp+1), *(tmp+2));

				tmp = &render_obj->shapes[i].mesh.positions[3 * i1 + 0];
				glVertex3f(*tmp, *(tmp + 1), *(tmp + 2));

				tmp = &render_obj->shapes[i].mesh.texcoords[2 * i2 + 0];
				glTexCoord2f(*tmp, *(tmp + 1));
				//avg normal goes here
				tmp = &render_obj->shapes[i].mesh.normals[3 * i2 + 0];
				glNormal3f(*tmp, *(tmp + 1), *(tmp + 2));
				tmp = &render_obj->shapes[i].mesh.positions[3 * i2 + 0];
				glVertex3f(*tmp, *(tmp + 1), *(tmp + 2));

				tmp = &render_obj->shapes[i].mesh.texcoords[2 * i3 + 0];
				glTexCoord2f(*tmp, *(tmp + 1));
				//avg normal goes here
				tmp = &render_obj->shapes[i].mesh.normals[3 * i3 + 0];
				glNormal3f(*tmp, *(tmp + 1), *(tmp + 2));

				tmp = &render_obj->shapes[i].mesh.positions[3 * i3 + 0];
				glVertex3f(*tmp, *(tmp + 1), *(tmp + 2));

				glEnd();
			}
		}

	}
	Window::shader_system->UnbindShader();

	glActiveTexture(GL_TEXTURE0);
	glPopMatrix();

	
}
void Model3D::VOnUpdate(GameInfoPacket* pData){
	
}