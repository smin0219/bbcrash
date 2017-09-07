/*
Author: Richard McKenna
Stony Brook University
Computer Science Department

BugsKeyEventHandler.cpp

See BugsKeyEventHandler.h for a class description.
*/

#include "stdafx.h"
#include "Crash_Main.h"
#include "CrashKeyEventHandler.h"
#include "GameClock.h"
#include "Game.h"
#include "WStringTable.h"
#include "GameGraphics.h"
#include "Physics.h"
#include "PhysicalProperties.h"
#include "AnimatedSprite.h"
#include "GameState.h"
#include "GameStateManager.h"
#include "Cursor.h"
#include "GameGUI.h"
#include "GameInput.h"

/*
handleKeyEvent - this method handles all keyboard interactions. Note that every frame this method
gets called and it can respond to key interactions in any custom way. Ask the GameInput class for
key states since the last frame, which can allow us to respond to key presses, including when keys
are held down for multiple frames.
*/
void CrashKeyEventHandler::handleKeyEvents()
{

	Game *game = Game::getSingleton();

	// WE CAN QUERY INPUT TO SEE WHAT WAS PRESSED
	GameInput *input = game->getInput();

	// LET'S GET THE PLAYER'S PHYSICAL PROPERTIES, IN CASE WE WANT TO CHANGE THEM
	GameStateManager *gsm = game->getGSM();
	AnimatedSprite *player = gsm->getSpriteManager()->getPlayer();
	AnimatedSprite *balls = gsm->getSpriteManager()->getBalls();


	PhysicalProperties *pl = player->getPhysicalProperties();
	PhysicalProperties *bl = balls->getPhysicalProperties();
	Viewport *viewport = game->getGUI()->getViewport();

	// IF THE GAME IS IN PROGRESS
	if (gsm->isGameInProgress())
	{
		if (input->isKeyDownForFirstTime(P_KEY))
		{
			gsm->getPhysics()->togglePhysics();

		}

		if (input->isKeyDownForFirstTime(M_KEY))
		{
			PlaySound(TEXT("data/music/music/back.wav"), NULL, SND_ASYNC);

		}
		

		if (input->isKeyDownForFirstTime(N_KEY))
		{
			PlaySound(TEXT("data/music/music/win.wav"), NULL, SND_ASYNC);
		
			gsm->loadNextLevel();

		}

		if (input->isKeyDownForFirstTime(T_KEY))
		{
			gsm->getPhysics()->activateForSingleUpdate();
		}
		if (input->isKeyDownForFirstTime(I_KEY))
		{
			viewport->toggleDebugView();
			game->getGraphics()->toggleDebugTextShouldBeRendered();
		}
		if (input->isKeyDownForFirstTime(W_KEY)) {

			//gsm->getPhysics()->togglePhysics();
			pl->setVelocity(0.0f, -3.0f);

		}


		if (input->isKeyDownForFirstTime(S_KEY)) {

			//gsm->getPhysics()->togglePhysics();
			pl->setVelocity(0.0f, 3.0f);

			
		}


		if (input->isKeyDownForFirstTime(A_KEY)) {

			//gsm->getPhysics()->togglePhysics();
			pl->setVelocity(-3.0f, 0.0f);


		}
		if (input->isKeyDownForFirstTime(D_KEY)) {

			//gsm->getPhysics()->togglePhysics();
			pl->setVelocity(3.0f, 0.0f);


		}

		if (input->isKeyDownForFirstTime(J_KEY)) {

			//gsm->getPhysics()->togglePhysics();
			PlaySound(TEXT("data/music/music/detonation.wav"), NULL, SND_ASYNC);

			bl->setPosition(pl->getX(), pl->getY());


		}



		bool viewportMoved = false;
		float viewportVx = 0.0f;
		float viewportVy = 0.0f;
		/*
		if (input->isKeyDown(UP_KEY))
		{
			viewportVy -= MAX_VIEWPORT_AXIS_VELOCITY;
			viewportMoved = true;
		}
		if (input->isKeyDown(DOWN_KEY))
		{
			viewportVy += MAX_VIEWPORT_AXIS_VELOCITY;
			viewportMoved = true;
		}
		if (input->isKeyDown(LEFT_KEY))
		{
			viewportVx -= MAX_VIEWPORT_AXIS_VELOCITY;
			viewportMoved = true;
		}
		if (input->isKeyDown(RIGHT_KEY))
		{
			viewportVx += MAX_VIEWPORT_AXIS_VELOCITY;
			viewportMoved = true;
		}
		if (viewportMoved)
			viewport->moveViewport((int)floor(viewportVx + 0.5f), (int)floor(viewportVy + 0.5f), game->getGSM()->getWorld()->getWorldWidth(), game->getGSM()->getWorld()->getWorldHeight());


	}

	// 0X43 is HEX FOR THE 'C' VIRTUAL KEY
	// THIS CHANGES THE CURSOR IMAGE
	if ((input->isKeyDownForFirstTime(C_KEY))
		&& input->isKeyDown(VK_SHIFT))
	{
		Cursor *cursor = game->getGUI()->getCursor();
		unsigned int id = cursor->getActiveCursorID();
		id++;
		if (id == cursor->getNumCursorIDs())
			id = 0;
		cursor->setActiveCursorID(id);
	}

	// LET'S MESS WITH THE TARGET FRAME RATE IF THE USER PRESSES THE HOME OR END KEYS
	GameClock *clock = game->getClock();
	int fps = clock->getTargetFPS();

	// THIS SPEEDS UP OUR GAME LOOP AND THUS THE GAME, NOTE THAT WE COULD ALTERNATIVELY SCALE
	// DOWN THE GAME LOGIC (LIKE ALL VELOCITIES) AS WE SPEED UP THE GAME. THAT COULD PROVIDE
	// A BETTER PLAYER EXPERIENCE
	if (input->isKeyDown(VK_HOME) && (fps < MAX_FPS))
		clock->setTargetFPS(fps + FPS_INC);

	// THIS SLOWS DOWN OUR GAME LOOP, BUT WILL NOT GO BELOW 5 FRAMES PER SECOND
	else if (input->isKeyDown(VK_END) && (fps > MIN_FPS))
		clock->setTargetFPS(fps - FPS_INC);

		*/
	}
}
