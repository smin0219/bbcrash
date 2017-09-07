/*	
	Author: Richard McKenna
			Stony Brook University
			Computer Science Department

	AnimatedSprite.h

	This class represents a sprite that can can
	be used to animate a game character or object.
*/

#pragma once
#include "stdafx.h"
#include "CollidableObject.h"
#include "PhysicalProperties.h"
#include "AnimatedSpriteType.h"
#include "Viewport.h"
#include "GridPathfinder.h"
#include "OrthographicGridPathfinder.h"
#include "AABB.h"

class AnimatedSprite : public CollidableObject
{
protected:
	// SPRITE TYPE FOR THIS SPRITE. THE SPRITE TYPE IS THE ID
	// OF AN AnimatedSpriteType OBJECT AS STORED IN THE SpriteManager
	AnimatedSpriteType *spriteType;

	// TRANSPARENCY/OPACITY
	int alpha;

	// THE "current" STATE DICTATES WHICH ANIMATION SEQUENCE 
	// IS CURRENTLY IN USE, BUT IT MAP ALSO BE USED TO HELP
	// WITH OTHER GAME ACTIVITIES, LIKE PHYSICS
	wstring currentState;

	// THE INDEX OF THE CURRENT FRAME IN THE ANIMATION SEQUENCE
	// NOTE THAT WE WILL COUNT BY 2s FOR THIS SINCE THE VECTOR
	// THAT STORES THIS DATA HAS (ID,DURATION) TUPLES
	unsigned int frameIndex;

	// USED TO ITERATE THROUGH THE CURRENT ANIMATION SEQUENCE
	unsigned int animationCounter;

	// USED TO RENDER A ROTATED SPRITE, NOT INVOLVED IN PHYSICS
	float rotationInRadians;

	// HELPS US KEEP TRACK OF WHEN TO REMOVE IT
	bool markedForRemoval;
	
	bool ReachedDestination;
	PathNode path2;
	list<PathNode>::iterator currentPathNode;
	list<PathNode> path;
	AABB aabb;
	OrthographicGridPathfinder orthographic;


public:
	// INLINED ACCESSOR METHODS
	int					getAlpha() { return alpha; }
	wstring				getCurrentState() { return currentState; }
	unsigned int		getFrameIndex() { return frameIndex; }
	float				getRotationInRadians() { return rotationInRadians; }
	AnimatedSpriteType*	getSpriteType() { return spriteType; }
	bool				isMarkedForRemoval() { return markedForRemoval; }
	AABB*				getBoundingVolume() { return &aabb; }
	list<PathNode>*	getCurrentPathToFollow() { return &path; }
	list<PathNode>::iterator getCurrentPathNode() { return currentPathNode; }
	OrthographicGridPathfinder* getOrthographic() { return &orthographic; }


	bool hasReachedDestination() { return ReachedDestination; }



	// INLINED MUTATOR METHODS
	void setAlpha(int initAlpha)
	{
		alpha = initAlpha;
	}
	void setRotationInRadians(float initRotation)
	{
		rotationInRadians = initRotation;
	}
	void setSpriteType(AnimatedSpriteType *initSpriteType)
	{
		spriteType = initSpriteType;
	}
	void markForRemoval()
	{
		markedForRemoval = true;
	}
	void advanceCurrentPathNode() 
	{
		currentPathNode++;
	}
	

	// METHODS DEFINED IN AnimatedSprite.cpp
	AnimatedSprite();
	virtual ~AnimatedSprite();
	void changeFrame();
	AnimatedSprite clearPath();
	void resetCurrentPathNode();
	unsigned int getCurrentImageID();
	void setCurrentState(wstring newState);
	void updateSprite();
};