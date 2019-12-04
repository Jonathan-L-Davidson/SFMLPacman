#include "headers/Grid.h"
#include "headers/Node.h"
#include <iostream>

Grid::Grid(int width, int height, int tileSize)
	:_currentPos(nullptr)
	, _targetNode(nullptr)
	, _gridSizeX(width)
	, _gridSizeY(height)
	, _tileSize(tileSize)
{
	createGrid();
}

void Grid::createGrid()
{
	for (int i = 0; i < _gridSizeX; ++i)
		for (int ii = 0; ii < _gridSizeY; ++ii)
			mNodes.emplace_back(std::make_unique<Node>(sf::Vector2i(i * _tileSize, ii * _tileSize), _tileSize));
}

void Grid::draw(sf::RenderTarget& renderTarget, sf::RenderStates renderStates) const
{
	for (auto& node : mNodes)
		renderTarget.draw(node->getNodeImage());
}

Node* Grid::getCurrentPosition() {
	return _currentPos;
}


Node* Grid::getTargetNode() {
	return _targetNode;
}

std::vector<Node*> Grid::getNeighbours(Node* const node)
{
	std::vector<Node*> neighbours;
	neighbours.reserve(9);
	for (int i = -1; i <= 1; ++i)
		for (int j = -1; j <= 1; ++j)
		{
			if (shouldIgnore(i, j))	continue;
			int nodePositionX = node->getPosition().x + _tileSize * i;
			int nodePositionY = node->getPosition().y + _tileSize * j;
			if (!isPositionProper(nodePositionX, nodePositionY)) continue;

			Node* neighbour = getNodeInWorld(nodePositionX, nodePositionY);
			neighbours.emplace_back(neighbour);
		}
	return neighbours;
}

bool Grid::shouldIgnore(int val1, int val2)
{
	std::vector<std::pair<int, int> > ignored = { {0, 0}, {-1,-1}, {-1,1}, {1,1}, {1,-1} };
	for (auto tile : ignored)
		if (val1 == tile.first && val2 == tile.second) return true;
	return false;
}


void Grid::setTargetNode(Node * const targetedNode)
{
	if (targetedNode == _currentPos)
		return;	//makes sure that does not overwrite startingNode

	if (_targetNode != nullptr)
		_targetNode->setType(NodeType::None);
	_targetNode = targetedNode;
	_targetNode->setType(NodeType::TargetedNode);
}

void Grid::handleObstacle(Node* const obstacleNode)
{
	if (obstacleNode->getType() != NodeType::StartingNode && obstacleNode->getType() != NodeType::TargetedNode)
	{
		if (obstacleNode->getType() != NodeType::ObstacleNode)
			setObstacle(obstacleNode);
		else if (obstacleNode->getType() == NodeType::ObstacleNode)
			removeObstacle(obstacleNode);
	}
}

void Grid::setObstacle(Node * const obstacleNode)
{
	obstacleNode->setType(NodeType::ObstacleNode);
}

void Grid::removeObstacle(Node * const obstacleNode)
{
	obstacleNode->setType(NodeType::None);
}

bool Grid::isPositionProper(int posX, int posY)
{
	if (posX > _tileSize * _gridSizeX + _tileSize || posX < 0 ||
		posY > _tileSize * _gridSizeY + _tileSize || posY < 0)
		return false;
	else
		return true;
}

bool Grid::getNodeToSet()
{
	static bool shouldSetStartingNode;
	if (!_currentPos)
		shouldSetStartingNode = true;
	else if (!_targetNode)
		shouldSetStartingNode = false;
	else if (_currentPos && _targetNode)
		shouldSetStartingNode = !shouldSetStartingNode;

	return shouldSetStartingNode;
}

Node* Grid::getNodeInWorld(int posX, int posY)
{
	int xPosition = posX / _tileSize;
	int yPosition = posY / _tileSize;
	int tilePosition = _gridSizeY * xPosition + yPosition;
	return mNodes[tilePosition].get();
}
