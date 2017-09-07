/*
	Author: Richard McKenna
			Stony Brook University
			Computer Science Department

	Game.cpp

	See Game.h for a class description.
*/
#include "stdafx.h"
#include "GameClock.h"
#include "Game.h"
#include "GameStateManager.h"
#include "Button.h"
#include "Cursor.h"
#include "GameGUI.h"
#include "ScreenGUI.h"
#include "GameGraphics.h"
#include "GameInput.h"
#include "GameOS.h"
#include "DirectXGraphics.h"
#include "WindowsInput.h"
#include "WindowsOS.h"
#include "BBEngineConfigImporter.h"
//#include "mg\resources\importers\MGLevelImporter.h"
#include "EngineConfigProperties.h"
#include "GameResources.h"
#include "GameText.h"
#include "TextFileWriter.h"
#include "TextGenerator.h"

bool Game::isSingletonInstantiated = false;
Game* Game::singleton = 0;

Game* Game::getSingleton()
{
	if (!isSingletonInstantiated)
	{
		singleton = new Game();
		isSingletonInstantiated = true;
	}
	return singleton;
}

void Game::startUp()
{
	// THESE TWO GUYS GET SETUP BY ENGINE CONFIG SETTINGS SO
	// THEY HAVE TO ALREADY EXIST WHEN THOSE FILES GET LOADED
	gsm = new GameStateManager();
	gsm->startUp();

	// NEXT WE NEED OUR GAME RESOURCE MANAGER SINCE IT LOADS OTHER STUFF
	resources = new GameResources();
	resources->startUp();

	// NOW LET'S LOAD THE CONFIG FILE
	BBEngineConfigImporter *importer = (BBEngineConfigImporter*)resources->getEngineConfigImporter();
	importer->load(CONFIG_DIR, CONFIG_FILE);
	EngineConfigProperties props;

	// INIT THE GUI
	gui = new GameGUI();
	gui->startUp();

	// GameText MUST BE FIRST BECAUSE IT PROVIDES A MEANS
	// FOR READING PROPERTIES TEXT FILES, LIKE THE ENGINE CONFIG FILE
	text = new GameText();
	text->startUp();

	// NOW WE NEED A GameOS, BUT WHICH ONE DEPENDS ON THE CONFIG FILE
	wstring osProp = importer->getProperty(props.PROP_NAME_OS);
	if (osProp.compare(props.PROP_VALUE_WINDOWS) == 0)
	{
		os = new WindowsOS();
		input = new WindowsInput();
	}
	// ELSE WE COULD MAKE A DIFFERENT OS SUBSYSTEM
	os->startUp();
	input->startUp();

	// NOW WE NEED A GameGraphics, AS SPECIFIED BY THE CONFIG FILE
	wstring renderLibProp = importer->getProperty(props.PROP_NAME_RENDER_LIB);
	if (renderLibProp.compare(props.PROP_VALUE_DIRECTX) == 0)
	{
		graphics = new DirectXGraphics();
	}
	graphics->startUp();

	// NOW THE CLOCK FOR TIMING OUR GAME LOOP
	clock = new GameClock();
	clock->startUp();

	// WE'RE DONE USING THE CONFIG PROPERTIES, SO CLEAR THEM
	importer->unload();
}

/*
exitApp - this begins the process of shutting down, exiting the game loop
and then unloading all the resources.
*/
void Game::exitApp()
{
	gsm->shutDown();
}

