#include "FontShader.h"

//********************************* MENU PROGRAM *********************************
const GLchar* fontVerShdr[] = {
	"#version 150 compatibility\n"
	"in vec2 offs; "
	"in vec4 texC; out vec2 t;"
	"uniform vec2 pos;"
	"void main() { "
	"	t = texC.xy + offs;"
	"	float x = pos.x + texC.z + offs.x;"
	"	float y = -(pos.y + offs.y + texC.w);"
	"	gl_Position = gl_ProjectionMatrix * vec4(x, y, 0.0, 1.0 );"
	"}"
};

const GLchar* fontFragShdr[] =	{
	"#version 150 compatibility\n"
    "uniform sampler2D tex;"
	"in vec2 t; "	
	"void main() { "
	//"	gl_FragColor = vec4(1,1,1,1);"
	"	gl_FragColor = texelFetch(tex, ivec2(t), 0);"
	"}"
};
//********************************* CONSTRUCTOR *********************************
FontShader::FontShader(){
	vbo = 0; 		ebo = 0;
	posAtt = -1; texAtt = -1;
	counter = 1;
	currBuffer = 3;

	
	clearAllBuffers();
	maxChars[0] = 0; maxChars[1] = 20;
	maxChars[2] = 100; maxChars[3] = 200;
	smallFont = false;

	prog = glCreateProgram();
	buildProgram(fontVerShdr, fontFragShdr, prog);
	
	texUni[0] = glGetUniformLocation(prog, "tex[0]");	//glUniform1i(texUni[0], 0);	
	posAtt = glGetUniformLocation( prog, "pos" ); 
	offsAtt = glGetAttribLocation( prog, "offs" );
	texAtt = glGetAttribLocation( prog, "texC" );

	buildFont(); 	build();
	
	//if(_DEBUG) cout << "Shaders Loaded" << endl;
}


void FontShader::quit(){
	
	glDeleteProgram( prog );
	glDeleteVertexArrays(1, &vao);		
	glDeleteBuffers(1, &vbo);
	
	//glDeleteBuffers(1, &ibo1);	
	//glDeleteBuffers(1, &ibo2);
	glDeleteBuffers(1, &ibo3);
	glDeleteTextures(1, &fontT);
	glDeleteTextures(1, &sfontT);
}

//********************************* FONT *********************************
const GLfloat charData[] = {	25, 26, 	25, 0,		0, 26,		0, 0};
const GLfloat smallCharData[] = {	16, 16, 	16, 0,		0, 16,		0, 0};

const int charWidth [] = { 
	6, 6, 8, 11, 11, 15, 18, 4, 7, 7, 
	10, 11, 5, 7, 6, 8, 11, 11, 11, 11, 
	11, 11, 11, 11, 11, 11, 6, 5, 11, 11,
	11, 9, 16, 15, 14, 15, 17, 13, 12, 16,
	17, 8, 7, 15, 13, 20, 17, 17, 13, 17, 
	15, 11, 14, 16, 15, 23, 15, 14, 13, 7, 
	8, 7, 11, 11, 7, 10, 12, 10, 12, 10, 
	7, 10, 12, 6, 6, 12, 6, 18, 12, 12, 
	12, 12, 9, 9, 8, 12, 11, 18, 12, 11, 10, 
};

const int smallCharWidth [] = { 
	4, 4, 5, 6,  6, 8, 9, 3,  4, 4, 6, 6,  4, 4, 4, 5, 
	6, 6, 7, 6,  6, 6, 6, 7,  7, 7, 4, 4,  6, 6, 6, 5, 
	9, 8, 8, 8,  9, 7, 7, 9,  9, 5, 5, 8,  7, 11, 9, 9, 
	7, 9, 8, 6,  8, 9, 8, 12, 8, 8, 7, 4,  5, 4, 6, 6, 
	4, 6, 7, 6,  7, 6, 4, 6,  7, 4, 4, 7,  4, 9, 7, 7,
	7, 7, 5, 5,  5, 7, 6, 9,  7, 6, 6, 5,  6, 5, 6
};

void FontShader::	buildFont(){	
	int ccol, crow;
	for (int i = 0; i < 91; i++){
		ccol = (i % 10) * 25;
		crow = i/10 * 26;		
		fontC[i] = glm::vec2(ccol, crow);
		ccol = (i % 16) * 16;
		crow = i/16 * 16;		
		smallFontC[i] = glm::vec2(ccol, crow);		
	}
}

void FontShader::loadMessage(){
	glBindVertexArray(vao);
	if (currBuffer == 1){
		glBindBuffer( GL_ARRAY_BUFFER, ibo1 ); 
		glBufferSubData( GL_ARRAY_BUFFER, 0, sizeof(glm::vec4) * chars[1], &message1[0]);
	}else if (currBuffer == 2){
		glBindBuffer( GL_ARRAY_BUFFER, ibo2 ); 
		glBufferSubData( GL_ARRAY_BUFFER, 0, sizeof(glm::vec4) * chars[2], &message2[0]);
	}else if (currBuffer == 3){
		glBindBuffer( GL_ARRAY_BUFFER, ibo3 ); 
		glBufferSubData( GL_ARRAY_BUFFER, 0, sizeof(glm::vec4) * chars[3], &message3[0]);
	}
	glVertexAttribPointer( texAtt, 4, GL_FLOAT, GL_FALSE, 4 * sizeof(GLfloat), (GLvoid*)0);
	
}


void FontShader::beginText(string s){	
 	int c = s.size();	
	if (c < currMax())
		convertString(s, 0, 0, 0);
}


