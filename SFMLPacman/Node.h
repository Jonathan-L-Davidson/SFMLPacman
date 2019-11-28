#pragma once

#include "Global.h"


// Probably will the the most complicated part of this project.
// Nodes, these objects will assist the AI for pathfinding and these will be generated inside the level.
// Nodes will link together in a grid layout to assist the AI into finding a path to get to pacman.


// We want it to take data from drawable just like the level class, however we want to manipulate the tiles, so inheriting Transformable will be useful.
class Tile : public sf::Drawable, public sf::Transformable {

private:

	sf::Sprite _tileSprite;
	sf::Vector2f _tileSize;

public:
	Tile();

	virtual void DrawTile();
};

class Node {
	private:
		enum ID {
			GhostStart, Pacman, Ghost, Wall, Empty
		};

		ID _id;

		Tile _tile;

		Node* _parentNode; // Points to it's parent node.
		
		sf::Vector2i _gridPosition;

		int _GCost;
		int _HCost;

	public:
		Node(sf::Vector2i tilePos, sf::Vector2f tileSize);


		void SetID(ID id);
		ID GetID();

		void SetParent(Node* parentNode);

		void SetGCost();
		void SetHCost();

		int GetFCost();
		int GetGCost();
		int GetHCost();
		
		Node* GetParent();

		bool IsReachable();
		sf::Vector2i GetPosition();
};