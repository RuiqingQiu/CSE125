#include "stdafx.h"
#include "SOIL.h"
#include "Model3D.h"


Model3D::Model3D()
{

}
Model3D::Model3D(string filename, string matname, string rough, string metal, string normal){

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
		
		/*
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

			if (0 == tex_2d)
			{
				printf("SOIL loading error: '%s'\n", SOIL_last_result());
				isTextured = false;
			}
			else{
				printf("SOIL loading success %i\n", tex_2d);
				isTextured = true;
			}
		}*/
		printf("load texture\n");

		if (true)
		{
			GLuint tex_2d = SOIL_load_OGL_texture
				(
				//strcat(pre,name),
				//"Texture/mygod.tga",
				matname.c_str(),
				SOIL_LOAD_AUTO,
				SOIL_CREATE_NEW_ID,
				SOIL_FLAG_INVERT_Y
				);

			/* check for an error during the load process */
			if (0 == tex_2d)
			{
				printf("SOIL loading error: '%s'\n", SOIL_last_result());
				isTextured = false;
			}
			else{
				printf("SOIL loading success material %i\n", tex_2d);
				isTextured = true;
				textureId = tex_2d;
			}
		}

		if (true)
		{
			GLuint tex_2d = SOIL_load_OGL_texture
				(
				//strcat(pre,name),
				//"Texture/mygod.tga",
				normal.c_str(),
				SOIL_LOAD_AUTO,
				SOIL_CREATE_NEW_ID,
				SOIL_FLAG_INVERT_Y
				);

			/* check for an error during the load process */
			if (0 == tex_2d)
			{
				printf("SOIL loading error: '%s'\n", SOIL_last_result());
				isTextured = false;
			}
			else{
				printf("SOIL loading success material %i\n", tex_2d);
				isTextured = true;
				normalId = tex_2d;
			}
		}

		if (true)
		{
			GLuint tex_2d = SOIL_load_OGL_texture
				(
				//strcat(pre,name),
				//"Texture/mygod.tga",
				metal.c_str(),
				SOIL_LOAD_AUTO,
				SOIL_CREATE_NEW_ID,
				SOIL_FLAG_INVERT_Y
				);

			/* check for an error during the load process */
			if (0 == tex_2d)
			{
				printf("SOIL loading error: '%s'\n", SOIL_last_result());
				isTextured = false;
			}
			else{
				printf("SOIL loading success material %i\n", tex_2d);
				isTextured = true;
				metalId = tex_2d;
			}
		}

		if (true)
		{
			GLuint tex_2d = SOIL_load_OGL_texture
				(
				//strcat(pre,name),
				//"Texture/mygod.tga",
				rough.c_str(),
				SOIL_LOAD_AUTO,
				SOIL_CREATE_NEW_ID,
				SOIL_FLAG_INVERT_Y
				);

			/* check for an error during the load process */
			if (0 == tex_2d)
			{
				printf("SOIL loading error: '%s'\n", SOIL_last_result());
				isTextured = false;
			}
			else{
				printf("SOIL loading success material %i\n", tex_2d);
				isTextured = true;
				roughId = tex_2d;
			}
		}



		//load the fucking shader
		loadObjShader();
}


Model3D::~Model3D()
{
}

