
#include "Bot.h"
#include "BotBehavior.h"
#include "DeterministicMovement.h"
#include "PhysicalProperties.h"

void DeterministicMovement::behave(Bot *bot)
{

}

BotBehavior* DeterministicMovement::clone()
{
	DeterministicMovement *behavior = new DeterministicMovement();
	return behavior;
}

