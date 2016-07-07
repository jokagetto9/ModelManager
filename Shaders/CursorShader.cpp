#include "CursorShader.h"

//********************************* MENU PROGRAM *********************************
const GLchar* cursorVerShdr[] = {
	"#version 150 compatibility\n"
	"in vec2 texC; out vec2 t;"
	"uniform vec2 pos;"
	"uniform mat4 spin;"
	"uniform float s;"
	"void main() { "
	"	t = texC;"
	"	gl_Position = gl_ProjectionMatrix * (spin * vec4( pos.x+s*t.x, -(pos.y+s*t.y), 0.0, 1.0 ));"
	"}"
};

const GLchar* cursorFragShdr[] =	{
	"#version 150 compatibility\n"
    "uniform sampler2D tex;"
	"in vec2 t; "	
	"void main() { "
//	"	gl_FragColor = vec4(1,1,1,1);"
	"	gl_FragColor = texelFetch(tex, ivec2(t), 0);"
	"}"
};

CursorShader::CursorShader(){
	vbo = 0;	ebo = 0;
	posAtt = -1; texAtt = -1;

	prog = glCreateProgram();
	buildProgram(cursorVerShdr, cursorFragShdr, prog);
	
	texUni[0] = glGetUniformLocation(prog, "tex[0]");	//glUniform1i(texUni[0], 0);
	scaUni = glGetUniformLocation( prog, "s");	
	spinUni = glGetUniformLocation(prog, "spin");
	texAtt = glGetAttribLocation( prog, "texC" );	
	posAtt = glGetUniformLocation( prog, "pos" ); 	

	buildCursors();

}

void CursorShader::quit(){
	glDeleteProgram( prog );
	for (int i = 0; i < 4; i++){
		glDeleteVertexArrays(1, &cursors[i].vao);		
		glDeleteBuffers(1, &cursors[i].vbo);
	}	
}

void CursorShader::basicVAOsetup(VAO &v){

	glGenVertexArrays(1, &v.vao);	glBindVertexArray(v.vao); //gen+bind vao
	//glGenBuffers( 1, &v.ebo );		glBindBuffer( GL_ELEMENT_ARRAY_BUFFER, v.ebo );
	glGenBuffers( 1, &v.vbo );		glBindBuffer( GL_ARRAY_BUFFER, v.vbo ); //gen+bind vbo

	glEnableVertexAttribArray( texAtt );
	glVertexAttribPointer( texAtt, 2, GL_FLOAT, GL_FALSE, 2 * sizeof(GLfloat), NULL );	

}

//********************************* MENU PROGRAM *********************************
const GLfloat pData[] = {	1, 1, 	1, 0,		0, 1,		0, 0};
const GLfloat p4Data[] = {	4, 4, 	4, 0,		0, 4,		0, 0};
const GLfloat hubData[] = {	166, 166, 	166, 0,		0, 166,		0, 0};
const GLfloat FSData[] = {	1000, 700, 	1000, 0,		0, 700,		0, 0}; //del
const GLfloat mapData[] = {	25, 25, 	25, 0,		0, 25,		0, 0};

const GLfloat compassData[] = {	9, 9, 	9, 0,		0, 9,		0, 0};
const GLfloat iconData[] = {	32, 32, 	32, 0,		0, 32,		0, 0};
const GLfloat arrowData[] = {	10, 10, 	10, 0,		0, 10,		0, 0};
const GLfloat cursor1Data[] = {	42, 42, 	42, 0,		0, 42,		0, 0};
const GLfloat cursor2Data[] = {	76, 76, 	76, 0,		0, 76,		0, 0};
const GLfloat cursor3Data[] = {	86, 44, 	86, 0,		0, 44,		0, 0};

void CursorShader::buildCursors(){
	int i = 0;
	basicVAOsetup(cursors[i]);
	cursors[i].vid.z = PIXELSCALE;
	glBindBuffer( GL_ELEMENT_ARRAY_BUFFER, lilebo );
	glBufferData( GL_ARRAY_BUFFER, sizeof(pData), pData, GL_STATIC_DRAW );

	i = 1;
	//cursorT[i] = loadTexture("MENU/key.png", false);
	basicVAOsetup(cursors[i]);
	cursors[i].vid.z = PIXELSCALE;
	glBindBuffer( GL_ELEMENT_ARRAY_BUFFER, lilebo );
	glBufferData( GL_ARRAY_BUFFER, sizeof(arrowData), arrowData, GL_STATIC_DRAW );

	i = 2;
	basicVAOsetup(cursors[i]);
	cursors[i].vid.z = 1;
	glBindBuffer( GL_ELEMENT_ARRAY_BUFFER, lilebo );
	glBufferData( GL_ARRAY_BUFFER, sizeof(p4Data), p4Data, GL_STATIC_DRAW );

	i = 3;
	basicVAOsetup(cursors[i]);
	cursors[i].vid.z = 1;
	glBindBuffer( GL_ELEMENT_ARRAY_BUFFER, lilebo );
	glBufferData( GL_ARRAY_BUFFER, sizeof(cursor2Data), cursor2Data, GL_STATIC_DRAW );		

	i = 4;
	basicVAOsetup(cursors[i]);
	cursors[i].vid.z = 1;
	glBindBuffer( GL_ELEMENT_ARRAY_BUFFER, lilebo );
	glBufferData( GL_ARRAY_BUFFER, sizeof(cursor3Data), cursor3Data, GL_STATIC_DRAW );		

	i = 5;
	//cursorT[i] = loadTexture("MENU/icon.png", false);
	basicVAOsetup(cursors[i]);
	cursors[i].vid.z = 1;
	glBindBuffer( GL_ELEMENT_ARRAY_BUFFER, lilebo );
	glBufferData( GL_ARRAY_BUFFER, sizeof(iconData), iconData, GL_STATIC_DRAW );		

	i = 9;
	//cursorT[i] = loadTexture("MENU/arrow.png", false);		
	basicVAOsetup(cursors[i]);
	cursors[i].vid.x = -27; cursors[i].vid.y = -27; 
	cursors[i].vid.z = 6;
	glBindBuffer( GL_ELEMENT_ARRAY_BUFFER, lilebo );
	glBufferData( GL_ARRAY_BUFFER, sizeof(compassData), compassData, GL_STATIC_DRAW );
	i++;


}


void CursorShader::basicDraw(){
	glUniformMatrix4fv(spinUni, 1, GL_FALSE, glm::value_ptr(idm));
	Shader::draw();
}

void CursorShader::drawCursor(GLuint tex, int i){
	glBindVertexArray(cursors[i].vao);
	glBindTexture(GL_TEXTURE_2D, tex);
	glUniform1f(scaUni, cursors[i].vid.z);	
	glUniform2f(posAtt, cursors[i].vid.x, cursors[i].vid.y );	
	basicDraw();
}


void CursorShader::drawCursor(GLuint tex, int i, int x, int y){
	glBindVertexArray(cursors[i].vao);
	glBindTexture(GL_TEXTURE_2D, tex);
	glUniform1f(scaUni, cursors[i].vid.z);	
	glUniform2f(posAtt, x, y-RES.z );		
	basicDraw();
}

void CursorShader::drawIcon(GLuint tex, int x, int y){
	int i=5;
	glBindVertexArray(cursors[i].vao);
	glBindTexture(GL_TEXTURE_2D, tex);
	glUniform1f(scaUni, cursors[i].vid.z);	
	glUniform2f(posAtt, x, y-RES.z );		
	basicDraw();
}

