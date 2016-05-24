#ifndef ENVIRONMENT_H
#define ENVIRONMENT_H


#include "../BaseEngine/BaseGameState.h"
#include "ModelManager.h"


//********************************* CONSTANTS *********************************


//********************************* INITIALIZATION *********************************



class Environment {
public:
	// Constructor
	Environment::		Environment();
	void Environment::	init();
	void Environment::	initFog(bool init);
	
	void Environment::	initSky();

	// view functions

	void Environment::	draw();			// draw update

	// Cycle updates 
	//void Environment::	update(Biome b);	
	void Environment::	refreshView();				// update fog and view matrix
	void Environment::	updateFog();	

	void Environment::	physUpdate(float physDelta);	// physics update
	void Environment::	rapidUpdate(float aiDelta);		// ai update
	void Environment::	slowaiUpdate();					// slow ai update
	void Environment::	optimize();			

/*/ Purpose: 
Side Effects:  
Triggers: 
/*/



//************************************************** MEMBERS ***************************************************
	

				// interpolate fog values
		
		glm::vec3 skyColour;
		glm::vec3 fogColour;

		float fogColor[4];
		float targetFog;

		float targetFogD, targetFogS;
		//Biome curBio;

		//vector<Nub> growList;
		//vector<Nub> bloomList;


			
};
#endif