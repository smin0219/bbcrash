#pragma once

#include "stdafx.h"
#include "BBImporter.h"
#include "xmlfi\XMLFileImporter.h"

class GameResources
{
private:	
	// THIS IS A SETUP FILE FOR LOADING THE GUI
	wstring guiFile;



	BBImporter *engineConfigImporter;


	
	// THESE IMPORTERS ARE FOR LOADING GAME & LEVEL DATA

	BBImporter *levelImporter;
	BBImporter *mapImporter;
	BBImporter *spriteTypeImporter;
	
	
public:
	// NOTHING TO INITIALIZE, WE'LL LEAVE THE DEFAULT CONSTRUCTION/DESTRUCTION OF THE
	// IMPORTERS UP TO THE startUp/shutDown METHODS
	GameResources()		{}
	~GameResources()	{}

	

	
	// INLINED ACCESSOR METHODS
	BBImporter*		getEngineConfigImporter()	{ return engineConfigImporter;	}
	


	BBImporter*		getLevelImporter()			{ return levelImporter;			}
	BBImporter*		getMapImporter()			{ return mapImporter;			}
	BBImporter*		getSpriteTypeImporter()		{ return spriteTypeImporter;	}
	
	wstring			getGUIFile()				{ return guiFile;				}

	

	/*
	
	// INLINED MUTATOR METHODS
	void setEngineConfigImporter(MGImporter *initEngineConfigImporter)
	{
		engineConfigImporter = initEngineConfigImporter;
	}
	void setLevelImporter(MGImporter *initLevelImporter)
	{
		levelImporter = initLevelImporter;
	}
	void setMapImporter(MGImporter *initMapImporter)
	{
		mapImporter = initMapImporter;
	}
	void setSpriteTypeImporter(MGImporter *initSpriteTypeImporter)
	{
		spriteTypeImporter = initSpriteTypeImporter;
	}
	
	*/
	void setGuiFile(wstring initGuiFile)
	{
		guiFile = initGuiFile;
	}

	void startUp();
	void shutDown();
};
