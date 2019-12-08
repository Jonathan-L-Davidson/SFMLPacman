#include "headers/Global.hpp"
#include "headers/Entities.h"
#include "headers/Game.h"

Edible::Edible() {
//	LoadEdible();
}

void Edible::LoadEdible() {
	LoadEntity();
}

void Edible::OnHit(int& score) {
	_eaten = true;
	score += _scoreValue;
}

Munchie::Munchie() {
	LoadMunchie();
}

void Munchie::LoadMunchie() {
	_entityName = "munchie";
	_entitySize = sf::Vector2f(12, 12);

	_animated = false;

	_scoreValue = 50;

	LoadEntity();
}

Fruit::Fruit(FruitType type) {
	_entityName = "fruit";

	_entitySize = sf::Vector2f(32, 32);


	switch (type) {
		case STRAWBERRY:
			_keyframePos = 0;
			_scoreValue = 300;
			break;
		case APPLE:
			_keyframePos = _entitySize.x;
			_scoreValue = 700;
			break;
		case CHERRY:
			_keyframePos = _entitySize.x * 2;
			_scoreValue = 100;
			break;
		case MELON:
			_keyframePos = _entitySize.x * 3;
			_scoreValue = 1000;
			break;
	}
	
	LoadEntity();
}

PowerPellet::PowerPellet() {
	_entityName = "powerpellet";
	
	_entitySize = sf::Vector2f(16, 16);

	
	_animated = true;
	_keyframeCount = 2;
	_keyframeDelay = 20;

	_scoreValue = 100;

	LoadEntity();
}

void PowerPellet::HandleCollision(int& score, Entity* entity, Game* game) {

	if (GetSprite().getGlobalBounds().intersects(entity->GetSprite().getGlobalBounds())) {
		OnHit(score, game);
	}

}

void PowerPellet::OnHit(int& score, Game* game) {
	_eaten = true;
	score += _scoreValue;
	game->ScareGhosts();
}
