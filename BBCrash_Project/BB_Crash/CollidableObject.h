#pragma once
#include "stdafx.h"
#include "PhysicalProperties.h"

class CollidableObject
{
protected:
	bool currentlyCollidable;
	PhysicalProperties pp;

public:
	CollidableObject()	{}
	~CollidableObject()	{}

	// INLINED METHODS
	bool				isCurrentlyCollidable()		{ return currentlyCollidable;	}
	PhysicalProperties* getPhysicalProperties()		{ return &pp;					}

	void setCurrentlyCollidable(bool initCurrentlyCollidable)
	{	currentlyCollidable = initCurrentlyCollidable; }
};