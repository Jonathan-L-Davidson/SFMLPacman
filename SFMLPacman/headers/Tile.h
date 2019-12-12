#pragma once
#include "Global.hpp"

class Game;

class Tile {
	private:
		std::string _resourceDir = resourceDir;

		TileType _type;

		// --- Sprite Start ---
		sf::Texture _texture;
		sf::Vector2f _size;
		sf::IntRect _sourceRect;
		sf::Sprite _sprite;
		// --- Sprite End ---

		sf::Vector2i _position;

		struct Neighbors {
			bool north;
			bool east;
			bool south;
			bool west;
		};

		Neighbors _neighbors;

	public:
		void LoadTile(TileType type, sf::Vector2i pos, Game* game);

		void InitSprite();

		void GetNeighbors(Game* game);
		void SetWallRotation();


		void SetType(TileType& type);
		TileType GetType() const { return _type; };
		void SetPosition(sf::Vector2i pos);
		void SetRotation(const int degrees) {};
		
		bool IsWall(const TileType& type) const { return type == WALLS || type == WALLT || _type == WALLC || _type == WALLE; };

};

