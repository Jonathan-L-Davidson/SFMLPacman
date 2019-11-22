#pragma once
#include <SFML/Graphics.hpp>
#include "Entities.h"

class Game {

	private:

		int ghostAmount = 4;

		//Ghosties _ghostList[ghostAmount];
		int* _score;

	protected:

		Pacman _pacman;

		enum GameState { RUNNING = 1, PAUSED, QUIT};

		//	sf::RenderWindow window(sf::VideoMode(res.x, res.y, 32), "SFML Pacman", sf::Style::Titlebar | sf::Style::Close);
		sf::RenderWindow* _window;
		sf::VideoMode* _videomode;
		sf::Clock* _clock;
		sf::Event* _event;
		sf::View* _view;

		sf::Font _font;
		sf::Text _pauseMessage;

		Resolution _res;

		GameState _gameState;
		float _deltaTime;

	public:
		Game();
		~Game();
		void virtual LoadGame();
		void virtual Update();
		void virtual Draw();
};

