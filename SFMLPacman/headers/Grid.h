#pragma once

#include <SFML/Graphics.hpp>
#include "Node.h"

#include <vector>
#include <memory>

struct MousePositions;
class Node;

class Grid : public sf::Drawable
{
	private:

		void createGrid();

		void setTargetNode(Node* const targetedNode);
		void handleObstacle(Node* const obstacleNode);
		void setObstacle(Node* const obstacleNode);
		void removeObstacle(Node* const obstacleNode);

		bool isPositionProper(int posX, int posY);
		bool shouldIgnore(int val1, int val2);
		bool getNodeToSet();

		std::vector<std::unique_ptr<Node>> mNodes;
		Node* _currentPos;
		Node* _targetNode;
		int _gridSizeX;
		int _gridSizeY;
		int _tileSize;

	public:
		Grid(int width, int height, int tileSize);

		void draw(sf::RenderTarget& renderTarget, sf::RenderStates renderStates) const override;

		Node* getCurrentPosition();
		Node* getTargetNode();
		std::vector<Node*> getNeighbours(Node* const node);
		Node* getNodeInWorld(int posX, int posY);

};
