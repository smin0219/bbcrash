#include "Bot.h"
#include "BotRecycler.h"
#include "BotBehavior.h"
#include "RecycledDeath.h"
#include "Game.h"
#include "SpriteManager.h"
#include "GameStateManager.h"

void RecycledDeath::behave(Bot *bot)
{
	// FIRST MAKE SURE THE ANIMATION STATE OF THE BOT
	// PLAYS THE DYING ANIMATION
	if (bot->getCurrentState().compare(L"DYING") != 0) {
		bot->setCurrentState(L"DYING");
		bot->getPhysicalProperties()->setVelocity(0.0f, 0.0f);
	}
	else {
		// CHECK TO SEE IF THE DYING ANIMATION IS DONE
		AnimatedSpriteType *spriteType = bot->getSpriteType();
		unsigned int frameIndex = (bot->getFrameIndex() * 2);
		unsigned int sequenceSize = spriteType->getSequenceSize(bot->getCurrentState()) + 2;
		if (frameIndex > sequenceSize) {
			// RETURN THIS BOT TO THE RECYCLE BIN
			Game *game = Game::getSingleton();
			GameStateManager *gsm = game->getGSM();
			SpriteManager *spriteManager = gsm->getSpriteManager();
			bot->markForRemoval();
			BotRecycler *botRecycler = spriteManager->getBotRecycler();
			botRecycler->recycleBot(bot);
		}
	}
}

BotBehavior* RecycledDeath::clone()
{
	RecycledDeath *behavior = new RecycledDeath();
	return behavior;
}