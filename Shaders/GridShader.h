#ifndef GRID6SHADER_H
#define GRIDSHADER_H

#include "Shader.h"

//********************************* CONSTANTS *********************************
enum GRIDTYPE {G1x1, G2x2, G4x4, GMISC};

struct ShaderProfile{
	ID tex;
	float scale;	
	GRIDTYPE g;
};
//********************************* INITIALIZATION *********************************



class GridShader : public Shader {
public:
	GridShader::GridShader();
	void GridShader::quit();

	void GridShader::use();

	// prep
	void GridShader::prepHero();
	void GridShader::prep(ShaderProfile &sp);

	void GridShader::drawx4(int t);
	void GridShader::drawx16(int t);
	void GridShader::flip(int x, int y);	

	//build
	void GridShader::build();	
/*/ Purpose: 
Side Effects:  
Triggers: 
/*/

//************************************************** MEMBERS ***************************************************
	
	GLuint heroT;
	GLuint laserPalmT;
	GLuint texIndex, texScale, gridScale;
	float scale;

};
#endif