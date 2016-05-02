//********************************* INITIALIZATION *********************************
#include "Animation.h"

Animation::Animation(){
	type = 0;
	index = 0;
	tpf = 100;
	if (tpf > 0) tick = rand() % tpf;
}

void Animation::init(AnimType t){
	type = t;
	if (tpf > 0) tick = rand() % tpf;

	if (type == CYCLIC){
		
		tpf = 100;
		tick = 0;
		index = 4;
	}
}

//********************************* DRAW *********************************

void Animation::draw(float frameDelta){
	//DISABLED
	//int it = frameTick(frameDelta) + 4;
	//glBindTexture(GL_TEXTURE_2D, M->gridBO.laserPalmT);
	//if (it >= 0 && it < 16) M->gridBO.drawx16(it);
}


void Animation::draw(glm::vec3 s, float camTheta, float frameDelta){
	int it = 0; 
	if (type != CYCLIC){		
		int tweak = 0; 
		int dir = getThetaIndex(camTheta);
		if (notZero(s)) tweak = frameTick(frameDelta);

		it = dir + tweak;
	}
	if (it >= 0 && it < 16) M->gridBO.drawx16(it);
	
}



// cycle looping animations
int Animation::frameTick( float frameDelta){
	if (type == WALK8){
		tick += 0.2 * frameDelta;
		if (tick >= tpf )tick -= tpf;
		if (tick >= tpf/2)	{ glTranslatef(0, 0.5, 0);   return 1;	}
		else if (tick >= tpf*3/4 && tick < tpf)	return 1;
	}
	else if (type == WALK12){
		tick += 0.1 * frameDelta;
		if (tick >= tpf )tick -= tpf;
		if (tick >= tpf/4 && tick < tpf/2)	return - 1;	
		else if (tick >= tpf*3/4 && tick < tpf)	return 1;
	}	
	else if (type == CYCLIC){
		tick += 0.3 * frameDelta;
		if (tick >= tpf )tick -= tpf;
		int i = tick/(tpf/index);
		//int i = (int)tick % index; 
		return i;
	}
	return 0;
}
const int WALK8INDEXES[] = {4, 8, 12, 0};
const int WALK12INDEXES[] = {5, 9, 13, 1};
	
//enum Oriet {LEFT, RIGHT, UP, DOWN,  UL, UR, DL, DR}; 
int Animation::getThetaIndex(float theta){	

	loop360(theta);
	Oriet o = DOWN;
	if (theta <= 135 && theta > 45)			o = LEFT;	//left
	else if (theta <= 225 && theta > 135)	o = UP;	//forward 
	else if (theta <= 315 && theta > 225)	o = RIGHT;	//right
	else if (theta <= 45 && theta >= 0 || theta < 360 && theta > 315) o = DOWN;//backward

	if (type == WALK8) return WALK8INDEXES[o];	
	if (type == WALK12) return WALK12INDEXES[o];
	return 1;
}



void Animation::setTPF(int s){	tpf = s;}
