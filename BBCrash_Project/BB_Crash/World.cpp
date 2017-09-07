/*
	Author: Richard McKenna
			Stony Brook University
			Computer Science Department

	World.cpp

	See World.h for a class description.
*/

#include "stdafx.h"
#include "Game.h"
#include "GameGraphics.h"
#include "RenderList.h"
#include "TextureManager.h"
#include "SpriteManager.h"
#include "GameStateManager.h"
#include "World.h"
#include "Viewport.h"


/*
World - Default Constructor, it constructs the layers
vector, allowing new layers to be added.
*/
World::World()
{
	layers = new vector<WorldLayer*>();
	worldWidth = 0;
	worldHeight = 0;
}

/*
~World - This destructor will remove the memory allocated
for the layer vector.
*/
World::~World()
{
	delete layers;
}

/*
addLayer - This method is how layers are added to the World.
These layers might be TiledLayers, SparseLayers, or
IsometricLayers, all of which are child classes of WorldLayer.
*/
void World::addLayer(WorldLayer *layerToAdd)
{
	layers->push_back(layerToAdd);
}

/*
addWorldRenderItemsToRenderList - This method sends the render
list and viewport to each of the layers such that they
may fill it with RenderItems to draw.
*/
void World::addWorldRenderItemsToRenderList()
{
	Game *game = Game::getSingleton();
	GameStateManager *gsm = game->getGSM();
	GameGUI *gui = game->getGUI();
	if (gsm->isWorldRenderable())
	{
		GameGraphics *graphics = game->getGraphics();
		RenderList *renderList = graphics->getWorldRenderList();
		Viewport *viewport = gui->getViewport();
		for (unsigned int i = 0; i < layers->size(); i++)
		{
			layers->at(i)->addRenderItemsToRenderList(renderList,
				viewport);
		}
	}
}

int World::getCollidableGridColumns()
{
	return 1;
}

int World::getCollidableGridRows()
{
	return 1;
}

bool World::overlapsCollidableTiles(int centerX, int centerY, int nodeWidth, int nodeHeight)
{
	return false;
}

bool World::isInsideCollidableTile(int centerX, int centerY)
{
	return false;
}

/*
clear - This method removes all data from the World. It should
be called first when a level is unloaded or changed. If it
is not called, an application runs the risk of having lots
of extra data sitting around that may slow the progam down.
Or, if the world thinks a level is still active, it might add
items to the render list using image ids that have already been
cleared from the GameGraphics' texture manager for the world.
That would likely result in an exception.
*/
void World::unloadWorld()
{
	// GO THROUGH AND DELETE ALL THE LAYERS
	vector<WorldLayer*>::iterator it = layers->begin();
	while (it != layers->end())
	{
		vector<WorldLayer*>::iterator tempIt = it;
		it++;
		WorldLayer *layerToDelete = (*tempIt);
		delete layerToDelete;
	}
	layers->clear();
	worldWidth = 0;
	worldHeight = 0;
}

/*
update - This method should be called once per frame. Note that
the World is for static objects, so we don't have anything
to update as/is. But, should the need arise, one could add non-
collidable layers to a game world and update them here. For
example, particle systems.
*/
void World::update()
{
	// NOTE THAT THIS METHOD IS NOT IMPLEMENTED BUT COULD BE
	// SHOULD YOU WISH TO ADD ANY NON-COLLIDABLE LAYERS WITH
	// DYNAMIC CONTENT OR PARTICLE SYSTEMS
}