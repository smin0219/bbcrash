/*
	Author: Richard McKenna
			Stony Brook University
			Computer Science Department

	Physics.cpp

	See Physics.h for a class description.
*/

#include "stdafx.h"
#include "AnimatedSprite.h"
#include "AnimatedSpriteType.h"
#include "Game.h"
#include "Physics.h"
#include "SpriteManager.h"

void Physics::startUp()
{

}

void Physics::shutDown()
{

}

void Physics::update()
{
	if (activated || activatedForSingleUpdate)
	{

		Game *game = Game::getSingleton();
		SpriteManager *spriteManager = game->getGSM()->getSpriteManager();
		AnimatedSprite *player = spriteManager->getPlayer();

		list<Bot*>::iterator botIterator = spriteManager->getBotsIterator();
		list<Bot*>::iterator end = spriteManager->getEndOfBotsIterator();

		while (botIterator != end)
		{

			Bot *bot = (*botIterator);
			PhysicalProperties *pl = player->getPhysicalProperties();

			


				PhysicalProperties *pp = bot->getPhysicalProperties();
	
			/**


			PhysicalProperties *pp = bot->getPhysicalProperties();
			float worldHeight = game->getGSM()->getWorld()->getWorldHeight();
			float worldWidth = game->getGSM()->getWorld()->getWorldWidth() - 10;
			if (pp->getX() > worldWidth || pp->getY() > worldHeight || pp->getX() < 0 || pp->getY() < 0) {

			pp->setVelocity(-pp->getVelocityX(), -pp->getVelocityY());
			pp->setIsHitWall(true);


			}



			*/

				float worldHeight = game->getGSM()->getWorld()->getWorldHeight();
				float worldWidth = game->getGSM()->getWorld()->getWorldWidth() - 10;


			pl->update();
			float pl_left = pl->getX();
			float pl_top = pl->getY();
			float pl_right = pl->getX() + player->getSpriteType()->getTextureWidth();
			float pl_bottom = pl->getY() + player->getSpriteType()->getTextureHeight();
			if ((pl_left < 0) && (pl->getVelocityX() < 0))
				pl->setVelocity(-pl->getVelocityX(), pl->getVelocityY());
			if ((pl_top < 0) && (pl->getVelocityY() < 0))
				pl->setVelocity(pl->getVelocityX(), -pl->getVelocityY());
			if ((pl_right >= worldWidth) && (pl->getVelocityX() > 0))
				pl->setVelocity(-pl->getVelocityX(), pl->getVelocityY());
			if ((pl_bottom >= worldHeight) && (pl->getVelocityY() > 0))
				pl->setVelocity(pl->getVelocityX(), -pl->getVelocityY());





			int worldCoordinateX = pl->getX();
			int worldCoordinateY = pl->getY();

			bot->getOrthographic()->mapPath(bot, worldCoordinateX, worldCoordinateY);
			bot->advanceCurrentPathNode();
			spriteManager->update();





			pp->update();
			botIterator++;
		}
	}
	activatedForSingleUpdate = false;
}
