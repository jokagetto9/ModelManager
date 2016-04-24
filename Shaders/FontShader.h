#ifndef FONTSHADER_H
#define FONTSHADER_H

#include "Shader.h"

//********************************* CONSTANTS *********************************


//********************************* INITIALIZATION *********************************


class FontShader : public Shader {
public:
	FontShader::FontShader();
	void FontShader::quit();	

	
	void FontShader::basicVAOsetup(VAO &v);

	
	void FontShader::	buildFont();
	void FontShader::loadMessage();
	
	void FontShader::beginText(string s);
	void FontShader::appendText(string s, int w, int y);
	void FontShader::convertString(string s, int w, int y, int a);
	
	void FontShader::changeFont();
	
	// draw
	void FontShader::build();
	void FontShader::draw(int x, int y);
/*/ Purpose: 
Side Effects:  
Triggers: 
/*/

//************************************************** MEMBERS ***************************************************
		bool smallFont;


		GLuint fontT, sfontT, ibo1, ibo2, ibo3;
		GLint offsAtt;

		glm::vec4 message1[20];	
		glm::vec4 message2[100];			
		glm::vec4 message3[200];		
		glm::vec2 fontC[100]; 		
		glm::vec2 smallFontC[100]; 
	
		int currBuffer;
		int counter;
		int chars[4];
		int maxChars[4];

	
//************************************************** MEMBER FUNCTIONS ***************************************************
	
	int FontShader:: currMax(){ return maxChars[currBuffer];}
	int FontShader:: currChars(){ return chars[currBuffer];}
	void FontShader:: setBuffer(int i){ if (i > 0 && i < 4) currBuffer = i;}
	void FontShader:: clearBuffer(int i){ if (i >= 0 && i < 4) chars[i] = 0;}
	void FontShader:: clearAllBuffers(){ for (int i = 0; i < 4; i++) clearBuffer(i);}

};
#endif