#include "stdafx.h"
#include "Window.h"
#include "SkyBox.h"
#define GL_CLAMP_TO_EDGE 0x812F

SkyBox::SkyBox()
{
	skyBoxName = "skyboxes/alpine";
	initSkyBox();
}

SkyBox::SkyBox(std::string filename)
{
	skyBoxName = filename;
	initSkyBox();
}

SkyBox::~SkyBox()
{
}

GLuint loadCubemap(vector<string> faces)
{
	cout << "in load cube map" << endl;
	GLuint textureID;
	glGenTextures(1, &textureID);
	glActiveTexture(GL_TEXTURE0);

	int width, height;
	unsigned char* image;
	glBindTexture(GL_TEXTURE_CUBE_MAP, textureID);

	for (GLuint i = 0; i < faces.size(); i++)
	{
		cout << faces[i] << endl;
		char *str = new char[faces[i].length() + 1];
		strcpy(str, faces[i].c_str());
		image = SOIL_load_image(str, &width, &height, 0, SOIL_LOAD_RGB);
		//cout << image << endl;
		glTexImage2D(
			GL_TEXTURE_CUBE_MAP_POSITIVE_X + i, 0,
			GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, image
			);
		SOIL_free_image_data(image);
	}
	/*DEBUG CODE */ 
	/*
	        GLubyte red[3] = {255, 0, 0};
	        GLubyte green[3] = {0, 255, 0};
	        GLubyte blue[3] = {0, 0, 255};
	        GLubyte cyan[3] = {0, 255, 255};
	        GLubyte magenta[3] = {255, 0, 255};
	        GLubyte yellow[3] = {255, 255, 0};
	        glTexImage2D(GL_TEXTURE_CUBE_MAP_POSITIVE_X ,
	                     0,3,1,1,0,GL_RGB,GL_UNSIGNED_BYTE, red);
	        glTexImage2D(GL_TEXTURE_CUBE_MAP_NEGATIVE_X ,
	                     0,3,1,1,0,GL_RGB,GL_UNSIGNED_BYTE, green);
	        glTexImage2D(GL_TEXTURE_CUBE_MAP_POSITIVE_Y ,
	                     0,3,1,1,0,GL_RGB,GL_UNSIGNED_BYTE, blue);
	        glTexImage2D(GL_TEXTURE_CUBE_MAP_NEGATIVE_Y ,
	                     0,3,1,1,0,GL_RGB,GL_UNSIGNED_BYTE, cyan);
	        glTexImage2D(GL_TEXTURE_CUBE_MAP_POSITIVE_Z ,
	                     0,3,1,1,0,GL_RGB,GL_UNSIGNED_BYTE, magenta);
	        glTexImage2D(GL_TEXTURE_CUBE_MAP_NEGATIVE_Z ,
	                     0,3,1,1,0,GL_RGB,GL_UNSIGNED_BYTE, yellow);
	*/
	glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
	glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
	glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_R, GL_CLAMP_TO_EDGE);
	glBindTexture(GL_TEXTURE_CUBE_MAP, 0);



	return textureID;
}


void SkyBox::VOnClientUpdate(GameInfoPacket* pData){

}

void SkyBox::VOnDraw(){
	glPushMatrix();
	localTransform.position.y = 100;
	glMultMatrixd(localTransform.GetGLMatrix4().getPointer());

	//glLoadIdentity();
	glDisable(GL_CULL_FACE);
	Window::shader_system->BindShader(SKYBOX_SHADER);
	glBegin(GL_QUADS);

	//Back
	glNormal3f(0, 0, -1);
	glVertex3f(size_of_texture_cube, -size_of_texture_cube, size_of_texture_cube);
	glVertex3f(-size_of_texture_cube, -size_of_texture_cube, size_of_texture_cube);
	glVertex3f(-size_of_texture_cube, size_of_texture_cube, size_of_texture_cube); //back up right
	glVertex3f(size_of_texture_cube, size_of_texture_cube, size_of_texture_cube); //back up left
	glEnd();

	//Front[0]

	glBegin(GL_QUADS);
	glNormal3f(0, 0, 1);
	glVertex3f(-size_of_texture_cube, -size_of_texture_cube, -size_of_texture_cube);
	glVertex3f(size_of_texture_cube, -size_of_texture_cube, -size_of_texture_cube);
	glVertex3f(size_of_texture_cube, size_of_texture_cube, -size_of_texture_cube);   //up right
	glVertex3f(-size_of_texture_cube, size_of_texture_cube, -size_of_texture_cube); //up left
	glEnd();

	//right
	glBegin(GL_QUADS);
	glNormal3f(-1, 0, 0);
	glVertex3f(-size_of_texture_cube, -size_of_texture_cube, size_of_texture_cube);
	glVertex3f(-size_of_texture_cube, -size_of_texture_cube, -size_of_texture_cube);
	glVertex3f(-size_of_texture_cube, size_of_texture_cube, -size_of_texture_cube); //up
	glVertex3f(-size_of_texture_cube, size_of_texture_cube, size_of_texture_cube); //up
	glEnd();

	//left
	glBegin(GL_QUADS);
	glNormal3f(1, 0, 0);
	 glVertex3f(size_of_texture_cube, -size_of_texture_cube, -size_of_texture_cube);
	 glVertex3f(size_of_texture_cube, -size_of_texture_cube, size_of_texture_cube);
	 glVertex3f(size_of_texture_cube, size_of_texture_cube, size_of_texture_cube);
	glVertex3f(size_of_texture_cube, size_of_texture_cube, -size_of_texture_cube);
	glEnd();

	glBegin(GL_QUADS);

	glNormal3f(0.0, 1.0, 0.0);

	glVertex3f(-size_of_texture_cube, size_of_texture_cube, size_of_texture_cube); //front up right
	glVertex3f(size_of_texture_cube, size_of_texture_cube, size_of_texture_cube);  //connect to front left
	glVertex3f(size_of_texture_cube, size_of_texture_cube, -size_of_texture_cube); //connect to front up right
	glVertex3f(-size_of_texture_cube, size_of_texture_cube, -size_of_texture_cube); //connect to front up left

	glEnd();

	
	glBegin(GL_QUADS);

	glNormal3f(0.0, -1.0, 0.0);

	glVertex3f(-size_of_texture_cube, -localTransform.position.y-1, size_of_texture_cube); //front up right
	glVertex3f(size_of_texture_cube, -localTransform.position.y-1, size_of_texture_cube);  //connect to front left
	glVertex3f(size_of_texture_cube, -localTransform.position.y-1, -size_of_texture_cube); //connect to front up right
	glVertex3f(-size_of_texture_cube, -localTransform.position.y-1, -size_of_texture_cube); //connect to front up left

	glEnd();
	glPopMatrix();

	Window::shader_system->UnbindShader();
}
void SkyBox::VOnUpdate(GameInfoPacket* pData){

}

