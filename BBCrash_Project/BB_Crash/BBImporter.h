#pragma once

#include "stdafx.h"

class BBImporter
{
public:
	virtual bool load(wstring dir, wstring mapFile) = 0;
	virtual bool unload() = 0;
};