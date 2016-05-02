#ifndef ANIMATION_H
#define ANIMATION_H


#include "Camera.h"
#include "Shaders\ModelManager.h"
//********************************* CONSTANTS *********************************
enum AnimType { CYCLIC, WALK8, WALK12};  


//********************************* EXTERNAL *********************************


//********************************* INITIALIZATION *********************************

class Animation{
public:

	Animation::Animation();
	//Animation:: Node(_sprite);
/*/ Purpose: default constructor /*/

	void Animation::init(AnimType t);
/*/ Purpose: init inherited members  
Side Effects: init tpf, theta - facing direction -> 0 = SOUTH
/*/
	
//********************************* DRAW *********************************
	
	void Animation::	draw(float frameDelta);
	void Animation::	draw(glm::vec3 s, float camTheta, float frameDelta);
/*/ Purpose: draw sprite -> changes by theta and tpf
Parameter(s): camTheta -> camera theta, frameDelta -> frameTick adjustment
Precondition(s): Once per frame
Triggers: getDirection, if moving -> frameTick 
/*/

	int Animation::	frameTick(  float frameDelta);
/*/ Purpose: track repeating animation
Parameter(s): frameDelta -> frameTick adjustment
Precondition(s): tick and tpf are initialized
Returns: -1, 0, 1, 0...
Side Effects: tick increases by frameDelta
/*/

	int Animation::	getThetaIndex(float theta);
/*/ Purpose: get frame index for sprite using theta
Parameter(s): theta - facing -> 0 - facing away 
Precondition(s): theta must account for camera position
Returns: 5 -> Left, 13 -> Down, 9 -> Right, 1 -> Up
Triggers: loop360 
/*/


	int type;
	int index;
	float tick; int tpf;


	void Animation::setTPF(int s);

};
#endif