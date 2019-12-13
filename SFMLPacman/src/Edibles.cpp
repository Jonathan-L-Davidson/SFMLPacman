#include "Global.hpp"
#include "Entities.h"
#include "Game.h"
#include "Sound.h"

Edible::Edible() {}

void Edible::LoadEdible() {
	LoadEntity();
}

void Edible::OnHit(int& score, Game* game) {
	_eaten = true;
	game->PlaySound("muncheat.wav");
	score += _scoreValue;
}

Munchie::Munchie() {
	LoadMunchie();
}

void Munchie::LoadMunchie() {
	_entityName = "munchie";
	_entitySize = sf::Vector2f(12, 12);

	_animated = true;
	_keyframeCount = 2;
	_keyframeDelay = 10;

	_scoreValue = 50;

	LoadEntity();
}

Fruit::Fruit(int type) {
	_entityName = "fruit";

	_entitySize = sf::Vector2f(32, 32);

	_animated = false;
	
	LoadEntity();

	SetType(type);
}

void Fruit::OnHit(int& score, Game* game) {
	_eaten = true;
	game->PlaySound("fruiteat.wav");
	score += _scoreValue;
}

void Fruit::SetType(int type) {
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

	UpdateSprite();
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
	game->PlaySound("muncheat.wav");
	game->ScareGhosts();
	score += _scoreValue;
}
