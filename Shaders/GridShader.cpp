#include "GridShader.h"


GridShader::GridShader(){
 	prog = 0;	vbo = 0;	ebo = 0;
	posAtt = -1; texAtt = -1;
	initBufferObjects();
	build();
	//glUniform1i(texUni[0], 0);		
}

void GridShader::quit(){
	glDeleteProgram( prog );
	glDeleteVertexArrays(1, &vao);
	
	glDeleteTextures(1, &treesT);
	glDeleteTextures(1, &heroT);	
	glDeleteTextures(1, &npcT);		
	glDeleteTextures(1, &cactiT);		
	glDeleteTextures(1, &miniNubsT);
	glDeleteTextures(1, &nobsT);
}

void GridShader::use(){	
	glUseProgram( prog ); //Bind program	
	glBindVertexArray(vao);			
}


void GridShader::prepTree(){
	glBindTexture(GL_TEXTURE_2D, treesT);
	//glUniform1i(texUni, 0);		
}
void GridShader::prepCacti(){
	glBindTexture(GL_TEXTURE_2D, cactiT);	
	glUniform2f(texsUni, 0.25, 3);	
}
void GridShader::prepFlowers(){
	glBindTexture(GL_TEXTURE_2D, miniNubsT);
	glUniform2f(texsUni, 0.25, 0.4); //mininubsize	
}
void GridShader::prepNobs(int s){
	glBindTexture(GL_TEXTURE_2D, nobsT);
	glUniform2f(texsUni, 0.25, s); //mininubsize	
}
void GridShader::prepHero(){
	use();
	glBindTexture(GL_TEXTURE_2D, heroT);	
	glUniform2f(texsUni, 0.25, 2);	
}
void GridShader::prepNPC(){
	use();
	glBindTexture(GL_TEXTURE_2D, npcT);	
	glUniform2f(texsUni, 0.25, 1);	
}


void GridShader::drawx16(int t){
	glUniform2f(texIUni, G16__[t].x, G16__[t].z);		
	glDrawElements( GL_TRIANGLES, 6, GL_UNSIGNED_INT, NULL );
}

//********************************* QUAD16 PROGRAM *********************************
const GLchar* gridVerShdr[] = {
	"#version 150 compatibility\n"
	"in int p;"
	"out vec2 t;"
	"out vec4 vs;"
	"out vec4 dv;"
	"uniform vec2 texI;"	
	"uniform vec2 texS;"
	"void main() { "
	"	p;"		
	"	float c = texS.x;  float d = texS.y * 5; vec2 pos;"
	"	if (gl_VertexID == 0)		{ pos.x = d/2 ;	pos.y = 0; t.x = c*(texI.x+1); t.y = c*(texI.y+1);}"
	"	else if (gl_VertexID == 1)	{ pos.x = d/2 ;	pos.y = d; t.x = c*(texI.x+1); t.y = c*texI.y;}"
	"	else if (gl_VertexID == 2)	{ pos.x = -d/2 ;	pos.y = 0; t.x = c*texI.x; t.y = c*(texI.y+1);}"
	"	else if (gl_VertexID == 3)	{ pos.x = -d/2 ;	pos.y = d; t.x = c*texI.x; t.y = c*texI.y;}"		
	"	vec4 vPos = vec4( pos, 0.0, 1.0 );"

	"	mat4 mvm = gl_ModelViewMatrix;"
	"	for(int i=0; i<3; i++ ) "
	"		for(int j=0; j<3; j++ ) {"
	"			if (j==1 ){ }"//if (i==1) mvm[1][1] = 1;}"	
	"			else if ( i==j ) mvm[j][i] = 1;"
	"			else		mvm[j][i] = 0.0;"
	"	}"//*/
	"	dv = gl_ProjectionMatrix * (mvm * vPos);"
	"	mvm[1][0] = 0; mvm[1][2] = 0; mvm[1][1] = 1;"
	"	gl_Position = gl_ProjectionMatrix * (mvm * vPos);" 
	"	vs = mvm * vPos;"
	"}"
};

const GLchar* gridFragShdr[] =	{
	"#version 150 compatibility\n"
    "uniform sampler2D tex;"
	"in vec2 t; "	
	"in vec4 vs;"
	"in vec4 dv;"
	"void main() { "
	"	float d = length(vs);"
	"	float fog = (gl_Fog.end - d) * gl_Fog.scale;"
	"	fog = clamp(fog, 0, 1);"
	"	vec4 image = texture2D(tex, t);"
	"	if (image.w < 0.9) discard;"
	"	vec3 color = mix(gl_Fog.color.rgb, image.rgb, fog);"
	"	gl_FragColor = vec4(color.rgb, image.a);" //image;"//
	// depth tweak
	//"float dep = ((gl_DepthRange.diff * dv.z/dv.w) + gl_DepthRange.near + gl_DepthRange.far) * 0.5;"
	"float dep = 0.5*dv.z/dv.w + 0.5;"
	"if (dep > 0.9999) gl_FragDepth = gl_FragCoord.z; "//gl_FragColor.r = 1;}"
	"else gl_FragDepth = dep;"
	"}"
};

void GridShader::build(){
	
	//4x4	
	heroT = loadTexture("MAGE/hood.png", false); 
	laserPalmT = loadTexture("MAGE/laserpalm.png", false); 
	npcT = loadTexture("MOBS/npc1.png", false);

	glGenVertexArrays(1, &vao); 	glBindVertexArray(vao);
	glBindBuffer( GL_ELEMENT_ARRAY_BUFFER, lilebo );
	
	prog = glCreateProgram();
	if (buildProgram(gridVerShdr, gridFragShdr, prog)){			
		texIUni = glGetUniformLocation(prog, "texI");
		texUni[0] = glGetUniformLocation(prog, "tex");
		texsUni = glGetUniformLocation(prog, "texS");

		attachDummy();	
	}
	//if(_DEBUG) cout << "Loaded: Grid Shader" << endl;
} 
