#pragma once

#include "Game.h"
#include "MouseEventHandler.h"

class CrashMouseEventHandler : public MouseEventHandler
{
public:
	CrashMouseEventHandler() {}
	~CrashMouseEventHandler() {}
	void handleMousePressEvent(int mouseX, int mouseY);
	void handleMouseMoveEvent(int mouseX, int mouseY);
};