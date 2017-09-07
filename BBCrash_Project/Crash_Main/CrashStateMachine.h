#pragma once

#include "GameStateMachine.h"

class CrashStateMachine : public GameStateMachine
{
public:
	CrashStateMachine() {}
	~CrashStateMachine() {}
	void update();
};