#include "stdafx.h"
#include "CrashMouseEventHandler.h"
#include "Game.h"
#include "SpriteManager.h"
#include "GameStateManager.h"
#include "Viewport.h"
void CrashMouseEventHandler::handleMousePressEvent(int mouseX, int mouseY)
{


	Game *game = Game::getSingleton();


	if (game->getGSM()->isGameInProgress())
	{
		Viewport *viewport = game->getGUI()->getViewport();
		// DETERMINE WHERE ON THE MAP WE HAVE CLICKED
		int worldCoordinateX = mouseX + viewport->getViewportX();
		int worldCoordinateY = mouseY + viewport->getViewportY();

		// CHECK TO SEE IF THE USER HAS CLICKED ON A SPRITE
		GameStateManager *gsm = game->getGSM();
		SpriteManager *spriteManager = gsm->getSpriteManager();
		BotRecycler *botRecycler = spriteManager->getBotRecycler();
		list<Bot*>::iterator botIterator = spriteManager->getBotsIterator();
		list<Bot*>::iterator endBotIterator = spriteManager->getEndOfBotsIterator();
		bool found = false;


		//AnimatedSprite *player = spriteManager->getPlayer();



		while ((botIterator != endBotIterator) && !found)
		{
			Bot *bot = (*botIterator);
			PhysicalProperties *pp = bot->getPhysicalProperties();
			AnimatedSpriteType *ast = bot->getSpriteType();
		
			//bot->getOrthographic()->mapPath()
			
			//if ((worldCoordinateX > pp->getX()) &&
				//(worldCoordinateY > pp->getY()) &&
				//(worldCoordinateX < (pp->getX() + ast->getTextureWidth())) &&
				//(worldCoordinateY < (pp->getY() + ast->getTextureHeight()))) {
				// BOT FOUND THAT'S BEEN CLICKED ON
				//bot->setBotState(BotState::DYING);
				//bot->setCurrentState(L"DYING");
				//found = false;
			//}
			botIterator++;
		}
		
	}
}

void CrashMouseEventHandler::handleMouseMoveEvent(int mouseX, int mouseY)
{
	Game *game = Game::getSingleton();

	// DETERMINE WHAT THE PATHFINDING GRID CELL
	// IS THAT THE MOUSE CURRENTLY IS ABOVE
	if (game->getGSM()->isGameInProgress())
	{
		// IF YOU LIKE YOU COULD DO SOME MOUSE OVER DEBUGGING STUFF HERE
	}
}