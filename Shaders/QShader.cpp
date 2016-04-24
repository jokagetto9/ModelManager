#include "QShader.h"


QShader::QShader(){
 	prog = 0;	vbo = 0;	ebo = 0;
	posAtt = -1; texAtt = -1;
	initBufferObjects();
	build();
	//if(_DEBUG) cout << "Loaded: Q Shader" << endl;
}

void QShader::quit(){
	glDeleteProgram( prog );
	glDeleteVertexArrays(1, &vao);
	glDeleteTextures(5, nubsT);
}

void QShader::use(){
	glBindVertexArray(vao); //preprep
	glUseProgram( prog ); //Bind program	
}

void QShader::prep(int t){
	glBindTexture(GL_TEXTURE_2D, nubsT[t]);	
	glUniform1f(texsUni, N_[t].scale);	
}

//********************************* BASIC QUAD PROGRAMS *********************************
const GLchar* QVerShdr[] = {
	"#version 150 compatibility\n"
	"in int p;"
	"out vec2 t;"
	"out vec4 vs;"
	"uniform float sc;"
	"void main() { "
	"	p;"
	"	mat4 mvp = gl_ModelViewMatrix;"
	"	for(int i=0; i<3; i++ ) "
	"		for(int j=0; j<3; j++ ) {"
	"			if ( i==j )	mvp[j][i] = sc;"
	//"			else if (j==1 )	{}"			
	"			else		mvp[j][i] = 0.0;"
	"	}"
	"   vec2 pos;"
	"	vec4 st = vec4(-2.5, 2.5, -2.5, 2.5);"
	"	if (gl_VertexID == 0)		{ pos.xy = st.xw; t.x = 0; t.y = 0;}"
	"	else if (gl_VertexID == 1)	{ pos.x = st.x;	pos.y = st.z; t.x = 0; t.y = 1;}"
	"	else if (gl_VertexID == 2)	{ pos.x = st.y;	pos.y = st.w; t.x = 1; t.y = 0;}"
	"	else if (gl_VertexID == 3)	{ pos.x = st.y;	pos.y = st.z; t.x = 1; t.y = 1;}"
	"	vec4 vPos = vec4( pos, 0.0, 1.0 );"
	"	gl_Position = gl_ProjectionMatrix * (mvp * vPos);" 
	"	vs = mvp * vPos;"
	"}"
};

void QShader::build(){
	// texture[]?
	
	nubsT[0] = loadTexture("NUB/rock1.png", false);
	nubsT[1] = loadTexture("NUB/tree1.png", false);
	nubsT[2] = loadTexture("NUB/tree2.png", false);
	nubsT[3] = loadTexture("NUB/tree3.png", false);	
	nubsT[4] = loadTexture("NUB/hay.png", false);	
	
	glGenVertexArrays(1, &vao);		glBindVertexArray(vao);
	glBindBuffer( GL_ELEMENT_ARRAY_BUFFER, lilebo );
	
	prog = glCreateProgram();
	if (buildProgram(QVerShdr, defFragShdr, prog)){	
		texUni[0] = glGetUniformLocation(prog, "tex");	//glUniform1i(texUni[0], 0); //gdebugger error?
		texsUni = glGetUniformLocation(prog, "sc");		
		attachDummy();	
	}
} //build better version

