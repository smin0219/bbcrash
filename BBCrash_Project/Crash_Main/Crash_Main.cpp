// Crash_Main.cpp : Defines the entry point for the application.
//

#include "stdafx.h"
#include "Crash_Main.h"

// Bugs GAME INCLUDES

#include "CrashButtonEventHandler.h"
#include "CrashKeyEventHandler.h"
#include "CrashMouseEventHandler.h"
#include "CrashTextGenerator.h"
#include "CrashStateMachine.h"

// GAME OBJECT INCLUDES
#include "Game.h"
#include "GameGraphics.h"
#include "GameState.h"
#include "GameStateMachine.h"
#include "Cursor.h"
#include "GameGUI.h"
#include "ScreenGUI.h"
#include "GameInput.h"
#include "GameOS.h"
#include "GameText.h"

// WINDOWS PLATFORM INCLUDES
#include "WindowsOS.h"
#include "WindowsInput.h"

// DIRECTX INCLUDES
#include "DirectXGraphics.h"
#include "DirectXTextureManager.h"
#define MAX_LOADSTRING 100

// Global Variables:
HINSTANCE hInst;                                // current instance
WCHAR szTitle[MAX_LOADSTRING];                  // The title bar text
WCHAR szWindowClass[MAX_LOADSTRING];            // the main window class name

void initCursor();
void initInGameGUI();
void initMainMenu();
void initSplashScreen();
void initLoadingLevel();
void initViewport();


	//Game* Game::singleton = 0;


int WINAPI WinMain(HINSTANCE hInstance,
	HINSTANCE hPrevInstance,
	LPSTR lpCmdLine,
	int nCmdShow)
{
	PlaySound(TEXT("data/music/music/main.wav"), NULL, SND_ASYNC);

	// CREATE AND START UP THE ENGINE
	Game *bb_crash_game = Game::getSingleton();
	bb_crash_game->startUp();

	// LOAD OUR CUSTOM TEXT GENERATOR, WHICH DETERMINES WHAT TEXT IS DRAWN EACH FRAME
	CrashTextGenerator *crashTextGenerator = new CrashTextGenerator();
	crashTextGenerator->startUp();



	// NOW LET'S LOAD THE GUI STUFF
	initViewport();
	initCursor();
	initSplashScreen();
	initMainMenu();
	initInGameGUI();
	initLoadingLevel();

	// SPECIFY WHO WILL HANDLE BUTTON EVENTS
	CrashButtonEventHandler *crashButtonHandler = new CrashButtonEventHandler();
	GameGUI *gui = bb_crash_game->getGUI();
	gui->registerButtonEventHandler((ButtonEventHandler*)crashButtonHandler);

	// SPECIFY WHO WILL HANDLE KEY EVENTS
	CrashKeyEventHandler *crashKeyHandler = new CrashKeyEventHandler();
	bb_crash_game->getInput()->registerKeyHandler((KeyEventHandler*)crashKeyHandler);


	// SPECIFY WHO WILL HANDLE MOUSE EVENTS NOT RELATED TO THE GUI
	CrashMouseEventHandler *crashMouseHandler = new CrashMouseEventHandler();
	bb_crash_game->getInput()->registerMouseHandler((MouseEventHandler*)crashMouseHandler);

	// MAKE THE GAME STATE MACHINE THAT WILL HELP 
	// IMPLEMENT SOME CUSTOM GAME RULES
	CrashStateMachine *bsm = new CrashStateMachine();
	GameStateManager *gsm = bb_crash_game->getGSM();
	gsm->setGameStateMachine(bsm);

	// START THE GAME LOOP
	bb_crash_game->runGameLoop();
	// AND RETURN
	return 0;
}
/*
initCursor - initializes a simple little cursor for the gui.
*/
void initCursor()
{
	Game *game = Game::getSingleton();
	GameGraphics *graphics = game->getGraphics();
	TextureManager *guiTextureManager = graphics->getGUITextureManager();

	// SETUP THE CURSOR
	vector<unsigned int> *imageIDs = new vector<unsigned int>();
	int imageID;

	// - LOAD THE RED ANT CURSOR IMAGE
	imageID = guiTextureManager->loadTexture(RED_ANT_CURSOR_PATH);
	imageIDs->push_back(imageID);

	// - LOAD THE BLACK ANT CURSOR IMAGE
	imageID = guiTextureManager->loadTexture(BLACK_ANT_CURSOR_PATH);
	imageIDs->push_back(imageID);

	// - NOW BUILD AND LOAD THE CURSOR
	Cursor *cursor = new Cursor();
	cursor->initCursor(imageIDs,
		*(imageIDs->begin()),
		0,
		0,
		0,
		255,
		32,
		32);
	GameGUI *gui = game->getGUI();
	gui->setCursor(cursor);
}