void Model3D::VOnClientUpdate(GameInfoPacket* pData){

}

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
			
			if (isTextured){
				
				glEnable(GL_TEXTURE_2D);
				glUseProgram(shaderId);

				// Bind our diffuse texture in Texture Unit 0
				glActiveTexture(GL_TEXTURE1);
				glBindTexture(GL_TEXTURE_2D, textureId);
				// Set our "texture" sampler to user Texture Unit 0
				glUniform1i(textureUniform, 1);

				
				// Bind our diffuse texture in Texture Unit 1
				glActiveTexture(GL_TEXTURE2);
				glBindTexture(GL_TEXTURE_2D, normalId);
				// Set our "Normal    TextureSampler" sampler to user Texture Unit 0
				glUniform1i(normalUniform, 2);
				

				// Bind our diffuse texture in Texture Unit 1
				glActiveTexture(GL_TEXTURE3);
				glBindTexture(GL_TEXTURE_2D, metalId);
				// Set our "Normal    TextureSampler" sampler to user Texture Unit 0
				glUniform1i(metalUniform, 3);

				// Bind our diffuse texture in Texture Unit 1
				glActiveTexture(GL_TEXTURE4);
				glBindTexture(GL_TEXTURE_2D, roughId);
				// Set our "Normal    TextureSampler" sampler to user Texture Unit 0
				glUniform1i(roughUniform, 4);


				Vector3* cam = g_pCore->pGameView->pViewCamera->position;
				float campos[3] = {-cam->x,-cam->y,-cam->z};
				// Set our "normalmap" sampler to user Texture Unit 1
				glUniform3fv(cameraUniform, 1, campos);
				
//				GLfloat* matrix;
//				matrix = (float*)localTransform.GetMatrix4().getPointer();
//				glUniformMatrix4fv(worldMatUniform, 1, false, matrix);

				
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
				glTexCoord2f(shapes[i].mesh.texcoords[2 * i1 + 0], shapes[i].mesh.texcoords[2 * i1 + 1]);
			}
			//avg normal goes here
			glNormal3f(shapes[i].mesh.normals[3 * i1 + 0],
				       shapes[i].mesh.normals[3 * i1 + 1],
					   shapes[i].mesh.normals[3 * i1 + 2]
					  );
			glVertex3f(shapes[i].mesh.positions[3 * i1 + 0], shapes[i].mesh.positions[3 * i1 + 1], shapes[i].mesh.positions[3 * i1 + 2]);

			if (isTextured){
				//texture
				glTexCoord2f(shapes[i].mesh.texcoords[2 * i2 + 0], shapes[i].mesh.texcoords[2 * i2 + 1]);
			}
			//avg normal goes here
			glNormal3f(shapes[i].mesh.normals[3 * i2 + 0],
				shapes[i].mesh.normals[3 * i2 + 1],
				shapes[i].mesh.normals[3 * i2 + 2]
				);
			glVertex3f(shapes[i].mesh.positions[3 * i2 + 0], shapes[i].mesh.positions[3 * i2 + 1], shapes[i].mesh.positions[3 * i2 + 2]);

			if (isTextured){
				//texture
				glTexCoord2f(shapes[i].mesh.texcoords[2 * i3 + 0], shapes[i].mesh.texcoords[2 * i3 + 1]);
			}
			//avg normal goes here
			glNormal3f(shapes[i].mesh.normals[3 * i3 + 0],
				shapes[i].mesh.normals[3 * i3 + 1],
				shapes[i].mesh.normals[3 * i3 + 2]
				);
			glVertex3f(shapes[i].mesh.positions[3 * i3 + 0], shapes[i].mesh.positions[3 * i3 + 1], shapes[i].mesh.positions[3 * i3 + 2]);

			glEnd();

			if (isTextured){
				glBindTexture(GL_TEXTURE_2D, 0);
				glDisable(GL_TEXTURE_2D);
				glActiveTexture(GL_TEXTURE0);
				glUseProgram(0);
			}

		}

	}

	glPopMatrix();

	//rotate
	localTransform.rotation.y += 2;
}
void Model3D::VOnUpdate(GameInfoPacket* pData){

}

GLhandleARB Model3D::loadShader(char* filename, unsigned int type)
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

	return handle;
}

void Model3D::loadObjShader()
{
	GLhandleARB vertexShaderHandle;
	GLhandleARB fragmentShaderHandle;

	vertexShaderHandle = loadShader("super.vert", GL_VERTEX_SHADER);
	fragmentShaderHandle = loadShader("super.frag", GL_FRAGMENT_SHADER);

	shaderId = glCreateProgramObjectARB();

	glAttachObjectARB(shaderId, vertexShaderHandle);
	glAttachObjectARB(shaderId, fragmentShaderHandle);
	glLinkProgramARB(shaderId);


	textureUniform = glGetUniformLocationARB(shaderId, "textureMap");
	normalUniform = glGetUniformLocationARB(shaderId, "normalMap");
	metalUniform = glGetUniformLocationARB(shaderId, "metalMap");
	roughUniform = glGetUniformLocationARB(shaderId, "roughMap");
	//worldMatUniform = glGetUniformLocationARB(shaderId, "model_view_projection_matrix");

	//cameraUniform = glGetUniformLocationARB(shaderId, "CAMERA_POSITION");


	//shadowMapUniform = glGetUniformLocationARB(shaderId, "ShadowMap");
}