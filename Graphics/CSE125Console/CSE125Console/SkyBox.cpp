#include "stdafx.h"
#include "SkyBox.h"
#define GL_CLAMP_TO_EDGE 0x812F

SkyBox::SkyBox()
{
	initSkyBox();
}

SkyBox::SkyBox(char* filename)
{
	// Change the following filename to a suitable filename value.
	const char* lFilename = filename;

	
}

SkyBox::~SkyBox()
{
}

void SkyBox::VOnClientUpdate(GameInfoPacket* pData){

}

void SkyBox::VOnDraw(){
	glDisable(GL_LIGHTING);
	glPushMatrix();
	//glLoadMatrixd(glmatrix.getPointer());

	glEnable(GL_TEXTURE_2D);
	//glActiveTexture(GL_TEXTURE1);

	glBindTexture(GL_TEXTURE_2D, texture[1]);
	// Make sure no bytes are padded:
	glPixelStorei(GL_UNPACK_ALIGNMENT, 1);

	// Select GL_MODULATE to mix texture with polygon color for shading:
	glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_MODULATE);

	// Use bilinear interpolation:
	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
	//glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
	//glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);

	glEnable(GL_TEXTURE_2D);
	glBegin(GL_QUADS);
	glNormal3f(0, 0, -1);
	glTexCoord2f(0, 0); glVertex3f(size_of_texture_cube, -size_of_texture_cube, size_of_texture_cube);
	glTexCoord2f(1, 0); glVertex3f(-size_of_texture_cube, -size_of_texture_cube, size_of_texture_cube);
	glTexCoord2f(1, 1); glVertex3f(-size_of_texture_cube, size_of_texture_cube, size_of_texture_cube); //back up right
	glTexCoord2f(0, 1); glVertex3f(size_of_texture_cube, size_of_texture_cube, size_of_texture_cube); //back up left
	glEnd();

	//Front[0]

	glBindTexture(GL_TEXTURE_2D, texture[0]);
	// Make sure no bytes are padded:
	glPixelStorei(GL_UNPACK_ALIGNMENT, 1);

	// Select GL_MODULATE to mix texture with polygon color for shading:
	glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_MODULATE);

	// Use bilinear interpolation:
	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
	glEnable(GL_TEXTURE_2D);
	glBegin(GL_QUADS);
	glNormal3f(0, 0, 1);
	glTexCoord2f(0, 0); glVertex3f(-size_of_texture_cube, -size_of_texture_cube, -size_of_texture_cube);
	glTexCoord2f(1, 0); glVertex3f(size_of_texture_cube, -size_of_texture_cube, -size_of_texture_cube);
	glTexCoord2f(1, 1); glVertex3f(size_of_texture_cube, size_of_texture_cube, -size_of_texture_cube);   //up right
	glTexCoord2f(0, 1); glVertex3f(-size_of_texture_cube, size_of_texture_cube, -size_of_texture_cube); //up left
	glEnd();

	//Left[2]
	glBindTexture(GL_TEXTURE_2D, texture[2]);
	// Make sure no bytes are padded:
	glPixelStorei(GL_UNPACK_ALIGNMENT, 1);

	// Select GL_MODULATE to mix texture with polygon color for shading:
	glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_MODULATE);

	// Use bilinear interpolation:
	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
	glBegin(GL_QUADS);
	glNormal3f(-1, 0, 0);
	glTexCoord2f(0, 0); glVertex3f(-size_of_texture_cube, -size_of_texture_cube, size_of_texture_cube);
	glTexCoord2f(1, 0); glVertex3f(-size_of_texture_cube, -size_of_texture_cube, -size_of_texture_cube);
	glTexCoord2f(1, 1); glVertex3f(-size_of_texture_cube, size_of_texture_cube, -size_of_texture_cube); //up
	glTexCoord2f(0, 1); glVertex3f(-size_of_texture_cube, size_of_texture_cube, size_of_texture_cube); //up
	glEnd();


	//Right[3]
	glBindTexture(GL_TEXTURE_2D, texture[3]);
	// Make sure no bytes are padded:
	glPixelStorei(GL_UNPACK_ALIGNMENT, 1);

	// Select GL_MODULATE to mix texture with polygon color for shading:
	glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_MODULATE);

	// Use bilinear interpolation:
	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
	glBegin(GL_QUADS);
	glNormal3f(1, 0, 0);
	glTexCoord2f(0, 0); glVertex3f(size_of_texture_cube, -size_of_texture_cube, -size_of_texture_cube);
	glTexCoord2f(1, 0); glVertex3f(size_of_texture_cube, -size_of_texture_cube, size_of_texture_cube);
	glTexCoord2f(1, 1); glVertex3f(size_of_texture_cube, size_of_texture_cube, size_of_texture_cube);
	glTexCoord2f(0, 1); glVertex3f(size_of_texture_cube, size_of_texture_cube, -size_of_texture_cube);
	glEnd();

	//Top[4]
	glBindTexture(GL_TEXTURE_2D, texture[4]);
	// Make sure no bytes are padded:
	glPixelStorei(GL_UNPACK_ALIGNMENT, 1);

	// Select GL_MODULATE to mix texture with polygon color for shading:
	glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_MODULATE);

	// Use bilinear interpolation:
	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
	glBegin(GL_QUADS);

	glNormal3f(0.0, 1.0, 0.0);
	glTexCoord2f(0, 1); glVertex3f(-size_of_texture_cube, size_of_texture_cube, size_of_texture_cube); //connect to back up left
	glTexCoord2f(0, 0); glVertex3f(-size_of_texture_cube, size_of_texture_cube, -size_of_texture_cube); //connect to front up left
	glTexCoord2f(1, 0); glVertex3f(size_of_texture_cube, size_of_texture_cube, -size_of_texture_cube); //connect to front up right
	glTexCoord2f(1, 1); glVertex3f(size_of_texture_cube, size_of_texture_cube, size_of_texture_cube);  //connect to back right


	glEnd();
	glDisable(GL_TEXTURE_2D);

	glPopMatrix();
}
void SkyBox::VOnUpdate(GameInfoPacket* pData){

}

