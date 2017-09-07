/*
Author: Richard McKenna
Stony Brook University
Computer Science Department

BugsButtonEventHandler.h

This is a custom button event handler. Each game can choose
to use different buttons and respond differently to when
buttons are pressed. This class will handle button presses for
the BugsGame following the ButtonEventHandler pattern.
*/

#pragma once
#include "stdafx.h"
#include "ButtonEventHandler.h"

class Game;

const wstring	GO_TO_MM_COMMAND = L"Go To Main Menu";
const wstring	START_COMMAND = L"Start";
const wstring	EXIT_COMMAND = L"Exit";
const wstring	QUIT_COMMAND = L"Quit";

class CrashButtonEventHandler : public ButtonEventHandler
{
public:
	// AS-IS, THIS CLASS HAS NO DATA, SO THERE IS NOTHING
	// TO INITIALIZE OR DESTROY
	CrashButtonEventHandler() {}
	~CrashButtonEventHandler() {}

	// DEFINED INSIDE BugsButtonEventHandler.cpp
	void handleButtonEvents(wstring command);
};