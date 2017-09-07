#pragma once

#include "BotBehavior.h"

class RecycledDeath : public BotBehavior
{
public:
	RecycledDeath() {}
	~RecycledDeath() {}
	void behave(Bot *bot);
	BotBehavior* clone();
};