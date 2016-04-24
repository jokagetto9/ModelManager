#include "TerrainShader.h"

TerrainShader::TerrainShader(){
 	prog = 0;	vbo = 0;	ebo = 0;
	posAtt = -1; texAtt = -1;
	build();	
	//if(_DEBUG) cout << "Loaded: Terrain Shader" << endl;
}

void TerrainShader::quit(){
	glDeleteProgram( prog );
	glDeleteVertexArrays(1, &vao);
	glDeleteTextures(8, terrainT1);
	glDeleteTextures(8, terrainT2);
	glDeleteTextures(1, &soil);

}	

void TerrainShader::use(){
	glBindVertexArray(vao);
	glUseProgram( prog ); //Bind program
}


void TerrainShader::drawStage(int s){
	glUniform4f(scaleUni, s, 50, 500, 500);
	glDrawElements( GL_TRIANGLES, 6, GL_UNSIGNED_INT, NULL );	
}


void TerrainShader::draw(float sx, float sy, float tx, float ty){
	glUniform4f(scaleUni, sx, sy, tx, ty);
	glDrawElements( GL_TRIANGLES, 6, GL_UNSIGNED_INT, NULL );
}
//********************************* TERRAIN PROGRAM *********************************
	//"   gl_FragColor = texture2D(tex, gl_TexCoord[0].xy) * vec4(1.0, 0.0, 0.0, 1.0);"
	//"   gl_Position = ftransform();"
	//"   gl_TexCoord[0] = gl_MultiTexCoord0;"
const GLchar* terrainVerShdr[] = {
	"#version 150 compatibility\n"
	"in int p;"
	"out vec2 t;"
	"out vec4 vs;"
	"uniform vec4 rscale;"
	"void main() { "
	"	p;"
	"   vec2 pos;"
	"	vec2 st = vec2(rscale.z, rscale.w);"
	"	if (gl_VertexID == 0)		{ pos.x = 0;	pos.y = 0;			t.x = rscale.x; t.y = rscale.y;}"
	"	else if (gl_VertexID == 1)	{ pos.x = 0;	pos.y = st.y;		t.x = rscale.x; t.y = 0;}"
	"	else if (gl_VertexID == 2)	{ pos.x = st.x;	pos.y = 0;			t.x = 0; t.y = rscale.y;}"
	"	else if (gl_VertexID == 3)	{ pos.x = st.x;	pos.y = st.y;		t.x = 0; t.y = 0;}"
	"	vec4 vPos = vec4(pos.x, 0.0, pos.y, 1.0);"
	"	gl_Position = gl_ModelViewProjectionMatrix * vPos;" 
	"	vs = gl_ModelViewMatrix * vPos;"
	"}"
};

void TerrainShader::build(){
	
	loadTexture2("grass1.png", terrainT1); //
	loadTexture2("grass2.png", terrainT2); //2x4
	soil = loadTexture("grass1.png", true);

	glGenVertexArrays(1, &vao); glBindVertexArray(vao);
	glBindBuffer( GL_ELEMENT_ARRAY_BUFFER, lilebo );
	//glBufferData( GL_ELEMENT_ARRAY_BUFFER, sizeof(EBO1), EBO1, GL_STATIC_DRAW );
	
	prog = glCreateProgram();
	if (buildProgram(terrainVerShdr, defFragShdr, prog)){	
		scaleUni = glGetUniformLocation(prog, "rscale");
		texUni[0] = glGetUniformLocation(prog, "tex");	 //glUniform1i(texUni[0], 0);					
		attachDummy();	
	}
} 


