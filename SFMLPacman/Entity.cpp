#include "Global.h"
#include "Entities.h"


Entity::Entity() {
}

Entity::~Entity()
{
	delete _spriteBlendMode;
	delete _res;
}

void Entity::LoadEntity()
{

	_resourceDir = resourceDir;
	
	if (!_entityName.length()) { _entityName = "entity"; }



	// Load Pacman
	_entityTex.loadFromFile(_resourceDir + "sprites/" + _entityName + ".tga");

	if (!_entitySize.x && !_entitySize.y) { _entitySize = sf::Vector2f(32, 32); }


	_entitySourceRect = sf::IntRect(0.0f, 0.0f, _entitySize.x, _entitySize.y);

	_entitySprite.setTexture(_entityTex);
	//_entitySprite.setPosition(0,0);
	_entitySprite.setTextureRect(_entitySourceRect);
	_entitySprite.setOrigin(_entitySize / 2.f);


	_entityDirection = dirRIGHT;
	_entityStat = LIVING;

	_spriteBlendMode = new sf::BlendMode;
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