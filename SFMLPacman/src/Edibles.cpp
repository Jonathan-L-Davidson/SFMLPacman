#include "headers/Global.h"
#include "headers/Entities.h"

// Not intended to be used as an entity. Rather a base parent to base all other instances of edibles off of.

Edible::Edible() {
//	LoadEdible();
}

void Edible::LoadEdible() {
	LoadEntity();
}

void Edible::Eat(Pacman pacman) {
	delete this;
}

Munchie::Munchie() {
	LoadMunchie();
}

void Munchie::LoadMunchie() {
	_entityName = "munchie";
	_entitySize = sf::Vector2f(12, 12);

	_animated = true;
	_keyframeCount = 2;
	_keyframeDelay = 20;

	_scoreValue = 50;

	LoadEntity();
}

void Munchie::UpdateMunch() {
	UpdateSprite();
}

Cherry::Cherry() {
	_entityName = "cherry";

	_scoreValue = 100;
	
	LoadEntity();
}


/*
class Munchie : public Edible {
public:
	Munchie();
	virtual ~Munchie();
};

class Cherry : public Edible {
public:
	Cherry();
	virtual ~Cherry();
};*/