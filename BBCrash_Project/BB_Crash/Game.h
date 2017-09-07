/*	
	Author: Richard McKenna
			Stony Brook University
			Computer Science Department

	Game.h

	The class is the central object of the game	application. It's a singleton
	so it is shared by all other game engine objects. It plays three important roles:

	1) It manages all major game subsystems like for dealing with graphics cards and input
	devices. The objects can be accessed via inlined public methods, i.e. getGraphics(), 
	getInput(), getClock(), etc.

	2) It initializes all subsystems in the proper order, using the settings found in
	the engine config file.

	3) It runs the game loop, calling the appropriate methods in the other major objects as needed. The
	runGameLoop method iterates once per frame, invoking all necessary methods needed each frame to run the game.

	NOTE: we have deliberately avoided making most classes technology specific. We would like to be able to change
	the way the graphics are rendered (i.e. DirectX or OpenGL) without having to change this or most other
	classes, but rather by simply swapping out the graphics object. Note that this class will construct
	the appropriate platform-specific sub-system based on what settings it finds in the config file.
*/

#pragma once

// PREPROCESSOR INCLUDE STATEMENTS
#include "stdafx.h"
#include "GameState.h"

// FORWARD DECLARATIONS OF CLASSES USED BY GAME
class GameClock;
class GameGraphics;
class GameInput;
class GameOS;
class GameResources;
class GameTimer;
class GameStateManager;
class GameGUI;
class GameText;

static const float PI = 3.1415926535897932384626433f;
static const wstring CONFIG_DIR = L"data/";

//static const wstring CONFIG_DIR = L"C:/Users/Tianran/Desktop/BBCrash_Project/Apps/data/";
static const wstring CONFIG_FILE = L"bb_engine.config";

class Game
{
private:
	// SINGLETON DESIGN PATTERN STUFF
	static bool isSingletonInstantiated;
	static Game* singleton;

	// BECAUSE THIS IS A SINGLETON WE DON'T DO ANYTHING IN THESE
	Game() {}
	~Game() {}

	// ANYTHING STARTING WITH Game IS AN ENGINE SUBSYSTEM. NOTE THAT
	// ALL THE SUBSYSTEMS ARE CONSTRUCTED VIA THIS SINGLETON'S startUp
	// AND THEN THEY THEMSELVES ARE INITIALIZED VIA startUp, CAREFULLY
	// DONE IN THE PROPER ORDER
	GameClock			*clock;
	GameStateManager	*gsm;
	GameGUI				*gui;
	GameText			*text;
	GameResources		*resources;

	// THESE GAME OBJECTS ALL REQUIRE CUSTOM DEFINITIONS AS SPECIFIED
	// IN THE GAME CONFIGURATION FILE	
	GameGraphics		*graphics;
	GameInput			*input;
	GameOS				*os;

public:
	// SINGLETON DESIGN PATTERN STUFF
	static Game* getSingleton();

	// INLINED ACCESSOR METHODS - THE REAL THINGS
	GameClock*			getClock()				{ return clock;								}	
	GameStateManager*	getGSM()				{ return gsm;								}
	GameGUI*			getGUI()				{ return gui;								}
	GameResources*		getResources()			{ return resources;							}
	GameText*			getText()				{ return text;								}

	// INLINED ACCESSOR METHODS - ACTUALLY SUB-CLASSES
	GameGraphics*		getGraphics()			{ return graphics;							}
	GameInput*			getInput()				{ return input;								}
	GameOS*				getOS()					{ return os;								}

	// METHODS DEFINED IN Game.cpp
	void	exitApp();
	void	processGameData();
	void	quitGame();
	void	reloadAllDevices();
	void	runGameLoop();
	void	startGame();
	void	startUp();
	void	shutDown();
};