bool SkyBox::initSkyBox()
{
	cout << "enter init skybox" << endl;
	vector<string> faces;

	/*
	faces.push_back("skyboxes/alpine_left.jpg");
	faces.push_back("skyboxes/alpine_right.jpg");
	faces.push_back("skyboxes/alpine_top.jpg");
	faces.push_back("skyboxes/alpine_top.jpg");
	faces.push_back("skyboxes/alpine_back.jpg");
	faces.push_back("skyboxes/alpine_front.jpg");
	*/
	
	string concat = skyBoxName + "_left.jpg";
	faces.push_back(concat);
	cout << faces[0] << endl;
	concat = skyBoxName + "_right.jpg";
	faces.push_back(concat);
	concat = skyBoxName + "_top.jpg";
	faces.push_back(concat);
	concat = skyBoxName + "_down.jpg";
	faces.push_back(concat);
	concat = skyBoxName + "_back.jpg";
	faces.push_back(concat);
	concat = skyBoxName + "_front.jpg";
	faces.push_back(concat);
	/*
	string concat = skyBoxName + "_left.tga";
	faces.push_back(concat);
	cout << faces[0] << endl;
	concat = skyBoxName + "_right.tga";
	faces.push_back(concat);
	concat = skyBoxName + "_top.tga";
	faces.push_back(concat);
	concat = skyBoxName + "_down.tga";
	faces.push_back(concat);
	concat = skyBoxName + "_back.tga";
	faces.push_back(concat);
	concat = skyBoxName + "_front.tga";
	faces.push_back(concat);
	*/
	cubemapTexture = loadCubemap(faces);
	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_CUBE_MAP, cubemapTexture);

	/*
	texture[0] = SOIL_load_OGL_texture
		(
		concat.c_str(),
		SOIL_LOAD_AUTO,
		SOIL_CREATE_NEW_ID,
		SOIL_FLAG_INVERT_Y
		);
	if (texture[0] == 0)
	{
		std::cout << concat << std::endl;
		printf("SOIL loading error: '%s'\n", SOIL_last_result());
		return false;
	}

	concat = skyBoxName + "_back.jpg";
	texture[1] = SOIL_load_OGL_texture
		(
		concat.c_str(),
		SOIL_LOAD_AUTO,
		SOIL_CREATE_NEW_ID,
		SOIL_FLAG_INVERT_Y
		);
	if (texture[1] == 0)
	{
		std::cout << concat << std::endl;
		printf("SOIL loading error: '%s'\n", SOIL_last_result());
		return false;
	}

	concat = skyBoxName + "_left.jpg";
	texture[2] = SOIL_load_OGL_texture
		(
		concat.c_str(),
		SOIL_LOAD_AUTO,
		SOIL_CREATE_NEW_ID,
		SOIL_FLAG_INVERT_Y
		);
	if (texture[2] == 0)
	{
		std::cout << concat << std::endl;
		printf("SOIL loading error: '%s'\n", SOIL_last_result());
		return false;
	}

	concat = skyBoxName + "_right.jpg";
	texture[3] = SOIL_load_OGL_texture
		(
		concat.c_str(),
		SOIL_LOAD_AUTO,
		SOIL_CREATE_NEW_ID,
		SOIL_FLAG_INVERT_Y
		);
	if (texture[3] == 0)
	{
		std::cout << concat << std::endl;
		printf("SOIL loading error: '%s'\n", SOIL_last_result());
		return false;
	}

	concat = skyBoxName + "_top.jpg";
	texture[4] = SOIL_load_OGL_texture
		(
		concat.c_str(),
		SOIL_LOAD_AUTO,
		SOIL_CREATE_NEW_ID,
		SOIL_FLAG_INVERT_Y
		);
	if (texture[4] == 0)
	{
		std::cout << concat << std::endl;
		printf("SOIL loading error: '%s'\n", SOIL_last_result());
		return false;
	}
	*/
	return true;
}