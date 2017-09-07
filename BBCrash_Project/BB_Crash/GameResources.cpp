#include "stdafx.h"
#include "Game.h"
#include "GameStateManager.h"
#include "World.h"
#include "GameResources.h"

#include "BBEngineConfigImporter.h"
#include "BBLevelImporter.h"
#include "PoseurSpriteTypeImporter.h"
#include "TMXMapImporter.h"
#include "tinyxml\tinystr.h";
#include "tinyxml\tinyxml.h";



void GameResources::startUp()
{

	engineConfigImporter = new BBEngineConfigImporter();
	levelImporter = new BBLevelImporter();
	mapImporter = new TMXMapImporter();
	spriteTypeImporter = new PoseurSpriteTypeImporter();
	
}

void GameResources::shutDown()
{

	/*
		delete engineConfigImporter;
	delete spriteTypeImporter;
	delete mapImporter;
	delete levelImporter;
	
	*/
}