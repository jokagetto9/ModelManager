//********************************* INITIALIZATION *********************************
#include "Shader.h"

GLuint Shader::bigebo = 0;
GLuint Shader::lilebo = 0;
GLuint Shader::dumbo = 0;

Shader::Shader(){
 	prog = 0;	
	posAtt = -1; texAtt = -1;
	vbo = 0; ebo = 0;
	
}

void Shader::initBufferObjects(){	
	
	glGenBuffers( 1, &lilebo );		glBindBuffer( GL_ELEMENT_ARRAY_BUFFER, lilebo );	
	glBufferData( GL_ELEMENT_ARRAY_BUFFER, sizeof(EBO1), EBO1, GL_STATIC_DRAW );
	//big ebo
	glGenBuffers( 1, &bigebo );		glBindBuffer( GL_ELEMENT_ARRAY_BUFFER, bigebo );
//glBufferData( GL_ELEMENT_ARRAY_BUFFER, sizeof(bigEBO), bigEBO, GL_STATIC_DRAW ); //load ebo	
	// dummy
	glGenBuffers( 1, &dumbo );		glBindBuffer( GL_ARRAY_BUFFER, dumbo );
	glBufferData( GL_ARRAY_BUFFER, sizeof(dummy), &dummy, GL_STATIC_DRAW );
}

void Shader::activateTextures(int i, GLuint test){
	for (int j = 0; j < i; j++){
		glBindTexture(GL_TEXTURE_2D, test);
		glUniform1i(texUni[i], i);
		glActiveTexture(GL_TEXTURE0+i+1);
	}	
	glActiveTexture(GL_TEXTURE0);
}

void Shader::finalQuit(){
	glDeleteBuffers(1, &lilebo);
	glDeleteBuffers(1, &bigebo);
	glDeleteBuffers(1, &dumbo);
}

void Shader::use(){	glUseProgram( prog ); }

int Shader::triangleCount(int s){ return s / 20 * 6; }

//********************************* DRAW CALLS *********************************

void Shader::draw(int vi){ 	glDrawElements( GL_TRIANGLES, vi, GL_UNSIGNED_INT, NULL );}

void Shader::draw(){	glDrawElements( GL_TRIANGLES, 6, GL_UNSIGNED_INT, NULL );}

//********************************* LINK  *********************************
void Shader::attachDummy(){
	dumAtt = glGetAttribLocation( prog, "p" );
	glBindBuffer( GL_ARRAY_BUFFER, dumbo );
	glVertexAttribPointer( dumAtt, 1, GL_FLOAT, GL_FALSE, 0, NULL );
	glEnableVertexAttribArray( dumAtt );	
	//glVertexAttrib1f(dumAtt, 0);
	//glBindBuffer( GL_ARRAY_BUFFER, 0);
}

//********************************* LOAD PROGRAM *********************************

/*/	buildProgram - reduces complex shader construction to one line
	Parameters:
	vsrc:	character data for vertex shader code	
	fsrc:	character data for fragment shader code
	Returns: True if program is built successfully
	Side Effect: Compiles vertex shader and fragment shader
		Links shaders into program if both are successful
/*/
bool Shader::buildProgram(const GLchar ** vsrc, const GLchar ** fsrc, GLuint progID){
	//IDs for each shader
	GLuint vertexShader, fragmentShader;
	// compile vertex shader - continue if successful - error if not
	if (loadShader(GL_VERTEX_SHADER, vertexShader, vsrc)) {		
	// compile vertex shader - continue if successful - error if not
		if (loadShader(GL_FRAGMENT_SHADER, fragmentShader, fsrc)){	
			// attach each shader to the program
			glAttachShader( progID, vertexShader );
			glAttachShader( progID, fragmentShader );
			// combine shaders into program
			bool success = loadProgram(progID);			
			// detach and delete shader IDs after completion
			glDetachShader( progID, vertexShader); 	
			//glDeleteShader(vertexShader);		
			glDetachShader( progID, fragmentShader); 		
			//glDeleteShader(fragmentShader);	
			return success; // program is ready for use	
		}
	} return false; // program failed
}

/*/	loadProgram - combine shaders into program
	Parameters:
	progID:	ID for referencing the program
	Returns: True if program is loaded successfully
	Side Effect: links program or displays linking error
/*/
bool Shader::loadProgram(GLuint progID){
	// buffer for error message
	char errorBuffer[ERROR_SIZE];
	// final stage of program creation - data sent to GPU
	glLinkProgram( progID );  
	// check if link is successful
	GLint programSuccess = GL_TRUE;
	glGetProgramiv( progID, GL_LINK_STATUS, &programSuccess );
	if( programSuccess != GL_TRUE )	{
		// print error message and return false
		glGetProgramInfoLog( progID, ERROR_SIZE, NULL, errorBuffer );
		std::cout << errorBuffer << std::endl; return false;
	}
	return true;	// link is successful
}

/*/	loadProgram - combine shaders into program
	Parameters:
	shdrType: type of shader
	shdr: shader ID being compiled
	Returns: True if shader is compiled successfully
	Side Effect: compiles shader or displays linking error
/*/
bool Shader::loadShader(GLenum shdrType, GLuint &shdr, const GLchar ** src ){
	// ensures shdrType is an accepted type - GL_GEOMETRY_SHADER can be added in the future
	assert(shdrType == GL_VERTEX_SHADER || shdrType == GL_FRAGMENT_SHADER);
	// buffer for error message
	char errorBuffer[ERROR_SIZE];
	// Create and compile the vertex shader
	shdr = glCreateShader(shdrType);   
    // upload shader source to GPU
	glShaderSource(shdr, 1, src, NULL);
	// compile shader
    glCompileShader(shdr);		
	// check if compile is successful
	GLint status;
	glGetShaderiv(shdr, GL_COMPILE_STATUS, &status);	
	if (status != GL_TRUE) {		
		// print error message, delete shader ID and return false
		glGetShaderInfoLog(shdr, ERROR_SIZE, NULL, errorBuffer);
		std::cout << errorBuffer << std::endl;
		glDeleteShader(shdr);	return false;
	}
	return true;	//compile is successful
}

