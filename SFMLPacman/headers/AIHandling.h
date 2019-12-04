#pragma once

#include "Node.h"

#include <SFML/Graphics.hpp>

#include <vector>

class Grid;
class Node;

class AIHandler
{
public:
	AIHandler();

	void update();

	void solveGrid(Grid& grid);
	void restartSolver();
	bool getSolved();
	float getSolveTime();

private:
	void handleNeighbour(Node* const neighbourNode);

	bool isGridCorrect();
	bool isInVector(const Node* const node, const std::vector<Node*>& nodeVector) const;
	int getDistance(Node* const nodeA, Node* const nodeB);

private:
	Grid* mGridToSolve;
	AIHandler mPathDrawer;
	std::vector<Node*> mOpenNodes;
	std::vector<Node*> mClosedNodes;
	Node* mCurrentNode;
	Node* mTargetNode;
	Node* mStartNode;
	sf::Time mSolveTime;
	bool mSolved;
};