#pragma once
#include "Global.h"
#include "Entities.h"

struct Ghosties {
	Ghosty blinky;	// Red ghost, chases the player.
	Ghosty pinky;	// Pink ghost, ambushes the player.
	Ghosty inky;	// Cyan ghost, unpredictable, can act like Blinky and Pinky.
	Ghosty clyde;	// Orange ghost, stupid ghost who acts like Blinky however flees when near.
};

class Tile;
enum class TileCollision;

class Game {

	protected:

		std::vector<std::vector<Tile*>>* _tiles; //A vector of vectors

		// Struct of all entities in the game. When you require more entities, insert them here.
		struct Entities {
			Pacman pacman;
			Munchie munchie;
			Ghosties ghosts;
		};
		
		Pacman* _pacman;

		enum GameState { RUNNING = 1, PAUSED, MENU, QUIT}; // Used to determine how the game is being used. RUNNING by default is 1, the rest go up in increments.

		// Window and viewport values including a clock definition.
		sf::RenderWindow* _window;
		sf::VideoMode* _videomode;
		sf::Clock* _clock;
		sf::Event* _event;
		sf::View* _view;

		// Text values for pause menu and start screen. More can be added here for GUI.
		// Later on this can be expanded and put into a seperate class and drawn from a list.
		sf::Font _font;
		sf::Text _pauseMessage;
		std::string _messageString;
		sf::RectangleShape _menuBackground; // Overlays during pause screen.
		bool _pauseButtonBuffer; // Used to check if the player is holding the pause button down.

		Resolution _res; // Resolution based from the global definition.

		GameState _gameState; // Enum definiton.
		
		float _deltaTime; // Used for smoothing out gameplay based on the framerate.

		std::string _resourceDir = resourceDir; // Directory for files.


	public:
		Game();
		~Game();

		// Pointer to the score of the game.
		int* _score;

		Entities _entities;

		void virtual LoadGame(); // Initialises pointers, starts values and assigns the correct data for values.
		void virtual Update(); // This is called every frame. Only use this for processing data, treat it like a looping main().
		void virtual Draw(); // Used to render each object each frame.
		void virtual PauseGame(); // Public call to pause the game if required.
	
		void LoadTiles(int levelIndex);
		Tile* LoadTile(const char tileType, int x, int y);
		Tile* LoadTile(const char name, TileCollision collision);
		Tile* LoadEdibleTile(int x, int y, std::string tileType);
		Tile* LoadStartTile(int x, int y);
		Tile* LoadGhostStartTile(int x, int y);
		TileCollision GetCollision(int x, int y);
		void DrawTiles();

		int GetWidth();
		int GetHeight();

};

