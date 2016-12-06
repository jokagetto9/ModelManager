#include "GridShader.h"


GridShader::GridShader(){
 	prog = 0;	vbo = 0;	ebo = 0;
	posAtt = -1; texAtt = -1;
	initBufferObjects();
	build(); 
	scale = 1;
	grid = G4x4;
	//glUniform1i(texUni[0], 0);		
}

void GridShader::quit(){
	glDeleteProgram( prog );
	glDeleteVertexArrays(1, &vao);
	
}

void GridShader::use(){	
	glUseProgram( prog ); //Bind program	
	glBindVertexArray(vao);			
}


void GridShader::prepHero(){
	use();
	glBindTexture(GL_TEXTURE_2D, heroT);	
	glUniform2f(texScale, 2, 2);	
	glUniform1f(gridScale, 0.25);
	grid  = G4x4;
}

void GridShader::prep(ShaderProfile &sp){
	glBindTexture(GL_TEXTURE_2D, sp.tex);
	float g = 0.25;

	if (sp.g != grid){
		grid = sp.g;
		g = GRIDSCALE[grid];
		glUniform1f(gridScale, g);		
		if (sp.g == GMISC){}
	}

	scale = sp.scale;
	glUniform2f(texScale, scale, scale);
	glUniform2f(offset, 0, 0);		
	//glUniform1f(gridScale, g);		
}

void GridShader::offsetTexture(float x, float y){	
	glUniform2f(offset, x, y);		
}

void GridShader::drawGrid(ID index){
	if (grid == G4x4)
		glUniform2f(texIndex, G16__[index].x, G16__[index].z);	
	else if (grid == G2x2)
		glUniform2f(texIndex, G4__[index].x, G4__[index].z);
	else if (grid == G5x5){
		glUniform2f(texIndex, G25__[index].x, G25__[index].z);
	}else 
		glUniform2f(texIndex, 0, 0);
	glDrawElements( GL_TRIANGLES, 6, GL_UNSIGNED_INT, NULL );
}


void GridShader::changeGrid(GRIDTYPE g){



}
void GridShader::flip(int x, int y){
	if (x < 0 && y < 0)
		glUniform2f(texScale, -scale, -scale);
	else if (x < 0)
		glUniform2f(texScale, -scale, scale);
	else if (y < 0)
		glUniform2f(texScale, scale, -scale);
}

//********************************* QUAD16 PROGRAM *********************************
const GLchar* gridVerShdr[] = {
	"#version 150 compatibility\n"
	"in int p;"
	"out vec2 t;"
	"out vec4 vs;"
	"out vec4 dv;"
	"uniform vec2 index;"	
	"uniform vec2 scale;"
	"uniform vec2 offset;"
	"uniform float grid;"
	"void main() { "

	"	p;												"		
	"	float c = grid;									"
	"	float sx = scale.x * 4;							"		
	"	float sy = scale.y * 4;							"		
	"	vec2 pos;										"
	"	if (gl_VertexID == 0){							"
	"		pos.x = sx/2 ;	pos.y = 0;					"
	"		t.x = c*(index.x+1); t.y = c*(index.y+1);	"
	"	}else if (gl_VertexID == 1)	{					"
	"		pos.x = sx/2 ;	pos.y = sy;					"
	"		t.x = c*(index.x+1); t.y = c*index.y;		"
	"	}else if (gl_VertexID == 2)	{					"
	"		pos.x = -sx/2 ;	pos.y = 0;					"
	"		t.x = c*index.x; t.y = c*(index.y+1);		"
	"	}else if (gl_VertexID == 3)	{					"
	"		pos.x = -sx/2 ;	pos.y = sy;					"
	"		t.x = c*index.x; t.y = c*index.y;			"
	"	}												"		
	"	vec4 vPos = vec4( pos.x + offset.x, pos.y + offset.y, 0.0, 1.0 );				"

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

	glGenVertexArrays(1, &vao); 	glBindVertexArray(vao);
	glBindBuffer( GL_ELEMENT_ARRAY_BUFFER, lilebo );
	
	prog = glCreateProgram();
	if (buildProgram(gridVerShdr, gridFragShdr, prog)){			
		texIndex = glGetUniformLocation(prog, "index");	
		texUni[0] = glGetUniformLocation(prog, "tex");
		texScale = glGetUniformLocation(prog, "scale");
		gridScale = glGetUniformLocation(prog, "grid");
		offset = glGetUniformLocation(prog, "offset");
		attachDummy();	
	}
	//if(_DEBUG) cout << "Loaded: Grid Shader" << endl;
} 
