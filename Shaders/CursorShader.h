#ifndef CURSORSHADER_H
#define CURSORSHADER_H

#include "Shader.h"

//********************************* CONSTANTS *********************************
//enum MenuTextures
//********************************* INITIALIZATION *********************************



class CursorShader : public Shader {
public:
	CursorShader::CursorShader();
	void CursorShader::quit();
	
	// draw
	void CursorShader::basicDraw();
	void CursorShader::drawCursor(int i);
	void CursorShader::drawCursor(int i, int x, int y);
	void CursorShader::drawIcon(GLuint tex, int x, int y);
	void CursorShader::drawCompass(float theta);

	void CursorShader::basicVAOsetup(VAO &v);
	void CursorShader::buildCursors();

	void convertString(char c[]);
/*/ Purpose: 
Side Effects:  
Triggers: 
/*/

//************************************************** MEMBERS ***************************************************
	
	VAO cursors[10];
	GLuint cursorT[10];
	
	GLuint scaUni, spinUni;
	glm::mat4 spin;
	glm::mat4 idm;
};
#endif