/*
initInGameGUI - initializes the game's in-game gui.
*/
void initInGameGUI()
{
	Game *game = Game::getSingleton();
	GameGraphics *graphics = game->getGraphics();
	TextureManager *guiTextureManager = graphics->getGUITextureManager();

	// NOW ADD THE IN-GAME GUI
	ScreenGUI *inGameGUI = new ScreenGUI();

	unsigned int imageID = guiTextureManager->loadTexture(IN_GAME_TOOLBAR_PATH);
	OverlayImage *imageToAdd = new OverlayImage();
	imageToAdd->alpha = 255;
	imageToAdd->width = 1366;
	imageToAdd->height = 64;
	imageToAdd->x = 0;
	imageToAdd->y = 0;
	imageToAdd->z = 0;
	imageToAdd->imageID = imageID;
	inGameGUI->addOverlayImage(imageToAdd);

	unsigned int normalTextureID = guiTextureManager->loadTexture(QUIT_IMAGE_PATH);
	unsigned int mouseOverTextureID = guiTextureManager->loadTexture(QUIT_IMAGE_MO_PATH);

	// INIT THE QUIT BUTTON
	Button *buttonToAdd = new Button();
	buttonToAdd->initButton(normalTextureID,
		mouseOverTextureID,
		0,
		0,
		0,
		255,
		200,
		100,
		false,
		QUIT_COMMAND);
	inGameGUI->addButton(buttonToAdd);

	// AND LET'S ADD OUR SCREENS
	GameGUI *gui = game->getGUI();
	gui->addScreenGUI(GS_GAME_IN_PROGRESS, inGameGUI);
}

/*
initMainMenu - initializes the game's main menu gui.
*/
void initMainMenu()
{
	Game *game = Game::getSingleton();
	GameGraphics *graphics = game->getGraphics();
	TextureManager *guiTextureManager = graphics->getGUITextureManager();

	// NOW LET'S LOAD A MAIN MENU GUI SCREEN
	ScreenGUI *mainMenuGUI = new ScreenGUI();
	unsigned int imageID = guiTextureManager->loadTexture(MAIN_MENU_PATH);
	OverlayImage *imageToAdd = new OverlayImage();
	imageToAdd->alpha = 200;
	imageToAdd->width = 1024;
	imageToAdd->height = 1024;
	imageToAdd->x = (graphics->getScreenWidth() / 2) - (imageToAdd->width / 2);
	imageToAdd->y = (graphics->getScreenHeight() / 2) - (imageToAdd->height / 2);
	imageToAdd->z = 0;
	imageToAdd->imageID = imageID;
	mainMenuGUI->addOverlayImage(imageToAdd);

	// AND LET'S ADD AN EXIT BUTTON
	Button *buttonToAdd = new Button();

	// - GET THE BUTTON COMMAND AND IMAGE IDs
	int normalTextureID = guiTextureManager->loadTexture(EXIT_IMAGE_PATH);
	int mouseOverTextureID = guiTextureManager->loadTexture(EXIT_IMAGE_MO_PATH);
	int buttonWidth = 200;
	int buttonHeight = 100;
	int buttonY = (graphics->getScreenHeight() * 70 / 100);
	int buttonPadding = 15;

	// - INIT THE EXIT BUTTON
	buttonToAdd->initButton(normalTextureID,
		mouseOverTextureID,
		(graphics->getScreenWidth() / 2) + buttonPadding,
		buttonY,
		0,
		255,
		buttonWidth,
		buttonHeight,
		false,
		EXIT_COMMAND);

	// AND NOW LOAD IT INTO A ScreenGUI
	mainMenuGUI->addButton(buttonToAdd);

	// AND LET'S ADD A START BUTTON
	buttonToAdd = new Button();

	// - GET THE BUTTON COMMAND AND IMAGE IDs

	normalTextureID = guiTextureManager->loadTexture(START_IMAGE_PATH);
	mouseOverTextureID = guiTextureManager->loadTexture(START_IMAGE_MO_PATH);

	// - INIT THE START BUTTON
	buttonToAdd->initButton(normalTextureID,
		mouseOverTextureID,
		(graphics->getScreenWidth() / 2) - buttonWidth - buttonPadding,
		buttonY,
		0,
		255,
		buttonWidth,
		buttonHeight,
		false,
		START_COMMAND);

	// AND NOW LOAD IT INTO A ScreenGUI
	mainMenuGUI->addButton(buttonToAdd);

	// AND LET'S ADD OUR SCREENS
	GameGUI *gui = game->getGUI();
	gui->addScreenGUI(GS_MAIN_MENU, mainMenuGUI);
}

