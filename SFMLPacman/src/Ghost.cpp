#include "Global.hpp"
#include "Entities.h"
#include "Game.h"

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

void Ghost::HandleCollision(Entity* entity, Game* game) {

	if (GetSprite().getGlobalBounds().intersects(entity->GetSprite().getGlobalBounds())) {
		OnHit(entity, game);
	}

}

void Ghost::OnHit(Entity* entity, Game* game) {
	// It's pacman!
	if (entity->GetName() == "pacman") {
		if (_entityStat == LIVING) {
			_scared ? Death(game) : entity->Death(game);
		}

	}
}

void Ghost::Death(Game* game) {
	_entitySprite.setTexture(_ghostDeadTexture);
	_entityStat = DEAD;

	game->PlaySound("ghosteat.wav");
	game->FreezeGame(15); // Pause the game for 15 frames;
	std::cout << std::endl << _entityName << " dies!\n";
}

void Ghost::Revive(Game* game) {
	if (_entityStat == LIVING)	return;

	_entitySprite.setTexture(_entityTexture);
	_entityStat = LIVING;
}