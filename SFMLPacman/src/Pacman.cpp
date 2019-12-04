#include "headers/Entities.h"

Pacman::Pacman() {
	LoadPacman();
}

Pacman::~Pacman()
{

}

void Pacman::LoadPacman()
{
	_entityName = "pacman";
	
	_animated = true;
	_keyframeCount = 2;
	_keyframeDelay = 20;

	buffer.loadFromFile(_resourceDir + _entityName + "_death.ogg");

	_deathSound.setBuffer(buffer);

	LoadEntity();

}

void Pacman::UpdatePacman(float deltaTime) {


	if (_entityStat == DYING) {
		PlayDeathAnim();
		return;
	}

	Update(deltaTime);

	HandleInput(deltaTime);
}

void Pacman::HandleInput(float &deltaTime) {

	// MOVE UP - UP ARROW
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up) && (GetPosition().y - _entitySize.y / 2 > 0))
	{
		_entityDirection = dirUP;
		Move(0.f, -_pacmanSpeed * deltaTime);
	}

	// MOVE RIGHT - RIGHT ARROW
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right) && (GetPosition().x + _entitySize.x / 2 < _res->x))
	{
		_entityDirection = dirRIGHT;
		Move(_pacmanSpeed * deltaTime, 0.0f);
	}

	// MOVE LEFT - LEFT ARROW
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left) && (GetPosition().x - _entitySize.x / 2 > 0))
	{
		_entityDirection = dirLEFT;
		Move(-_pacmanSpeed * deltaTime, 0.0f);
	}

	// MOVE DOWN - DOWN ARROW
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down) && (GetPosition().y + _entitySize.y / 2 < _res->y))
	{
		_entityDirection = dirDOWN;
		Move(0.f, _pacmanSpeed * deltaTime);
	}
}


void Pacman::PlayDeathAnim() {

	if (_deathKeyframeInterval > _deathKeyframeDelay) {
		_deathKeyframePos = _entitySize.x * _deathKeyframe;

		_deathKeyframe++;
	}
	else {
		_deathKeyframeInterval++;
	}

	// If animation has finished.
	if (_deathKeyframePos >= _deathKeyframeCount) {
		delete this;
		return;
	}

	_entitySourceRect = sf::IntRect(_deathKeyframePos, _entityDirection, _entitySize.x, _entitySize.y);
}

void Pacman::Death() {

	if (_entityStat != DYING)	return;

	_deathSound.play();
	_entityStat = DYING;

}

