#ifndef MENUSHADER_H
#define MENUSHADER_H

#include "Shader.h"

//********************************* CONSTANTS *********************************
//enum MenuTextures
const int MENUCOUNT = 25;
//********************************* INITIALIZATION *********************************



class MenuShader : public Shader {
public:
	MenuShader::MenuShader();
	void MenuShader::quit();
	
	// draw
	void MenuShader::draw(int i);
	void MenuShader::drawMap(int x, int y);

	void MenuShader::basicVAOsetup(VAO &v);
	void MenuShader::buildMenus();

/*/ Purpose: 
Side Effects:  
Triggers: 
/*/

//************************************************** MEMBERS ***************************************************
	
	VAO fsMenu;
	GLuint menuT[MENUCOUNT];
	
	VAO map;
	GLuint mapT;

	
	GLuint scaUni, spinUni;
	glm::mat4 spin;
	glm::mat4 idm;
};
#endif