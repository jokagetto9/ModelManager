#ifndef SHADER_H
#define SHADER_H

#include "../ModelData.h"

//********************************* CONSTANTS *********************************


struct VAO{
	GLuint vao;
	GLuint vbo;
	GLuint ebo;
	int tri;
	glm::vec4 vid;
};

const int ERROR_SIZE = 512;

//********************************* INITIALIZATION *********************************
class Shader {
public:
	Shader::Shader();
	
	static void Shader::initBufferObjects();
	void Shader::activateTextures(int i, GLuint test);
	static void Shader::finalQuit();
	
	void Shader::use();
	int Shader::triangleCount(int s);
	
	virtual void Shader::build(){}
	void Shader::buildBasic();

	// draw
	void Shader::draw();	
	void Shader::draw(int vi);	
	void Shader::testDraw();
	
	void Shader::attachDummy();
	// load
	bool Shader::loadVertexShader(const GLchar ** src);
	bool Shader::loadFragmentShader(const GLchar ** src);
	bool Shader::loadShader(GLenum shdrType, GLuint &shdr, const GLchar ** src );
	bool Shader::loadProgram(GLuint progID);
	bool Shader::buildProgram(const GLchar ** vsrc, const GLchar ** fsrc, GLuint progID);


//************************************************** MEMBERS ***************************************************
	
	
	
	GLuint vao; GLuint prog;
	GLuint texUni[5];

	GLint posAtt, texAtt, dumAtt;
	GLuint vbo, ebo;

	static GLuint bigebo, lilebo, dumbo;
};
#endif