
#include "Entities.h"

#include <SFML/Audio.hpp>
#include <cmath>
#include <ctime>
#include <cstdlib>
#include <iostream>
#include "Global.h"

Pacman::Pacman() {
	LoadEntity();
	LoadPacman();
}

Pacman::~Pacman()
{

}

void Pacman::LoadPacman()
{
	_entityName = "pacman";

	_entityStat = LIVING;
	
	_animated = true;
	_keyframeCount = 2;
	_keyframeDelay = 750;
}

void Pacman::UpdatePacman(float deltaTime) {
	Update(deltaTime);

	HandleInput(deltaTime);
}

void Pacman::HandleInput(float &deltaTime) {
	// MOVE UP - UP ARROW
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up) && (GetPosition().y - _entitySize->y / 2 > 0))
	{
		_entityDirection = dirUP;
		_entitySprite.move(0.f, -_pacmanSpeed * deltaTime);
	}

	// MOVE RIGHT - RIGHT ARROW
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right) && (GetPosition().x + _entitySize->x / 2 < _res.x))
	{
		_entityDirection = dirRIGHT;
		_entitySprite.move(_pacmanSpeed * deltaTime, 0.0f);
	}

	// MOVE LEFT - LEFT ARROW
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left) && (GetPosition().x - _entitySize->x / 2 > 0))
	{
		_entityDirection = dirLEFT;
		_entitySprite.move(-_pacmanSpeed * deltaTime, 0.0f);
	}

	// MOVE DOWN - DOWN ARROW
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down) && (GetPosition().y + _entitySize->y / 2 < _res.y))
	{
		_entityDirection = dirDOWN;
		_entitySprite.move(0.f, _pacmanSpeed * deltaTime);
	}
}
