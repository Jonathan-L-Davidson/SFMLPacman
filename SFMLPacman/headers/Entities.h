#pragma once
#include "Global.h"



class Entity {

	protected:

		std::string _resourceDir; // Used for gathering resources for the entities.

		// Direction of the mob
		enum dir {
			dirRIGHT = 0,
			dirDOWN = 32,
			dirLEFT = 64,
			dirUP = 96
		};

		// Mob's stat, if it's alive, living, or dead.
		enum stat {
			DEAD = 0,
			LIVING = 1,
			DYING = 2
		};

		std::string _entityName; // Name of the entity, used for getting the filename. e.g: "Resources/entity.tga"

		// Variables used for creating and rendering the entity sprite
		// --- Sprite Start ---
		sf::Texture _entityTexture;
		sf::Vector2f _entitySize;
		sf::IntRect _entitySourceRect;
		sf::Sprite _entitySprite;

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

		sf::BlendMode _spriteBlendMode;
		sf::Color _spriteColor;
		// --- Sprite End ---

		dir _entityDirection; // Entity's direction, based off of the 'dir' enum.
		stat _entityStat; // Stat of the enemy, based off of the 'stat' enum.

		Resolution* _res; // Pointer to the resolution of the game.

	public:

		// --- Helpers Start ---
		sf::Vector2f GetPosition() const { return _entitySprite.getPosition(); };
		sf::Sprite GetSprite() const { return _entitySprite; };
		void Move(float x, float y) { return _entitySprite.move(x, y); };
		void SetPosition(sf::Vector2f pos);
		// --- Helpers End ---

		Entity();
		void LoadEntity(); // Load any values and initialise pointers. Assign any needed values.
		virtual ~Entity();
		
		void Update(float &deltaTime); // Should be looped for every entity tick. Deltatime must be given to sync the frames.
		
		void UpdateSprite(); // Used for sprite rendering, similar to Draw except it modies the entity sprite.
};

class Pacman : public Entity {
	protected:

		float _pacmanSpeed = 150.0f; // Pacman's movement speed.

		void virtual HandleInput(float &deltaTime); // Handle player input.

		sf::SoundBuffer buffer; // Sound buffering for pacman.
		sf::Sound _deathSound; // His death sound.


	public:

		Pacman();
		virtual ~Pacman();

		void LoadPacman(); // Assign values for pacman.
		void UpdatePacman(float deltaTime); // Update pacman every tick.
		void Death(); // When pacman dies.
		void PlayDeathAnim(); // Render during pacman's death.

};

class Ghosty : public Entity {

	public:
		Ghosty(int ghostType); // To do. Do math to make it so you can dynamically increase the amoutn of ghosts.

};

class Edible : public Entity {
	public:
		int _scoreValue;

		Edible();
		void LoadEdible();
		void Eat(Pacman pacman);
		//void ApplyEffect(Pacman pacman);

};

class Munchie : public Edible {
	public:
		Munchie();
		void LoadMunchie();
		void UpdateMunch();
};

class Cherry : public Edible {
	public:
		Cherry();
};