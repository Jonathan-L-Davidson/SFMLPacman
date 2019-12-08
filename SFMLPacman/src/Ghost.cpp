#include "headers/Global.hpp"
#include "headers/Entities.h"


Ghost::Ghost(GhostType ghostType) {
	_entityName = "ghost";
	_entitySize = sf::Vector2f(32, 32);

	_animated = false;
	
	switch (ghostType) {
	case BLINKY:
		_entityName = "blinky";
		_ghostType = BLINKY;
		break;
	case INKY:
		_entityName = "inky";
		_ghostType = INKY;
		break;
	case PINKY:
		_entityName = "pinky";
		_ghostType = PINKY;
		break;
	case CLYDE:
		_entityName = "clyde";
		_ghostType = CLYDE;
		break;
	}

	LoadEntity();

	_ghostScaredTexture.loadFromFile(_resourceDir + "sprites/ghostscared.png");
	_ghostDeadTexture.loadFromFile(_resourceDir + "sprites/ghostdead.png");

}

Ghost::~Ghost() {
	return;
}

void Ghost::UpdateGhost() {
	
}

void Ghost::SetScared() {
	if (!_entityStat == LIVING)	return;
	_scared = true;
	_entitySprite.setTexture(_ghostScaredTexture);
}

void Ghost::CalmGhost() {
	if (!_entityStat == LIVING)	return;
	_scared = false;
	_entitySprite.setTexture(_entityTexture);
}

void Ghost::HandleCollision(Entity* entity) {

	if (GetSprite().getGlobalBounds().intersects(entity->GetSprite().getGlobalBounds())) {
		OnHit(entity);
	}

}

void Ghost::OnHit(Entity* entity) {
	// It's pacman!
	if (entity->GetName() == "pacman") {
		if (_entityStat == LIVING) {
			if (_scared) {
				Death();
			} else {
				entity->Death(); 
			}
		}

	}
}

void Ghost::Death() {
	_entitySprite.setTexture(_ghostDeadTexture);
	_entityStat = DEAD;

	std::cout << std::endl << _entityName << " dies!\n";
}

void Ghost::Revive() {
	if (_entityStat == LIVING)	return;

	_entitySprite.setTexture(_entityTexture);
	_entityStat = LIVING;
}