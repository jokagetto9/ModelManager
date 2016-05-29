#ifndef MODELMANAGER_H
#define MODELMANAGER_H

#include "Shaders/GridShader.h"
#include "Shaders/TileShader.h"
#include "Shaders/MenuShader.h"
#include "Shaders/CursorShader.h"
#include "Shaders/FontShader.h"
//********************************* CONSTANTS *********************************
//********************************* EXTERNAL *********************************
//********************************* INITIALIZATION *********************************
class ModelManager {
public:
	//singleton
	static ModelManager* ModelManager::I(){
		if(instance == 0){
			instance = new ModelManager();
			return instance;
		}return instance;	}
	void ModelManager::quit();

//************************************************** MEMBERS ***************************************************
		
	//QShader qBO;
	GridShader gridBO;
	TileShader tileBO;
	//TerrainShader terrainBO;
	//TerrainShader2 terrain2BO;
	//CrossRoadShader roadBO;
	//ObjectShader objBO;
	MenuShader menuBO;
	CursorShader cursorBO;
	//IconShader iconBO;
	FontShader fontBO;
	
private:
	ModelManager::ModelManager(){}
	static ModelManager* instance ;
};

extern ModelManager* M;

#endif