void FontShader::appendText(string s, int w, int y){
	int size = s.size();
	if (currChars() + size < currMax()){	
		convertString(s, w, y, currChars());
	}
}


void FontShader::convertString(string s, int w, int y, int a){
	int c;
	int size = s.length();
	chars[currBuffer] = size + a;
	for (int i = 0; i < size; i++){
		c = s[i]-32;


		if (smallFont){
			if (currBuffer == 1)
				message1[a] = glm::vec4(smallFontC[c].x, smallFontC[c].y, w, y);
			else if (currBuffer == 2)
				message2[a] = glm::vec4(smallFontC[c].x, smallFontC[c].y, w, y);
			else if (currBuffer == 3)
				message3[a] = glm::vec4(smallFontC[c].x, smallFontC[c].y, w, y);
			w += smallCharWidth[c];
		} else{	
			if (currBuffer == 1)
				message1[a] = glm::vec4(fontC[c].x, fontC[c].y, w, y);
			else if (currBuffer == 2)
				message2[a] = glm::vec4(fontC[c].x, fontC[c].y, w, y);
			else if (currBuffer == 3)
				message3[a] = glm::vec4(fontC[c].x, fontC[c].y, w, y);
			w += charWidth[c];
		}
		a++;
	} 
}

void FontShader::changeFont(){
	glBindBuffer( GL_ARRAY_BUFFER, vbo );
	if (smallFont){
		smallFont = false;
		glBufferSubData( GL_ARRAY_BUFFER, 0, sizeof(charData), &charData);
	} else {
		smallFont = true;
		glBufferSubData( GL_ARRAY_BUFFER, 0, sizeof(charData), &smallCharData);
	}	
	//glVertexAttribPointer( offsAtt, 2, GL_FLOAT, GL_FALSE, 2 * sizeof(GLfloat), NULL );
}

//********************************* FONT  *********************************
void FontShader::build(){

	fontT = loadTexture("MENU/pesca.png", false);
	sfontT = loadTexture("MENU/pesca-small.png", false);
	
	//beginText("The quick brown fox jumps over the lazy dog.");
	//appendText("Because   stuff.", 500, 0);

	glGenVertexArrays(1, &vao);		glBindVertexArray(vao); //gen+bind vao
	//glGenBuffers( 1, &ebo );		glBindBuffer( GL_ELEMENT_ARRAY_BUFFER, ebo );
	glGenBuffers( 1, &vbo );		glBindBuffer( GL_ARRAY_BUFFER, vbo ); //gen+bind vbo
	glBindBuffer( GL_ELEMENT_ARRAY_BUFFER, lilebo );
	
	glEnableVertexAttribArray( offsAtt );
	glBufferData( GL_ARRAY_BUFFER, sizeof(charData), charData, GL_DYNAMIC_DRAW );
	glVertexAttribPointer( offsAtt, 2, GL_FLOAT, GL_FALSE, 2 * sizeof(GLfloat), NULL );

	glEnableVertexAttribArray( texAtt );	glVertexAttribDivisor(texAtt, 1);  //*/

	//glGenBuffers( 1, &ibo1);		glBindBuffer( GL_ARRAY_BUFFER, ibo1 ); 
	//glBufferData( GL_ARRAY_BUFFER, sizeof(glm::vec4) * maxChars[1], &message1[0], GL_STREAM_DRAW );	
	glGenBuffers( 1, &ibo2);		glBindBuffer( GL_ARRAY_BUFFER, ibo2 ); 
	glBufferData( GL_ARRAY_BUFFER, sizeof(glm::vec4) * maxChars[2], &message2[0], GL_STREAM_DRAW );	
	glGenBuffers( 1, &ibo3);		glBindBuffer( GL_ARRAY_BUFFER, ibo3 ); 
	glBufferData( GL_ARRAY_BUFFER, sizeof(glm::vec4) * maxChars[3], &message3[0], GL_STREAM_DRAW );	
	glGenBuffers( 1, &ibo3);		glBindBuffer( GL_ARRAY_BUFFER, ibo3 ); 
	glBufferData( GL_ARRAY_BUFFER, sizeof(glm::vec4) * maxChars[3], &message3[0], GL_STREAM_DRAW );	

	glVertexAttribPointer( texAtt, 4, GL_FLOAT, GL_FALSE, 4 * sizeof(GLfloat), (GLvoid*)0);
			
	//loadMessage();
	//changeFont();
} 


void FontShader::draw(int x, int y){
	/*glBindVertexArray(vao);

	if (currBuffer == 1)		glBindBuffer( GL_ARRAY_BUFFER, ibo1 ); 
	else if (currBuffer == 2)	glBindBuffer( GL_ARRAY_BUFFER, ibo2 ); 
	else if (currBuffer == 3)	glBindBuffer( GL_ARRAY_BUFFER, ibo3 ); 
	
	glVertexAttribPointer( texAtt, 4, GL_FLOAT, GL_FALSE, 4 * sizeof(GLfloat), (GLvoid*)0);
	//*/
	if (smallFont)	glBindTexture(GL_TEXTURE_2D, sfontT);
	else			glBindTexture(GL_TEXTURE_2D, fontT);
	glUniform2f(posAtt, x, -RES.z+y);	
	glDrawElementsInstanced(GL_TRIANGLES, 6, GL_UNSIGNED_INT, NULL, currChars());
	
	//if(counter >= 46)	glDrawElementsInstanced(GL_TRIANGLES, 6, GL_UNSIGNED_INT, NULL, (counter-44)/2);
	//if (counter < 132) counter++;
}



