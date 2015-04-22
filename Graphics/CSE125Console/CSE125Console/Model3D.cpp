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



GLhandleARB loadShader1(char* filename, unsigned int type)
{
	FILE *pfile;
	GLhandleARB handle;
	const GLcharARB* files[1];

	// shader Compilation variable
	GLint result;				// Compilation code result
	GLint errorLoglength;
	char* errorLogText;
	GLsizei actualErrorLogLength;

	char buffer[400000];
	memset(buffer, 0, 400000);

	// This will raise a warning on MS compiler
	pfile = fopen(filename, "rb");
	if (!pfile)
	{
		printf("Sorry, can't open file: '%s'.\n", filename);
		exit(0);
	}

	fread(buffer, sizeof(char), 400000, pfile);
	//printf("%s\n",buffer);


	fclose(pfile);

	handle = glCreateShaderObjectARB(type);
	if (!handle)
	{
		//We have failed creating the vertex shader object.
		printf("Failed creating vertex shader object from file: %s.", filename);
		exit(0);
	}

	files[0] = (const GLcharARB*)buffer;
	glShaderSourceARB(
		handle, //The handle to our shader
		1, //The number of files.
		files, //An array of const char * data, which represents the source code of theshaders
		NULL);

	glCompileShaderARB(handle);

	//Compilation checking.
	glGetObjectParameterivARB(handle, GL_OBJECT_COMPILE_STATUS_ARB, &result);

	// If an error was detected.
	if (!result)
	{
		//We failed to compile.
		printf("Shader '%s' failed compilation.\n", filename);

		//Attempt to get the length of our error log.
		glGetObjectParameterivARB(handle, GL_OBJECT_INFO_LOG_LENGTH_ARB, &errorLoglength);

		//Create a buffer to read compilation error message
		errorLogText = (char*)malloc(sizeof(char)* errorLoglength);

		//Used to get the final length of the log.
		glGetInfoLogARB(handle, errorLoglength, &actualErrorLogLength, errorLogText);

		// Display errors.
		printf("%s\n", errorLogText);

		// Free the buffer malloced earlier
		free(errorLogText);
	}
	printf("Shader loaded done\n");
	return handle;
}


Model3D::Model3D(RenderObject* r, string texture, string normal, string gloss,
			string metal){
	render_obj = r;
	setTextureMap(texture);
	setNormalMap(normal);
	setGlossMap(gloss);
	setMetallicMap(metal);
	
	setVertexShader("shadow.vert");
	setFragmentShader("shadow.frag");
	localTransform = Transform();

	GLhandleARB vertexShaderHandle;
	GLhandleARB fragmentShaderHandle;
	char *v_str = new char[vertex_shader.length() + 1];
	strcpy(v_str, vertex_shader.c_str());
	char *f_str = new char[fragment_shader.length() + 1];
	strcpy(f_str, fragment_shader.c_str());
	vertexShaderHandle = loadShader1(v_str, GL_VERTEX_SHADER);
	fragmentShaderHandle = loadShader1(f_str, GL_FRAGMENT_SHADER);

	shader_id = glCreateProgramObjectARB();

	glAttachObjectARB(shader_id, vertexShaderHandle);
	glAttachObjectARB(shader_id, fragmentShaderHandle);
	glLinkProgramARB(shader_id);

	//glUseProgramObjectARB(shader_id);


	glGenTextures(3, texturaID);
	int width, height;
	//unsigned char* image;

	glBindTexture(GL_TEXTURE_2D, texturaID[0]);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
	texturaID[0] = SOIL_load_OGL_texture(texture_map.c_str(), SOIL_LOAD_AUTO,
		SOIL_CREATE_NEW_ID,
		SOIL_FLAG_INVERT_Y);
	if (texturaID[0] == 0)
	{
		cout << "error" << endl;
	}
	else{
		cout << texturaID[0] << endl;
		isTextured = true;
	}
	//glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, image);
	//SOIL_free_image_data(image);


	glBindTexture(GL_TEXTURE_2D, texturaID[1]);
	texturaID[1] = SOIL_load_OGL_texture(normal_map.c_str() , SOIL_LOAD_AUTO,
		SOIL_CREATE_NEW_ID,
		SOIL_FLAG_INVERT_Y);
	//glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, image);
	//SOIL_free_image_data(image);
	if (texturaID[1] == 0)
	{
		cout << "error 1" << endl;
	}

	glBindTexture(GL_TEXTURE_2D, texturaID[2]);
	texturaID[2] = SOIL_load_OGL_texture(gloss_map.c_str(), SOIL_LOAD_AUTO,
		SOIL_CREATE_NEW_ID,
		SOIL_FLAG_INVERT_Y);
	//glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, image);
	//SOIL_free_image_data(image);
	if (texturaID[2] == 0)
	{
		cout << "error 2" << endl;
	}

	glBindTexture(GL_TEXTURE_2D, texturaID[3]);
	texturaID[3] = SOIL_load_OGL_texture(metallic_map.c_str(), SOIL_LOAD_AUTO,
		SOIL_CREATE_NEW_ID,
		SOIL_FLAG_INVERT_Y);
	//glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, image);
	//SOIL_free_image_data(image);
	if (texturaID[3] == 0)
	{
		cout << "error 3" << endl;
	}


	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, texturaID[0]);

	glActiveTexture(GL_TEXTURE1);
	glBindTexture(GL_TEXTURE_2D, texturaID[1]);

	glActiveTexture(GL_TEXTURE2);
	glBindTexture(GL_TEXTURE_2D, texturaID[2]);

	glActiveTexture(GL_TEXTURE3);
	glBindTexture(GL_TEXTURE_2D, texturaID[3]);

	glUniform1i(glGetUniformLocation(shader_id, "tex"), 0);
	glUniform1i(glGetUniformLocation(shader_id, "norm"), 1);
	glUniform1i(glGetUniformLocation(shader_id, "gloss"), 2);
	glUniform1i(glGetUniformLocation(shader_id, "metallic"), 3);
	glUniform1i(glGetUniformLocation(shader_id, "light_position"), 4);	

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
	counter = (counter + 1) % 360;
	localTransform.rotation.y = counter;
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
				glUseProgramObjectARB(shader_id);
				glActiveTexture(GL_TEXTURE0);
				glBindTexture(GL_TEXTURE_2D, texturaID[0]);

				glActiveTexture(GL_TEXTURE1);
				glBindTexture(GL_TEXTURE_2D, texturaID[1]);


				glActiveTexture(GL_TEXTURE2);
				glBindTexture(GL_TEXTURE_2D, texturaID[2]);

				glActiveTexture(GL_TEXTURE3);
				glBindTexture(GL_TEXTURE_2D, texturaID[3]);

				glUniform1i(glGetUniformLocation(shader_id, "tex"), 0);
				glUniform1i(glGetUniformLocation(shader_id, "norm"), 1);
				glUniform1i(glGetUniformLocation(shader_id, "gloss"), 2);
				glUniform1i(glGetUniformLocation(shader_id, "metallic"), 3);

				GLint l_x = glGetUniformLocation(shader_id, "light_x");
				GLint l_y = glGetUniformLocation(shader_id, "light_y");
				GLint l_z = glGetUniformLocation(shader_id, "light_z");
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
	
	glUseProgramObjectARB(0);

	glActiveTexture(GL_TEXTURE0);
	glPopMatrix();

	
}
void Model3D::VOnUpdate(GameInfoPacket* pData){

}