/*
shutdown - This method starts the termination of the game application,
cascading shutdown proceedings through all the necessary classes, resulting
in the release of all game resources.
*/
void Game::shutDown()
{
	if (text)
		delete text;

	if (gui)
	{
		gui->shutDown();
		delete gui;
	}

	// MAKE SURE THE GAME LOOP ENDS AND THAT THE GSM CLEANS
	// UP ALL THE MEMORY IT IS USING
	if (gsm)
	{
		gsm->shutDown();
		delete gsm;
	}

	if (clock)
	{
		clock->shutDown();
		delete clock;
	}

	// CLEAR OUT AND RELEASE THE GPU
	if (graphics)
	{
		graphics->shutDown();
		delete graphics;
	}

	// RELEASE GAME CONTROLLERS IF NECESSARY
	if (input)
	{
		input->shutDown();
		delete input;
	}

	// WE MAY SHUTDOWN OTHER THINGS HERE LIKE SOUND & MUSIC
	// RESOURCES IN THE FUTURE
	// AND KILL THE WINDOW
	if (os)
	{
		os->shutDown();
		delete os;
	}

	// THIS IS LAST
	if (resources)
	{
		resources->shutDown();
		delete resources;
	}
}

/*
reloadAllDevices - Windows applications must cooperate
with other running applications, so when someone hits
ALT-TAB and switches from a full-screen game, it might
lose ownership of the graphics card. This method can
be called when a full-screen application retains ownership
of all necessary resources such that all necessary
data (like textures, sound, music, etc.) can be reloaded.
*/
void Game::reloadAllDevices()
{
	graphics->reloadGraphics();

	// WE MIGHT ADD MORE LATER
}

/*
runGameLoop - This is the game loop management method.
It runs continuously while the game is active. Once per
frame it instructs the major game objects to get
user input, record user input, update the GUI state,
update the sprites' states using AI and input, perform
collision detection and resolution (physics), render
the screen, etc.

This loop is timed such that everything is kept to a
consistent framerate, thus the game should run
consistently on all machines.
*/
void Game::runGameLoop()
{
	// FIRST PROFILE?
	bool firstTimeThroughLoop = true;

	// LET'S START THE TIMER FROM SCRATCH
	clock->resetTimer();

	// KEEP RENDERING UNTIL SOMEONE PULLS THE PLUG
	while (gsm->isAppActive())
	{
		if (gsm->isPreGame())
			gsm->goToLoadLevel();

		// MOVE ALONG WINDOWS MESSAGES, THIS ALLOWS
		// US TO GET USER INPUT
		os->processOSMessages();

		// GET USER INPUT AND UPDATE GAME, GUI, OR PLAYER
		// STATE OR WHATEVER IS NECESSARY
		input->processInput();

		// IT IS POSSIBLE THE USER REQUESTED A SHUTDOWN
		// OF THE APP, SO WE NEED TO CHECK AGAIN
		if (gsm->isAppActive())
		{
			// USE THE INPUT TO UPDATE THE GAME
			processGameData();

			// AND RENDER THE GAME
			graphics->renderGame();
		}
	}

	// GAME'S OVER SHUTDOWN THE GAME
	shutDown();
}

/*
processGameData - This method directs game logic to be
executed or not, depending on the game state, it addition
it triggers the building or render lists and game loop
timing each frame.
*/
void Game::processGameData()
{
	// WE ONLY PERFORM GAME LOGIC IF THE GAME
	// IS IN PROGRESS
	if (gsm->isGameInProgress() || gsm->isGameLevelLoading())
	{
		gsm->update();
	}

	// UPDATE TEXT
	TextGenerator *tg = text->getTextGenerator();
	tg->update();

	// BUILD THE RENDER LISTS
	graphics->fillRenderLists();

	// KEEP THE FRAME RATE CONSISTENT
	clock->timeGameLoop();
}

/*
quitGame - When called, this method will force the unloading of all game data
loaded for the current level and then return the user to the main menu.
*/
void Game::quitGame()
{
	// CLEAN UP ALL THE WORLD TEXTURES
	graphics->clearWorldTextures();

	// WE'RE GOING BACK TO THE MAIN MENU
	gsm->goToMainMenu();
}

/*
startUp - When called, this method will load the first level of the
game and start play. Note that one must make sure the currentLeve
*/
void Game::startGame()
{
	// AND UPDATE THE GAME STATE OF COURSE
	gsm->goToPreGame();
}
