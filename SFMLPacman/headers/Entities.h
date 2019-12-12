#pragma once
#include "Global.hpp"

class Sound;
class Game;

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
		std::string GetName() const { return _entityName; };
		void Move(float x, float y) { return _entitySprite.move(x, y); };
		void SetPosition(sf::Vector2f pos);
		// --- Helpers End ---

		Entity();
		void LoadEntity(); // Load any values and initialise pointers. Assign any needed values.
		virtual ~Entity();
		
		void Update(float &deltaTime); // Should be looped for every entity tick. Deltatime must be given to sync the frames.
		
		void UpdateSprite(); // Used for sprite rendering, similar to Draw except it modies the entity sprite.

		virtual void HandleCollision(int& score, Entity* entity, Game* game);
		virtual void OnHit(int& score, Game* game);

		virtual void Death(Game* game);


};

class Pacman : public Entity {
	protected:

		float _pacmanSpeed = 150.0f; // Pacman's movement speed.

		void virtual HandleInput(float &deltaTime); // Handle player input.

	public:

		Pacman();
		~Pacman();

		void LoadPacman(); // Assign values for pacman.
		void UpdatePacman(float deltaTime); // Update pacman every tick.
		void Death(Game* game); // When pacman dies.
		void PlayDeathAnim(); // Render during pacman's death.

};

class Ghost : public Entity {
	private:
		GhostType _ghostType;
		
		float _ghostSpeed = 150.f;

		bool _scared;

		void HandleAI();
		void Death(Game* game);

		sf::Texture _ghostScaredTexture;
		sf::Texture _ghostDeadTexture;


	public:
		Ghost(GhostType ghostType); // To do. Do math to make it so you can dynamically increase the amoutn of ghosts.
		~Ghost();
		
		void Revive(Game* game);

		void SetScared();
		void CalmGhost();
		void UpdateGhost();
		void HandleCollision(Entity* entity, Game* game);
		void OnHit(Entity* entity, Game* game);
};

class Edible : public Entity {
	protected:
		int _scoreValue;
		bool _eaten;
	public:

		bool IsEaten() const { return _eaten; };
		Edible();
		void LoadEdible();
		std::string GetName() const { return _entityName; };
		void OnHit(int& score, Game* game);
};

class Munchie : public Edible {
	public:
		Munchie();
		void LoadMunchie();
		
};

class Fruit : public Edible {
	public:
		Fruit(int type);
		void OnHit(int& score, Game* game);
		void SetType(int type);
};

class PowerPellet : public Edible {
	public:
		PowerPellet();

		void HandleCollision(int& score, Entity* entity, Game* game);
		void OnHit(int& score, Game* game);
};