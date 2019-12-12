#pragma once
#include "Global.hpp"
#include "Entities.h"
#include "Tile.h"

class Game {

	protected:
		
		Pacman* _pacman;

		Munchie* _munchies[munchieAmount];

		PowerPellet* _pellets[pelletAmount];

		Ghost* _ghosts[ghostAmount];

		Fruit* _fruit;

		Sound* _sound;

		int _timeFrozen; // Used to determine how long the game should be frozen for.

		std::vector<std::vector<Tile*>>* _tiles;

		// Window and viewport values including a clock definition.
		sf::RenderWindow* _window;
		sf::VideoMode* _videomode;
		sf::Clock* _clock;
		sf::Event* _event;
		sf::View* _view;

		// Text values for pause menu and start screen. More can be added here for GUI.
		// Later on this can be expanded and put into a seperate class and drawn from a list.
		sf::Font* _font;
		sf::Text* _pauseMessage;
		std::string* _messageString;
		sf::RectangleShape* _menuBackground; // Overlays during pause screen.
		bool _pauseButtonBuffer; // Used to check if the player is holding the pause button down.

		Resolution _res; // Resolution based from the global definition.

		enum GameState { RUNNING, STARTING, PAUSED, FROZEN, MENU, QUIT }; // Used to determine how the game is being used.

		GameState _gameState; // Enum definiton.
		
		float _deltaTime; // Used for smoothing out gameplay based on the framerate.

		std::string _resourceDir = resourceDir; // Directory for files.

		void LoadEntities(); // Load the entities.
		void LoadText();   // Load the text.
		void LoadWindow(); // Load the window.
		void LoadLevel(); // Load the game's level.
		void LoadExtras(); // Misc/Unsorted things.

		void Pause();
		void UnPause();

		void StartGame();
		void UpdateEntities();
		void UpdateEvent();

		int _score;

		int _scaredTimer;

	public:
		Game();
		~Game();

		void ScareGhosts();

		void LoadGame(); // Initialises pointers, starts values and assigns the correct data for values.
		void Update(); // This is called every frame. Only use this for processing data, treat it like a looping main().
		void Draw(); // Used to render each object each frame.
		void PauseGame(); // Public call to pause the game if required.
		void FreezeGame(const int& time); // Freeze the game for effects.

		void PlaySound(const std::string& input);

		sf::Text* ResetOrigin(sf::Text* text);

		TileType TileCharToType(char& type);
		Tile GetTile(const sf::Vector2i& pos) { return *(*_tiles)[pos.x][pos.y]; }; // Very weird to dereference it as a pointer, but it works.

};

