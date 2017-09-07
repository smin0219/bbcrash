/*	
	Author: Richard McKenna
			Stony Brook University
			Computer Science Department

	GameStateManager.h

	This class manages the static data for the game level being
	used. This means all game backgrounds, which are stored and
	manipulated in WorldLayer objects. A given level can have
	a game background rendered using multiple layers, some which
	can be tiled, others that can be sparse, and others that
	can be isometric.

	This class stores these layers and ensures they are rendered
	in the proper order, low index to high. Layers that need to
	be drawn first (the back-most layer), should be added first.
*/
#pragma once
#include "stdafx.h"
#include "RenderList.h"
#include "GameState.h"
#include "Physics.h"
#include "SpriteManager.h"
#include "GameStateMachine.h"
#include "World.h"
#include "WorldLayer.h"

class Game;

static const int NO_LEVEL_LOADED = -1;

class GameStateManager
{
private:
	// THE CURRENT GAME STATE
	GameState currentGameState;

	// THE CURRENT LEVEL IS THE ONE CURRENTLY BEING PLAYED. NOTE THAT IF
	// THE CURRENT LEVEL IS 0, THEN IT MEANS THERE IS NO ACTIVE LEVEL LOADED,
	// LIKE WHEN WE'RE AT THE MAIN MENU
	unsigned int currentLevelIndex;

	// THESE VECTORS STORE THE NAMES OF EACH LEVEL AND THE RELATIVE
	// PATH AND FILE NAME OF EACH DATA INPUT FILE FOR ALL GAME LEVELS. 
	// NOTE THAT WE'LL LOAD THESE VECTORS WITH THIS DATA WHEN THE GAME STARTS UP, 
	// BUT WE'LL ONLY LOAD THE LEVELS INTO THE GAME WORLD AS EACH LEVEL IS PLAYED
	// NOTE THAT THE LEVEL NAME AT INDEX i IN THE FIRST VECTOR CORRESPONDS
	// TO THE PATH AND FILE NAME AT INDEX i IN THE SECOND ONE
	vector<wstring> levelNames;
	vector<wstring> levelDirs;
	vector<wstring> levelFiles;

	// FOR MANAGING STATIC GAME WORLD DATA, i.e. BACKGROUND IMAGES,
	// TILES, PLATFORMS, etc. BASICALLY THINGS THAT ARE NOT ANIMATED
	// AND DO NOT MOVE
	World world;

	// FOR MANAGING DYNAMIC GAME OBJECTS FOR CURRENT LEVEL
	// NOTE THAT WE CALL THE DYNAMIC OBJECTS "SPRITES"
	SpriteManager *spriteManager;

	// THIS IS AI SYSTEM THAT MANAGES GAME STATE TRANSITIONS
	GameStateMachine *gameStateMachine;

	// FOR DOING ALL COLLISION DETECTION AND RESOLUTION
	Physics			physics;

public:
	// INLINED ACCESSOR METHODS
	GameState			getCurrentGameState()	{ return currentGameState;				}
	unsigned int		getCurrentLevelIndex()	{ return currentLevelIndex;				}
	unsigned int		getNumLevels()			{ return levelNames.size();				}
	Physics*			getPhysics()			{ return &physics;						}
	SpriteManager*		getSpriteManager()		{ return spriteManager;					}
	World*				getWorld()				{ return &world;						}
	GameStateMachine*	getGameStateMachine()	{ return gameStateMachine; }
	wstring				getCurrentLevelName()	{ return levelNames[currentLevelIndex];	}

	// INLINED MUTATOR METHOD
	void setGameStateMachine(GameStateMachine *initBotStateManager)
	{
		gameStateMachine = initBotStateManager;
	}

	// METHODS FOR TESTING THE CURRENT GAME STATE
	bool			isAppActive();
	bool			isAtSplashScreen();
	bool			isGameInProgress();
	bool			isGameLevelLoading();
	bool			isPreGame();
	bool			isWorldRenderable();

	// METHODS FOR TRANSITIONING TO OTHER GAME STATES
	void			goToGame();
	void			goToLoadLevel();
	void			goToMainMenu();
	void			goToPreGame();

	// METHODS DEFINED in GameStateManager.cpp
	GameStateManager();
	~GameStateManager();
	void			addGameRenderItemsToRenderList();
	void			addLevel(wstring levelToAddName, wstring levelToAddDir, wstring levelToAddFile);
	unsigned int	getLevelNum(wstring levelName);
	void			loadLevel(unsigned int levelNum);
	void			loadLevel(wstring levelName);
	void			loadCurrentLevel();
	void			loadNextLevel();
	void			unloadCurrentLevel();
	void			update();
	void			startUp();
	void			shutDown();
};