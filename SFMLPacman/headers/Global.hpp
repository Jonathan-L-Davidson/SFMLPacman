#pragma once

#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <cmath>
#include <ctime>
#include <cstdlib>
#include <iostream>
#include <list>

#define resourceDir	"Resources/";


class Resolution {
	public:
		float x = 800.0f;
		float y = 600.0f;
};

enum GhostType {
	BLINKY,	// Red ghost, chases the player.
	PINKY,	// Pink ghost, ambushes the player.
	INKY,	// Cyan ghost, unpredictable, can act like Blinky and Pinky.
	CLYDE	// Orange ghost, stupid ghost who acts like Blinky however flees when near.
};

enum FruitType {
	STRAWBERRY,
	APPLE,
	CHERRY,
	MELON
};

const int scaredTime = 500;
const int munchieAmount = 50;
const int pelletAmount = 5;
const int ghostAmount = 4;
