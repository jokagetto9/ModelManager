#ifndef TERRAINSHADER_H
#define TERRAINSHADER_H

#include "Shader.h"


//********************************* CONSTANTS *********************************


//********************************* INITIALIZATION *********************************
class TerrainShader : public Shader {
public:
	TerrainShader::TerrainShader();
	void TerrainShader::quit();	
	void TerrainShader::use();
	
	// draw
	void TerrainShader::drawStage(int s);
void TerrainShader::draw(float sx, float sy, float tx, float ty);

	void TerrainShader::build();
	void TerrainShader::buildCrossroad();
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