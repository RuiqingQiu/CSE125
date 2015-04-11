#include "stdafx.h"
#include "button.h"



button::button()
{
}


button::~button()
{
}

bool setTexture(char * filename) {

	//return true if successfully set texture
	return false;
}

void button::draw() {
	//bind the texture and draw it

	glDisable(GL_LIGHTING);
	glPushMatrix();
	//glLoadMatrixd(glmatrix.getPointer());

	glEnable(GL_TEXTURE_2D);
	//glActiveTexture(GL_TEXTURE1);

	glBindTexture(GL_TEXTURE_2D, texture[0]);
	// Make sure no bytes are padded:
	glPixelStorei(GL_UNPACK_ALIGNMENT, 1);



	glPopMatrix();
	//glEnable(GL_LIGHTING);
	glDisable(GL_TEXTURE_2D);

}

void onClick() {
	//do somethin
}
