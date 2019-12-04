#include "headers/AIHandling.h"
#include "headers/Grid.h"

#include <iostream>
#include <algorithm>

//========================================================

AIHandler::AIHandler()
	:mGridToSolve(nullptr)
	, mCurrentNode(nullptr)
	, mTargetNode(nullptr)
	, mStartNode(nullptr)
	, mSolved(false)
{
}

void AIHandler::update()
{
	if (mSolved && !mPathDrawer.isDrawn())
		mPathDrawer.drawStep();
}

void AIHandler::solveGrid(Grid& grid)
{
	mGridToSolve = &grid;
	mTargetNode = mGridToSolve->getTargetedNode();
	mStartNode = mGridToSolve->getStartingNode();
	sf::Clock mSolveClock;
	mOpenNodes.emplace_back(mStartNode);

	if (!isGridCorrect())
		return;

	while (mCurrentNode != mTargetNode)
	{
		mCurrentNode = mOpenNodes.front();

		for (int i = 1; i < mOpenNodes.size(); ++i)
			if (mOpenNodes[i]->getFCost() < mCurrentNode->getFCost() || mOpenNodes[i]->getFCost() == mCurrentNode->getFCost() && mOpenNodes[i]->getHCost() == mCurrentNode->getHCost())
				mCurrentNode = mOpenNodes[i];

		for (int i = 0; i < mOpenNodes.size(); ++i)
			if (mOpenNodes[i] == mCurrentNode)
			{
				mOpenNodes.erase(mOpenNodes.begin() + i);
				continue;
			}

		mClosedNodes.emplace_back(mCurrentNode);

		if (mCurrentNode == mTargetNode)
		{
			mSolved = true;
			mSolveTime = mSolveClock.getElapsedTime();
			mPathDrawer.init(mCurrentNode, mStartNode);
			return;
		}

		std::vector<Node*> neighbourNodes = mGridToSolve->getNeighbours(mCurrentNode);
		for (auto& neighbourNode : neighbourNodes)
			if (!isInVector(neighbourNode, mClosedNodes) && neighbourNode->isWalkable())
				handleNeighbour(neighbourNode);

		if (mSolveClock.getElapsedTime().asMilliseconds() > 1000.f)
		{
			restartSolver();
			return;
		}
	}
}

bool AIHandler::isGridCorrect()
{
	if (mStartNode == mTargetNode)
		throw std::runtime_error("Chosen points are the same!");
	if (mStartNode == nullptr || mTargetNode == nullptr)
		return false;
	else
		return true;
}

bool AIHandler::isInVector(const Node* const node, const std::vector<Node*>& nodeVector) const
{
	return std::find(nodeVector.begin(), nodeVector.end(), node) != nodeVector.end();
}

void AIHandler::handleNeighbour(Node* const neighbourNode)
{
	int movementCostToNeighbour = mCurrentNode->getGCost() + getDistance(neighbourNode, mCurrentNode);
	if (movementCostToNeighbour < neighbourNode->getGCost() || !isInVector(neighbourNode, mOpenNodes))
	{
		neighbourNode->setGCost(movementCostToNeighbour);
		neighbourNode->setHCost(getDistance(neighbourNode, mTargetNode));
		neighbourNode->setParentNode(mCurrentNode);
		if (!isInVector(neighbourNode, mOpenNodes))
			mOpenNodes.emplace_back(neighbourNode);
	}
}

int AIHandler::getDistance(Node* const nodeA, Node* const nodeB)
{
	sf::Vector2i nodeAPos = nodeA->getPosition();
	sf::Vector2i nodeBPos = nodeB->getPosition();

	int xDist = std::abs(nodeAPos.x - nodeBPos.x);
	int yDist = std::abs(nodeAPos.y - nodeBPos.y);

	xDist *= xDist;
	yDist *= yDist;

	return static_cast<int>(std::hypot(xDist, yDist));
}

void AIHandler::restartSolver()
{
	mCurrentNode = nullptr;
	mTargetNode = nullptr;
	mStartNode = nullptr;
	mGridToSolve = nullptr;
	mClosedNodes.clear();
	mOpenNodes.clear();
	mSolved = false;
	mSolveTime = sf::Time::Zero;
}

bool AIHandler::getSolved()
{
	return mSolved;
}

float AIHandler::getSolveTime()
{
	return mSolveTime.asMicroseconds();
}
