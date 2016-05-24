//********************************* INITIALIZATION *********************************
#include "Environment.h"
Environment::Environment(){}	// dummy constructor

// Actual init - create actors
void Environment::init(){	
	initFog(true);		// create fog	 
}


void Environment::initFog(bool init){
	//fogColor[0] = 0.18; fogColor[1] = 0.75;
	//fogColor[2] = 1; fogColor[3] = 1;
	fogColor[0] = 0.5; fogColor[1] = 1;
	fogColor[2] = 1; fogColor[3] = 1;
	targetFog = 1;
	//M->fogD = FOG_D;	
	//M->adjustFog(0);
	targetFogD = 500;
	targetFogS = 150;
	glEnable(GL_FOG);				//enable
	glClearColor(0, 0, 0, 1.0);		//initialise background color

	glFogi(GL_FOG_MODE, GL_LINEAR);			//linear mode?
	glHint(GL_FOG_HINT, GL_DONT_CARE);		//???

	glFogfv(GL_FOG_COLOR, fogColor);		
	glFogf(GL_FOG_START, 0);				//fog start <- follow the user 
	glFogf(GL_FOG_END, 1000);			//fog end
	//glFogi(GL_FOG_COORD_SRC, GL_FOG_COORDINATE);
	//glFogCoordf(5);
	glFogi(GL_FOG_COORD_SRC, GL_FRAGMENT_DEPTH);//?
	//*/
}




//********************************* CYCLE UPDATES *********************************


// AI
void Environment::rapidUpdate(float aiDelta){
	
}



void Environment::refreshView(){

	glClearColor(skyColour.r, skyColour.g, skyColour.b, 1);		//background
	glFogfv(GL_FOG_COLOR, fogColor);
	glFogf(GL_FOG_START, targetFogS);
	
}

