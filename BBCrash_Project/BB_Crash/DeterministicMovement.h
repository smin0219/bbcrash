#pragma once

#include "Bot.h"
#include "BotBehavior.h"

class DeterministicMovement : public BotBehavior
{
public:
	DeterministicMovement() {}
	~DeterministicMovement() {}
	void behave(Bot *bot);
	BotBehavior* clone();
};