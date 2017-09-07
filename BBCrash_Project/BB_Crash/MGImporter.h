#pragma once
#pragma once

#include "tinyxml_VS\stdafx.h"

class MGImporter
{
public:
	virtual bool load(wstring dir, wstring mapFile) = 0;
	virtual bool unload() = 0;
};