void initLoadingLevel()
{
	Game *game = Game::getSingleton();
	GameGraphics *graphics = game->getGraphics();
	TextureManager *guiTextureManager = graphics->getGUITextureManager();

	// ADD A LOADING SCREEN GUI
	ScreenGUI *loadingLevelGUI = new ScreenGUI();

	// INIT THE QUIT BUTTON
	// NOW LET'S LOAD A MAIN MENU GUI SCREEN
	ScreenGUI *mainMenuGUI = new ScreenGUI();
	unsigned int imageID = guiTextureManager->loadTexture(LOADING_LEVEL_PATH);
	OverlayImage *imageToAdd = new OverlayImage();
	imageToAdd->alpha = 255;
	imageToAdd->width = 800;
	imageToAdd->height = 530;
	imageToAdd->x = (graphics->getScreenWidth() / 2) - (imageToAdd->width / 2);
	imageToAdd->y = (graphics->getScreenHeight() / 2) - (imageToAdd->height / 2);
	imageToAdd->z = 0;
	imageToAdd->imageID = imageID;
	loadingLevelGUI->addOverlayImage(imageToAdd);

	// AND REGISTER IT WITH THE GUI
	GameGUI *gui = game->getGUI();
	gui->addScreenGUI(GS_PRE_GAME, loadingLevelGUI);
	gui->addScreenGUI(GS_LOADING_LEVEL, loadingLevelGUI);
}

void initSplashScreen() {


	
	Game *game = Game::getSingleton();
	GameGraphics *graphics = game->getGraphics();
	TextureManager *guiTextureManager = graphics->getGUITextureManager();


	ScreenGUI *splashScreenGUI = new ScreenGUI();
	unsigned int normalTextureID = guiTextureManager->loadTexture(SPLASH_SCREEN_PATH);
	unsigned int mouseOverTextureID = normalTextureID;
	int imageWidth = 1300;
	int imageHeight = 768;
	Button *buttonToAdd = new Button();
	buttonToAdd->initButton(normalTextureID,
		mouseOverTextureID,
		(game->getGraphics()->getScreenWidth() / 2) - (imageWidth / 2),
		(game->getGraphics()->getScreenHeight() / 2) - (imageHeight / 2),
		0,
		255,
		imageWidth,
		imageHeight,
		false,
		GO_TO_MM_COMMAND);
	splashScreenGUI->addButton(buttonToAdd);

	// AND REGISTER IT WITH THE GUI
	GameGUI *gui = game->getGUI();
	gui->addScreenGUI(GS_SPLASH_SCREEN, splashScreenGUI);
	
	

}


/*
initViewport - initializes the game's viewport.
*/
void initViewport()
{
	Game *game = Game::getSingleton();
	GameGUI *gui = game->getGUI();
	GameGraphics *graphics = game->getGraphics();

	// AND NOW SPECIFY THE VIEWPORT SIZE AND LOCATION. NOTE THAT IN THIS EXAMPLE,
	// WE ARE PUTTING A TOOLBAR WITH A BUTTON ACCROSS THE NORTH OF THE APPLICATION.
	// THAT TOOLBAR HAS A HEIGHT OF 64 PIXELS, SO WE'LL MAKE THAT THE OFFSET FOR
	// THE VIEWPORT IN THE Y AXIS
	Viewport *viewport = gui->getViewport();

	int viewportWidth = graphics->getScreenWidth() - VIEWPORT_OFFSET_X;
	int viewportHeight = graphics->getScreenHeight() - VIEWPORT_OFFSET_Y;
	viewport->setViewportWidth(viewportWidth);
	viewport->setViewportHeight(viewportHeight);
	viewport->setToggleOffsetY(TOGGLE_OFFSET_Y);
}