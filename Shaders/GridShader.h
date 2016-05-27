#ifndef GRID6SHADER_H
#define GRIDSHADER_H

#include "Shader.h"

//********************************* CONSTANTS *********************************


//********************************* INITIALIZATION *********************************



class GridShader : public Shader {
public:
	GridShader::GridShader();
	void GridShader::quit();

	void GridShader::use();

	// prep
	void GridShader::prepHero();
	void GridShader::prep(ID tex, float scale);

	void GridShader::drawx4(int t);
	void GridShader::drawx16(int t);

	//build
	void GridShader::build();	
/*/ Purpose: 
Side Effects:  
Triggers: 
/*/

//************************************************** MEMBERS ***************************************************
	
	
	//x4
	GLuint treesT;	
	//x16
	GLuint heroT, npcT;
	GLuint laserPalmT;
	GLuint nobsT, miniNubsT, cactiT;
	GLuint mimicT;
	GLuint texIUni, texsUni;
	

};
#endif