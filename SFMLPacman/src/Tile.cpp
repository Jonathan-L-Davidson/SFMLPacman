#include "headers/Tile.h"
#include "headers/Game.h"

void Tile::LoadTile(TileType type, sf::Vector2i pos, Game* game) {

	std::cout << "\n Type: " << type << std::endl;
	
	//SetType(type);
	SetPosition(pos);

	if (IsWall(_type)) {
		GetNeighbors(game);
	}

	InitSprite();
}

void Tile::SetType(TileType& type) {
	_type = type;
}

void Tile::InitSprite() {
	_texture.loadFromFile(_resourceDir + "sprites/level.png");
	_sourceRect = sf::IntRect(0, _size.y * _type, _size.x, _size.y);

	_sprite.setTexture(_texture);
	_sprite.setTextureRect(_sourceRect);
	_sprite.setOrigin(_size / 2.f); // Set the pivot to the middle.

	if (IsWall(_type))	SetWallRotation();
}

void Tile::GetNeighbors(Game* game) {
	// Get north
	if (IsWall(game->GetTile(sf::Vector2i(_position.x, _position.y + 1)).GetType()))	_neighbors.north = true;
	// Get east
	if (IsWall(game->GetTile(sf::Vector2i(_position.x + 1, _position.y)).GetType()))	_neighbors.east = true;
	// Get south
	if (IsWall(game->GetTile(sf::Vector2i(_position.x, _position.y - 1)).GetType()))	_neighbors.south = true;
	// Get west
	if (IsWall(game->GetTile(sf::Vector2i(_position.x - 1, _position.y)).GetType()))	_neighbors.west = true;
}

void Tile::SetPosition(sf::Vector2i pos) {
	_sprite.setPosition(_position.x * _size.x, _position.y * _size.y);
}

void Tile::SetWallRotation() {
	switch (_type) {
	case WALLS: // Facing east and west by default.
		if (_neighbors.north && _neighbors.south) {
			SetRotation(90); // Face north and south.
		}
		break;
	case WALLT: // Faces north, east and south by default.
		if (_neighbors.east && _neighbors.south && _neighbors.west) {
			SetRotation(90); // Face east, south and west.
		}
		if (_neighbors.south && _neighbors.west && _neighbors.north) {
			SetRotation(180); // Face south, west and north.
		}
		if (_neighbors.west && _neighbors.north && _neighbors.south) {
			SetRotation(270); // Face west, north and east.
		}
		break;
	case WALLC: // Faces north and east by default.
		if (_neighbors.south && _neighbors.east) {
			SetRotation(90); // Face east and south.
		}

		if (_neighbors.south && _neighbors.west) {
			SetRotation(180); // Face south and west.
		}

		if (_neighbors.west && _neighbors.north) {
			SetRotation(270); // Face west and north.
		}
		break;

	case WALLE: // Faces right by default.
		if (_neighbors.north) {
			SetRotation(90); // Face down.
		}
		if (_neighbors.east) {
			SetRotation(180); // Face left.
		}
		if (_neighbors.south) {
			SetRotation(270); // Face north
		}
		break;
	default:
		break;
	}
}
