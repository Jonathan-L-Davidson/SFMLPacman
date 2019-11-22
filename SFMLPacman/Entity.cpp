#include "Entities.h"
#include "Global.h"
#include <iostream>

Entity::Entity() {
	LoadEntity();
}

Entity::~Entity()
{
	delete _entityTex;
	delete _entitySize;
//	delete _entitySourceRect;
	delete _spriteBlendMode;
	//delete _spriteColor;
	//delete _deathSound;
}

void Entity::LoadEntity()
{

	_resourceDir = resourceDir;
	_entityName = "entity";

	// Load Pacman
	_entityTex = new sf::Texture;
	_entityTex->loadFromFile(_resourceDir + _entityName + ".tga");

	_entitySize = new sf::Vector2f(32, 32);

	_entitySourceRect = sf::IntRect(0.0f, 0.0f, _entitySize->x, _entitySize->y);

	_entitySprite.setTexture(*_entityTex);
	_entitySprite.setPosition(150, 150);
	_entitySprite.setOrigin(*_entitySize / 2.f);
	_entitySprite.setTextureRect(_entitySourceRect);


	_entityDirection = dirUP;
	_entityStat = LIVING;

	_animated = false; // Not animated by default.

	_keyframeCount = 0;
	_keyframeDelay = 0;
	_keyframeInterval = 0;
	_keyframe = 0;

	_spriteBlendMode = new sf::BlendMode;
	_spriteColor = sf::Color::Transparent;

	buffer.loadFromFile(_resourceDir + _entityName + "_death.ogg");
	
	_deathSound.setBuffer(buffer);

}

void Entity::UpdateSprite() {


	// Handle animation sprite.
	if (_animated && _entityStat == LIVING) {
		if (_keyframeInterval > _keyframeDelay) {
			
			if (_keyframe >= _keyframeCount) {
				_keyframe = 0;
			}
			
			_keyframePos = _entitySize->x * _keyframe;
			
			_keyframe++;
			
			_keyframeInterval = 0;
		}
		else {
			_keyframeInterval++;
		}
	}
	
	if (_entityStat == LIVING) {
		_entitySourceRect = sf::IntRect(_keyframePos, _entityDirection, _entitySize->x, _entitySize->y);
		_entitySprite.setTextureRect(_entitySourceRect);
	}
}


void Entity::Update(float &deltaTime) {
	if (_entityStat == DYING) {
		PlayDeathAnim();
		return;
	}

	UpdateSprite();
}

void Entity::PlayDeathAnim() {

	if (_deathKeyframeInterval > _deathKeyframeDelay) {
		_deathKeyframePos = _entitySize->x * _deathKeyframe;

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

	_entitySourceRect = sf::IntRect(_deathKeyframePos, _entityDirection, _entitySize->x, _entitySize->y);
}

void Entity::Death() {

	if (_entityStat != DYING)	return;

	_deathSound.play();
	_entityStat = DYING;
	
}


