#ifndef MODELDATA_H
#define MODELDATA_H
#include "../../lib.h"

void enableDraw();
void billboard();
GLuint loadTexture(char *fname, bool rep);

const GLint dummy[] = {0, 0, 0, 0};
const GLfloat dummy2[] = {0, 0, 0, 5, 5, 0, 5, 5};
const GLuint EBO1[] = {0, 1, 2, 2, 1, 3};    

const GLuint cubeEBO[] = { //crateEBO 
	0, 1, 2, 2, 1, 3, 
	4, 5, 6, 6, 5, 7,
	8, 9, 10, 10, 9, 11,
	12, 13, 14, 14, 13, 15,
	16, 17, 18, 18, 17, 19																					 
};

#endif