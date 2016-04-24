#ifndef TILESHADER_H
#define TILESHADER_H

#include "Shader.h"


//********************************* CONSTANTS *********************************


//********************************* INITIALIZATION *********************************
class TileShader : public Shader {
public:
	TileShader::TileShader();
	void TileShader::quit();	
	void TileShader::use();
	
	// draw
	void TileShader::drawStage(int s);
void TileShader::draw(float sx, float sy, float tx, float ty);

	void TileShader::build();
	void TileShader::buildCrossroad();
/*/ Purpose: 
Side Effects:  
Triggers: 
/*/

//************************************************** MEMBERS ***************************************************
	
	GLuint scaleUni;

	GLuint soil;
	GLuint terrainT1[8];
	GLuint terrainT2[8];
};
#endif