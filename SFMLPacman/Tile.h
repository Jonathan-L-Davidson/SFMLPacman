#pragma once

#include "global.h"

/// <summary>
/// Controls the collision detection and response behavior of a tile.
/// </summary>
enum class TileCollision
{
    /// <summary>
    /// A passable tile is one which does not hinder player motion at all.
    /// </summary>
    Passable = 0,

    /// <summary>
    /// An impassable tile is one which does not allow the player to move through
    /// it at all. It is completely solid.
    /// </summary>
    Impassable = 1,

    /// <summary>
    /// A platform tile is one which behaves like a passable tile except when the
    /// player is above it. A player can jump up through a platform as well as move
    /// past it to the left and right, but can not fall down through the top of it.
    /// </summary>
    Platform = 2,
};

struct Tile
{
public:
    sf::Texture* Texture;
    TileCollision Collision;

    static const sf::Vector2i* Size;

    Tile(sf::Texture* texture, TileCollision collision);
	~Tile(void);
};