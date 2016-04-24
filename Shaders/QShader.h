#ifndef QSHADER_H
#define QSHADER_H

#include "Shader.h"

//********************************* CONSTANTS *********************************


//********************************* INITIALIZATION *********************************

class QShader : public Shader {
public:
	QShader::QShader();
	void QShader::quit();
	void QShader::use();
	
	// draw
	void QShader::prep(int t);
	//void QShader::prepTrees(int t);
	
	void QShader::tempDraw(int t);

	void QShader::build();
/*/ Purpose: 
Side Effects:  
Triggers: 
/*/

//************************************************** MEMBERS ***************************************************
	

	GLuint texsUni;
	GLuint nubsT[5];


};
#endif