bool SkyBox::initSkyBox()
{
	texture[0] = SOIL_load_OGL_texture
		(
		"alpine_front.jpg"
		//"/Users/ruiqingqiu/Desktop/Qiu_Code/CSE167/CSE167 Final Project/()airFT.tga"
		//"/Users/Ennuma/Desktop/CSE167_Final_Project/nightsky_north.bmp"

		,
		SOIL_LOAD_AUTO,
		SOIL_CREATE_NEW_ID,
		SOIL_FLAG_INVERT_Y
		);
	if (texture[0] == 0)
	{
		printf("SOIL loading error: '%s'\n", SOIL_last_result());
		return false;
	}
	else{
		printf("SOIL loading success\n");
	}
	texture[1] = SOIL_load_OGL_texture
		(
		"alpine_back.jpg"
		//"/Users/ruiqingqiu/Desktop/Qiu_Code/CSE167/CSE167 Final Project/()airBK.tga"
		//"/Users/Ennuma/Desktop/CSE167_Final_Project/nightsky_south.bmp"

		,
		SOIL_LOAD_AUTO,
		SOIL_CREATE_NEW_ID,
		SOIL_FLAG_INVERT_Y
		);
	if (texture[1] == 0)
	{
		printf("SOIL loading error: '%s'\n", SOIL_last_result());
		return false;
	}
	else{
		printf("SOIL loading success\n");
	}

	texture[2] = SOIL_load_OGL_texture
		(
		"alpine_left.jpg"

		//"/Users/ruiqingqiu/Desktop/Qiu_Code/CSE167/CSE167 Final Project/()airRT.tga"
		//"/Users/Ennuma/Desktop/CSE167_Final_Project/nightsky_west.bmp"

		,
		SOIL_LOAD_AUTO,
		SOIL_CREATE_NEW_ID,
		SOIL_FLAG_INVERT_Y
		);
	if (texture[2] == 0)
	{
		printf("SOIL loading error: '%s'\n", SOIL_last_result());
		return false;
	}
	else{
		printf("SOIL loading success\n");
	}
	texture[3] = SOIL_load_OGL_texture
		(
		"alpine_right.jpg"
		//"/Users/ruiqingqiu/Desktop/Qiu_Code/CSE167/CSE167 Final Project/()airLT.tga"
		//"/Users/Ennuma/Desktop/CSE167_Final_Project/nightsky_east.bmp"

		,
		SOIL_LOAD_AUTO,
		SOIL_CREATE_NEW_ID,
		SOIL_FLAG_INVERT_Y
		);
	if (texture[3] == 0)
	{
		printf("SOIL loading error: '%s'\n", SOIL_last_result());
		return false;
	}
	else{
		printf("SOIL loading success\n");
	}
	texture[4] = SOIL_load_OGL_texture
		(
		"alpine_top.jpg"
		//"/Users/Ennuma/Desktop/CSE167_Final_Project/nightsky_up.bmp"

		,
		SOIL_LOAD_AUTO,
		SOIL_CREATE_NEW_ID,
		SOIL_FLAG_INVERT_Y
		);
	if (texture[4] == 0)
	{
		printf("SOIL loading error: '%s'\n", SOIL_last_result());
		return false;
	}
	else{
		printf("SOIL loading success\n");
	}
}