#include "headers/Tile.h"
#include "headers/Game.h"

void Tile::LoadTile(char& type, sf::Vector2i pos, Game* game) {

	_size = sf::Vector2f(32, 32);

	SetType(type);
	SetPosition(pos);

}

void Tile::SetType(char& type) {
	_type = ConvertCharToType(type);
}

void Tile::InitSprite() {
	_texture.loadFromFile(_resourceDir + "sprites/level.png");
	_sourceRect = sf::IntRect(0, _size.y * _type, _size.x, _size.y);

	_sprite.setTexture(_texture);
	_sprite.setTextureRect(_sourceRect);
	_sprite.setOrigin(_size / 2.f); // Set the pivot to the middle.

}

void Tile::GetNeighbors(Game* game) {
	// Get north
	if (IsWall(game->GetTile(sf::Vector2i(_position.x, _position.y - 1)).GetType()))	_neighbors.north = true;
	// Get east
	if (IsWall(game->GetTile(sf::Vector2i(_position.x + 1, _position.y)).GetType()))	_neighbors.east = true;
	// Get south
	if (IsWall(game->GetTile(sf::Vector2i(_position.x, _position.y + 1)).GetType())) {
		std::cout << IsWall(game->GetTile(sf::Vector2i(_position.x, _position.y + 1)).GetType()) << "\nType: " << game->GetTile(sf::Vector2i(_position.x, _position.y + 1)).GetType() << "\n";
		_neighbors.south = true;
	}
	// Get west
	if (IsWall(game->GetTile(sf::Vector2i(_position.x - 1, _position.y)).GetType()))	_neighbors.west = true;
}

void Tile::SetPosition(sf::Vector2i& pos) {
	_position = pos;
	_sprite.setPosition(pos.x * _size.x, pos.y * _size.y);
}

void Tile::SetWallRotation() {
	switch (_type) {
	case WALLS: // Facing north and south by default.
		if (_neighbors.east && _neighbors.west) {
			_sprite.setRotation(90); // Face east and west.
		}
		break;
	case WALLT: // Faces north, east and south by default.
		if (_neighbors.east && _neighbors.south && _neighbors.west) {
			_sprite.setRotation(90); // Face east, south and west.
		}
		if (_neighbors.south && _neighbors.west && _neighbors.north) {
			_sprite.setRotation(180); // Face south, west and north.
		}
		if (_neighbors.west && _neighbors.north && _neighbors.south) {
			_sprite.setRotation(270); // Face west, north and east.
		}
		break;
	case WALLC: // Faces north and east by default.
		if (_neighbors.south && _neighbors.east) {
			_sprite.setRotation(90); // Face east and south.
		}

		if (_neighbors.south && _neighbors.west) {
			_sprite.setRotation(180); // Face south and west.
		}

		if (_neighbors.west && _neighbors.north) {
			_sprite.setRotation(270); // Face west and north.
		}
		break;

	case WALLE: // Faces right by default.
		if (_neighbors.north) {
			_sprite.setRotation(90); // Face down.
		}
		if (_neighbors.east) {
			_sprite.setRotation(180); // Face left.
		}
		if (_neighbors.south) {
			_sprite.setRotation(270); // Face north
		}
		break;
	default:
		break;
	}
}

TileType Tile::ConvertCharToType(char& type) {
	switch (type) {
	case 'P':
		return PACMAN;
		break;
	case '#':
		return MUNCHIE;
		break;
	case '@':
		return PELLET;
		break;
	case 'G':
		return GHOST;
		break;
	case 'D':
		return GHOSTDOOR;
		break;
	case 'F':
		return FRUIT;
		break;
	case 'S':
		return WALLS;
		break;
	case 'T':
		return WALLT;
		break;
	case 'C':
		return WALLC;
		break;
	case 'E':
		return WALLE;
		break;
	default:
		return MUNCHIE;
		break;
	}
}

void Tile::HandleRotation(Game* game) {
	if (IsWall(_type)) {
		GetNeighbors(game);
		SetWallRotation();
	}
}

bool Tile::IsWall(const TileType& type) {
	if (type == WALLS || type == WALLT || _type == WALLC || _type == WALLE) {
			return true;
	}
}