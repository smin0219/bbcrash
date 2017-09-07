#pragma once

#include "Bot.h"
#include "BotBehavior.h"

class RandomSpawn : public BotBehavior
{
private:
	float maxVelocity;

public:
	RandomSpawn() { maxVelocity = 0.0f; }
	~RandomSpawn() {}
	void setVelocity(float initMaxVelocity) {
		maxVelocity = initMaxVelocity;
	}
	void behave(Bot *bot);
	BotBehavior* clone();
};