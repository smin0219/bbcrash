
#pragma once
#include "stdafx.h"

class IllegalArgumentException :exception
{
public:
	// INLINED CONSTRUCTOR
	IllegalArgumentException(string *errorMessage)
	{
		exception(errorMessage->c_str());
	}

	// INLINED DESTRUCTOR
	~IllegalArgumentException() {}
};