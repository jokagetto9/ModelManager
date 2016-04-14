//********************************* INITIALIZATION *********************************
#include "ModelManager.h"

//**EXTERNAL**
ModelManager* ModelManager::instance = 0;
ModelManager* M;

void ModelManager::		quit(){
	menuBO.quit();			//if(_DEBUG) cout << "Quit: Menu Shader" << endl;
	Shader::finalQuit();	
	delete instance; instance = NULL;
}

//********************************* EXTERNAL *********************************	

void billboard(){
	float modelview[16];
	glGetFloatv(GL_MODELVIEW_MATRIX , modelview);
	glLoadMatrixf(modelview);	//*/
}

string getZeros(int q, int d){
	stringstream ss("");
	if (q < 10000	&& d >= 4) ss << 0; 
	if (q < 1000	&& d >= 3) ss << 0;		
	if (q < 100		&& d >= 2) ss << 0;	
	if (q < 10		&& d >= 1) ss << 0;
	ss << q;
	return ss.str();
}

//********************************* LOAD PNG *********************************
GLuint loadTexture(char *fname, bool rep){
	//free();	//Get rid of preexisting texture

	SDL_Surface *png;
	png = IMG_Load(fname);
	if(!png) {printf("IMG_Load: %s\n", IMG_GetError()); SDL_Delay(5000); exit(1);}		// handle error
	else{	// handle error
	
 		SDL_PixelFormat* format = png->format;   

		GLenum textureForm = GL_RGBA;
		GLint  nOfColors;
		nOfColors = png->format->BytesPerPixel;
		if (nOfColors == 4){     // contains an alpha channel
			if (png->format->Rmask == 0x000000ff) textureForm = GL_RGBA;
			else if (nOfColors == 3) if (png->format->Rmask == 0x000000ff) textureForm = GL_RGB;    // no alpha channel
			else printf("warning: the image is not truecolor..  this will probably break\n");
		}
		
		//Binding to opengl
		GLuint texture;//, temp_fbo, temp_fbo_depth;
		glGenTextures(1, &texture);
		//glGenRenderbuffersEXT(1, &temp_fbo_depth);
		//glGenFramebuffersEXT(1, &temp_fbo);

		////////////////TEXTURE SECTION
		glBindTexture(GL_TEXTURE_2D, texture); //bind image to an ID
		
		glTexImage2D(GL_TEXTURE_2D, 0, nOfColors, png->w, png->h, 0, textureForm, GL_UNSIGNED_BYTE, png->pixels);

		if (rep){
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST); 
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST); 
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MAX_ANISOTROPY_EXT, 16);
		}else{
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR); //GL_NEAREST_MIPMAP_NEAREST
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST); //GL_NEAREST_MIPMAP_NEAREST
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MAX_ANISOTROPY_EXT, 16);
			//gluBuild2DMipmaps( GL_TEXTURE_2D, 4,  png->w, png->h, GL_RGBA, GL_UNSIGNED_BYTE, (Uint8 *)png->pixels);
		}
		SDL_FreeSurface(png);
		glBindTexture(GL_TEXTURE_2D, 0);//unbind	
		return texture;//storing ID information
	}
	return 0;//storing ID information
}


