#pragma once

#include "stdafx.h"
#include "Game.h"
#include "GridPathfinder.h"
#include "World.h"

const int DIAGONAL_COST = 14;
const int COLUMN_COST = 10;
const int ROW_COST = 10;
const float GRID_EPSILON = 3.0f;

// NOTE THE USER WILL BE ABLE TO CHANGE
// PLAYER SPEED VIA M AND N
const float MAX_WALK_SPEED = 6.0f;

class OrthographicGridPathfinder : public GridPathfinder
{
public:
	OrthographicGridPathfinder(Game *game);
	~OrthographicGridPathfinder() {}
	void mapPath(AnimatedSprite *sprite, float worldX, float worldY);
	void updatePath(AnimatedSprite *sprite);
	float getColumnCenterX(int column);
	float getRowCenterY(int row);
	void initGrid();
	bool isWalkable(int col, int row);
	int getGridWidth();
	int getGridHeight();
	void increaseSpeed() {
		speed++;
	}

	void decreaseSpeed() {
		speed--;
	}
private:
	bool containsPathNode(list<PathNode> *path, PathNode testNode);
	int calculateG(PathNode node);
	int calculateH(PathNode start, PathNode *end);
	bool hasReachedNode(AnimatedSprite *sprite, PathNode destination);
	void buildPath(list<PathNode> *pathToFill,
		float startX, float startY,
		float endX, float endY);
	int getGridIndex(int col, int row);


	void moveSelectedPathfindingCell(int worldX, int worldY);
	int getAdjacencyIndex(int col, int row);
	void findNeighborsToCheck(bool *adjacencies,
		PathNode *nodeToConsider,
		map<int, PathNode> *closedNodes);
	PathNode* findDupNodeInList(PathNode targetNode, list<PathNode> *nodeList);
	void addNeighbors(bool *nodesToAdd, PathNode *centerNode, PathNode *destination, map<int, PathNode> *openNodes, map<int, PathNode> *closedNodes);
	PathNode* findCheapestNode(map<int, PathNode> *openNodes);
	void removeNodeFromList(PathNode *nodeToRemove, list<PathNode> *nodeList);

};