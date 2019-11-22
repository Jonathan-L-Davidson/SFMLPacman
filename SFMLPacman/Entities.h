#pragma once

#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <thread>
#include <mutex>
#include <condition_variable>
#include "Global.h"

class Entity {

	protected:

		enum dir {
			dirRIGHT = 0,
			dirDOWN = 32,
			dirLEFT = 64,
			dirUP = 96 };

		enum stat {
			DEAD = 0,
			LIVING = 1,
			DYING = 2};

		std::string _resourceDir;
		std::string _entityName;

		sf::Texture* _entityTex;
		sf::Vector2f* _entitySize;
		sf::IntRect _entitySourceRect;
		sf::Sprite _entitySprite;

		dir _entityDirection;
		stat _entityStat;

		bool _animated;
		int _keyframeCount;
		int _keyframeInterval;
		int _keyframeDelay;
		int _keyframe;
		int _keyframePos;

		int _deathKeyframeCount;
		int _deathKeyframeInterval;
		int _deathKeyframeDelay;
		int _deathKeyframe;
		int _deathKeyframePos;

		sf::BlendMode* _spriteBlendMode;
		sf::Color _spriteColor;
		
		sf::SoundBuffer buffer;
		sf::Sound _deathSound;

		Resolution _res;

	public:

		sf::Vector2f GetPosition() const { return _entitySprite.getPosition(); };
		sf::Sprite GetSprite() const { return _entitySprite; };
		
		Entity();
		void LoadEntity();
		virtual ~Entity();
		void Update(float &deltaTime);
		void UpdateSprite();
		void Death();
		void PlayDeathAnim();

};

class Pacman : public Entity {
	private:
		// Data used for Pacman.
		float _pacmanSpeed = 150.0f;

		Entity _entity;

		void virtual HandleInput(float &deltaTime);

	public:

		Pacman();
		void LoadPacman();
		void UpdatePacman(float deltaTime);
		virtual ~Pacman();

};

class Ghosties : public Entity {

	public:
		Ghosties(int ghostType); // To do. Do math to make it so you can dynamically increase the amoutn of ghosts.

};