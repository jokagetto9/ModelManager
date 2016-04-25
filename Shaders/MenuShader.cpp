#include "MenuShader.h"

//********************************* MENU PROGRAM *********************************
const GLchar* menuVerShdr[] = {
	"#version 150 compatibility\n"
	"in vec2 texC; out vec2 t;"
	"uniform vec2 pos;"
	"uniform float s;"
	"void main() { "
	"	t = texC;"
	"	gl_Position = gl_ProjectionMatrix  * vec4( pos.x+s*t.x, -(pos.y+s*t.y), 0.0, 1.0 );"
	"}"
};

const GLchar* menuFragShdr[] =	{
	"#version 150 compatibility\n"
    "uniform sampler2D tex;"
	"in vec2 t; "	
	"void main() { "
//	"	gl_FragColor = vec4(1,1,1,1);"
	"	gl_FragColor = texelFetch(tex, ivec2(t), 0);"
	"}"
};

const GLfloat FSData[] = {	dfWIDTH, dfHEIGHT, 	dfWIDTH, 0,		0, dfHEIGHT,		0, 0}; //del

MenuShader::MenuShader(){
	vbo = 0;	ebo = 0;
	posAtt = -1; texAtt = -1;
	
	initBufferObjects();

	prog = glCreateProgram();
	buildProgram(menuVerShdr, menuFragShdr, prog);
	
	texUni[0] = glGetUniformLocation(prog, "tex[0]");	//glUniform1i(texUni[0], 0);
	scaUni = glGetUniformLocation( prog, "s");	
	texAtt = glGetAttribLocation( prog, "texC" );	
	posAtt = glGetUniformLocation( prog, "pos" ); 	

	basicVAOsetup(fsMenu);
	fsMenu.vid.x = 0; fsMenu.vid.y = -RES.z; 
	glBindBuffer( GL_ELEMENT_ARRAY_BUFFER, lilebo );
	glBufferData( GL_ARRAY_BUFFER, sizeof(FSData), FSData, GL_STATIC_DRAW );

	
	menuT[LOAD] = loadTexture("MENU/crablord.png", false);
	menuT[TITLE] = loadTexture("MENU/title.png", false);

}

void MenuShader::quit(){
	glDeleteProgram( prog );
	glDeleteVertexArrays(1, &fsMenu.vao);	
	glDeleteBuffers(1, &fsMenu.vbo);	
	glDeleteVertexArrays(1, &map.vao);	
	glDeleteBuffers(1, &map.vbo);	
	glDeleteTextures(1, &mapT);
	glDeleteTextures(10, menuT);	
}

void MenuShader::basicVAOsetup(VAO &v){

	glGenVertexArrays(1, &v.vao);	glBindVertexArray(v.vao); //gen+bind vao
	//glGenBuffers( 1, &v.ebo );		glBindBuffer( GL_ELEMENT_ARRAY_BUFFER, v.ebo );
	glGenBuffers( 1, &v.vbo );		glBindBuffer( GL_ARRAY_BUFFER, v.vbo ); //gen+bind vbo

	glEnableVertexAttribArray( texAtt );
	glVertexAttribPointer( texAtt, 2, GL_FLOAT, GL_FALSE, 2 * sizeof(GLfloat), NULL );	

}

//********************************* DRAW *********************************
void MenuShader::draw(int i){
	glBindVertexArray(fsMenu.vao);
	glBindTexture(GL_TEXTURE_2D, menuT[i]);
	glUniform1f(scaUni, PIXELSCALE);	
	glUniform2f(posAtt, 0, -RES.z);		
	Shader::draw();
}


