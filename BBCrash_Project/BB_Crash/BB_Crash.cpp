// BB_Crash.cpp : Defines the entry point for the application.
//

#include "stdafx.h"
#include "BB_Crash.h"


#include "stdafx.h"

// Bugs GAME INCLUDES
//#include "bugs\BugsApp.h"

// GAME OBJECT INCLUDES
#include "Game.h"
//#include "GameGraphics.h"
#include "GameState.h"
#include "GameStateMachine.h"
//#include "mg\gui\Cursor.h"
//#include "mg\gui\GameGUI.h"
//#include "mg\gui\ScreenGUI.h"
//#include "GameInput.h"
#include "GameOS.h"
//#include "mg\text\GameText.h"

// WINDOWS PLATFORM INCLUDES
#include "WindowsOS.h"
#include "WindowsInput.h"

// DIRECTX INCLUDES
#include "DirectXGraphics.h"
#include "DirectXTextureManager.h"

#define MAX_LOADSTRING 100

//void initMainMenu();
void initSplashScreen();


int APIENTRY wWinMain(_In_ HINSTANCE hInstance,
                     _In_opt_ HINSTANCE hPrevInstance,
                     _In_ LPWSTR    lpCmdLine,
                     _In_ int       nCmdShow)
{
   
	initSplashScreen();
	//initMainMenu();
    return (int) 0;
}


void initSplashScreen()
{
	Game *game = Game::getSingleton();
	GameGraphics *graphics = game->getGraphics();
	TextureManager *guiTextureManager = graphics->getGUITextureManager();

}
