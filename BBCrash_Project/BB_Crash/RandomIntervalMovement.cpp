#include "Bot.h"
#include "BotBehavior.h"
#include "RandomIntervalMovement.h"
#include "PhysicalProperties.h"

void RandomIntervalMovement::behave(Bot *bot)
{
	// HOW MUCH TIME HAS PASSED SINCE THE LAST TIME WE CHECKED?

	// IS IT TIME TO CHANGE DIRECTION AGAIN?

}

BotBehavior* RandomIntervalMovement::clone()
{
	RandomIntervalMovement *behavior = new RandomIntervalMovement();
	return behavior;
}

