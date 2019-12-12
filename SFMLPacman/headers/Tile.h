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
			bool north = false;
			bool east = false;
			bool south = false;
			bool west = false;
		};

		Neighbors _neighbors;

	public:
		void LoadTile(char& type, sf::Vector2i pos, Game* game);

		sf::Sprite GetSprite() const { return _sprite; };
		void InitSprite();

		void GetNeighbors(Game* game);
		void SetWallRotation();

		void HandleRotation(Game* game);

		void SetType(char& type);
		TileType GetType() { return _type; };
		TileType ConvertCharToType(char& type);
		void SetPosition(sf::Vector2i& pos);
		void SetRotation(const int degrees) {};
		
		bool IsWall(const TileType& type);

};

