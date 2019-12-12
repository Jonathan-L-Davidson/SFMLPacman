#include "headers/Global.hpp"
#include "headers/Entities.h"
#include "headers/Game.h"


Entity::Entity() {
}

Entity::~Entity()
{
	delete _res;
}

void Entity::LoadEntity()
{

	_resourceDir = resourceDir;
	
	if (!_entityName.length()) { _entityName = "entity"; }

	_entityTexture.loadFromFile(_resourceDir + "sprites/" + _entityName + "/" + _entityName + ".png");

	if (!_entitySize.x && !_entitySize.y) { _entitySize = sf::Vector2f(32, 32); }

	_entitySourceRect = sf::IntRect(0.0f, 0.0f, _entitySize.x, _entitySize.y);

	_entitySprite.setTexture(_entityTexture);
	//_entitySprite.setPosition(0,0);
	_entitySprite.setTextureRect(_entitySourceRect);
	_entitySprite.setOrigin(_entitySize / 2.f);


	_entityDirection = dirRIGHT;
	_entityStat = LIVING;

	_spriteColor = sf::Color::Transparent;

	_res = new Resolution;

}

void Entity::UpdateSprite() {


	// Handle animation sprite.
	if (_animated && _entityStat == LIVING) {
		if (_keyframeInterval > _keyframeDelay) {
			
			if (_keyframe >= _keyframeCount) {
				_keyframe = 0;
			}
			
			_keyframePos = _entitySize.x * _keyframe;
			
			_keyframe++;
			
			_keyframeInterval = 0;
		}
		else {
			_keyframeInterval++;
		}
	}
	
	if (_entityStat == LIVING) {
		_entitySourceRect = sf::IntRect(_keyframePos, _entityDirection, _entitySize.x, _entitySize.y);
		_entitySprite.setTextureRect(_entitySourceRect);
	}
}


void Entity::Update(float &deltaTime) {
	UpdateSprite();
}

void Entity::SetPosition(sf::Vector2f pos) {
	_entitySprite.setPosition(pos);
}

void Entity::HandleCollision(int& score, Entity* entity, Game* game) {

	if (GetSprite().getGlobalBounds().intersects(entity->GetSprite().getGlobalBounds())) {
		OnHit(score, game);
	}

}

void Entity::OnHit(int& score, Game* game) {
	return; // Do nothing.
}

void Entity::Death(Game* game) {
	std::cout << std::endl << _entityName << " dies!\n";
	_entityStat = DEAD;
}