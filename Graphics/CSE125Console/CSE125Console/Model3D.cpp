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
	//If it's a static object, we don't want it to disappear
	if (this->static_object == true){
		this->isUpdated = true;
		return;
	}
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
		//material goes here
		//glMaterialfv(GL_FRONT_AND_BACK, GL_SPECULAR, whiteSpecularMaterial);
		//glMaterialfv(GL_FRONT_AND_BACK, GL_SHININESS, mShininess);
		GLuint vt = glGetAttribLocationARB(Window::shader_system->shader_ids[shader_type], "VertexTangent");
		if (false && this->type == BATTLEFIELD){
			printf("battle field\n");
		}
		else if (this->edge_highlight || this->blur){}
		else{
			Window::shader_system->BindShader(shader_type);

			//Passing modelMatrix
			glUniformMatrix4fv(glGetUniformLocation(Window::shader_system->shader_ids[shader_type], "ModelView"), 1, true,
				localTransform.GetGLMatrix4().getFloatPointer());

			//Passing four maps
			glActiveTexture(GL_TEXTURE1);
			glBindTexture(GL_TEXTURE_2D, render_obj->texturaID[0]);

			glActiveTexture(GL_TEXTURE2);
			glBindTexture(GL_TEXTURE_2D, render_obj->texturaID[1]);


			glActiveTexture(GL_TEXTURE3);
			glBindTexture(GL_TEXTURE_2D, render_obj->texturaID[2]);

			glActiveTexture(GL_TEXTURE4);
			glBindTexture(GL_TEXTURE_2D, render_obj->texturaID[3]);

			glUniform1i(glGetUniformLocation(Window::shader_system->shader_ids[shader_type], "tex"), 1);
			glUniform1i(glGetUniformLocation(Window::shader_system->shader_ids[shader_type], "norm"), 2);
			glUniform1i(glGetUniformLocation(Window::shader_system->shader_ids[shader_type], "gloss"), 3);
			glUniform1i(glGetUniformLocation(Window::shader_system->shader_ids[shader_type], "metallic"), 4);

		
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
		for (size_t i = 0; i < render_obj->shapes.size(); i++) {

			for (size_t f = 0; f < render_obj->shapes[i].mesh.indices.size() / 3; f++) {
				int i1 = render_obj->shapes[i].mesh.indices[3 * f + 0];
				int i2 = render_obj->shapes[i].mesh.indices[3 * f + 1];
				int i3 = render_obj->shapes[i].mesh.indices[3 * f + 2];
				int m1 = render_obj->shapes[i].mesh.material_ids[f];
			
				//!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
				//THIS LINE OF CODE MUST BE AFTER THE TEXTURE LOADING CODE
				//!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
				glBegin(GL_TRIANGLES);
				//!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
				//DONT MODIFY IF YOU DONT KNOW WHAT IT IS
				//!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
				glTexCoord2f(render_obj->shapes[i].mesh.texcoords[2 * i1 + 0], render_obj->shapes[i].mesh.texcoords[2 * i1 + 1]);
				//avg normal goes here
				glNormal3f(render_obj->shapes[i].mesh.normals[3 * i1 + 0],
					render_obj->shapes[i].mesh.normals[3 * i1 + 1],
					render_obj->shapes[i].mesh.normals[3 * i1 + 2]
					);

				float value[4] = { float(render_obj->shapes[i].mesh.tangent[f].x),
					float(render_obj->shapes[i].mesh.tangent[f].y),
					float(render_obj->shapes[i].mesh.tangent[f].z),
					float(render_obj->shapes[i].mesh.tangent[f].w) };
				glVertexAttrib3fvARB(vt, value);
				glVertex3f(render_obj->shapes[i].mesh.positions[3 * i1 + 0], render_obj->shapes[i].mesh.positions[3 * i1 + 1], render_obj->shapes[i].mesh.positions[3 * i1 + 2]);

				//texture
				glTexCoord2f(render_obj->shapes[i].mesh.texcoords[2 * i2 + 0], render_obj->shapes[i].mesh.texcoords[2 * i2 + 1]);
				//avg normal goes here

				glNormal3f(render_obj->shapes[i].mesh.normals[3 * i2 + 0],
					render_obj->shapes[i].mesh.normals[3 * i2 + 1],
					render_obj->shapes[i].mesh.normals[3 * i2 + 2]
					);
				float value1[4] = { float(render_obj->shapes[i].mesh.tangent[i2].x),
					float(render_obj->shapes[i].mesh.tangent[i2].y),
					float(render_obj->shapes[i].mesh.tangent[i2].z),
					float(render_obj->shapes[i].mesh.tangent[i2].w) };
				glVertexAttrib3fvARB(vt, value1);
				glVertex3f(render_obj->shapes[i].mesh.positions[3 * i2 + 0], render_obj->shapes[i].mesh.positions[3 * i2 + 1], render_obj->shapes[i].mesh.positions[3 * i2 + 2]);

				
				glTexCoord2f(render_obj->shapes[i].mesh.texcoords[2 * i3 + 0], render_obj->shapes[i].mesh.texcoords[2 * i3 + 1]);
				//avg normal goes here
				glNormal3f(render_obj->shapes[i].mesh.normals[3 * i3 + 0],
					render_obj->shapes[i].mesh.normals[3 * i3 + 1],
					render_obj->shapes[i].mesh.normals[3 * i3 + 2]
					);
				float value2[4] = { float(render_obj->shapes[i].mesh.tangent[i3].x),
					float(render_obj->shapes[i].mesh.tangent[i3].y),
					float(render_obj->shapes[i].mesh.tangent[i3].z),
					float(render_obj->shapes[i].mesh.tangent[i3].w) };
				glVertexAttrib3fvARB(vt, value2);
				glVertex3f(render_obj->shapes[i].mesh.positions[3 * i3 + 0], render_obj->shapes[i].mesh.positions[3 * i3 + 1], render_obj->shapes[i].mesh.positions[3 * i3 + 2]);

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