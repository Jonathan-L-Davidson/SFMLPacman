#include "Game.h"
#include <algorithm>
#include "Entities.h"

Game::Game() {
	LoadGame();

	Update();
}

Game::~Game() {

	delete _window;
	delete _videomode;
	delete _clock;
	delete _event;
	delete _view;

	delete _score;

}

void Game::LoadGame() {

	/*
	for (int i = 0; i < ghostAmount; i++) {
		_ghostList[i] = new Ghosties(i);
	}*/

//	_pacman = new Pacman;

	_clock = new sf::Clock;

	_videomode = new sf::VideoMode(_res.x, _res.y, 32);
	_window = new sf::RenderWindow(*_videomode, "Pacman", sf::Style::Titlebar | sf::Style::Close);


	_font.loadFromFile("Resources/sansation.ttf");

	_pauseMessage.setFont(_font);
	_pauseMessage.setCharacterSize(40);
	_pauseMessage.setPosition(170.f, 150.f);
	_pauseMessage.setFillColor(sf::Color::White);
	_pauseMessage.setString("Welcome to Pacman!\nPress space to start the game");


	_view = new sf::View;

	_deltaTime = _clock->restart().asSeconds();

	_gameState = PAUSED;

}
void Game::Update() {

	while (_window->isOpen()) {
		// Event value to store incoming events.
		sf::Event event;
		while (_window->pollEvent(event)) {
			// CLOSE WINDOW - ESC / CLOSE WINDOW
			if ((event.type == sf::Event::Closed) || ((event.type == sf::Event::KeyPressed) && (event.key.code == sf::Keyboard::Escape))) {
				_window->close();
				break;
			}

			// If the window resize has changed somehow, force the viewport to be the screen's resolution. Prevents distortion.
			if (event.type == sf::Event::Resized) {
				sf::View view;
				view.setSize(_res.x, _res.y);
				view.setCenter(_res.x / 2, _res.y / 2);
				_window->setView(view);
			}

			// PLAY - SPACEBAR
			if (((event.type == sf::Event::KeyPressed) && (event.key.code == sf::Keyboard::Space))) {
				if (_gameState != RUNNING) {
					// Start the game 
					_gameState = RUNNING;
					_clock->restart();
				}
			}
		}


		// MAIN GAME LOOP.
		if (_gameState == RUNNING)
		{
			// Every tick, reset deltaTime.
			_deltaTime = _clock->restart().asSeconds();

			_pacman.UpdatePacman(_deltaTime);
			
			/*
			for (int i = 0; i < ghostAmount; i++) {
				_ghostList[i]->Update(_deltaTime);
			}*/

		}

		Draw();
	}

}
void Game::Draw() {

	// Clear all drawn objects.
	_window->clear();

	// Drawing objects goes here!

	if (_gameState == RUNNING)
	{
		_window->draw(_pacman.GetSprite());

	}
	else
	{
		// Draw the pause message
		_window->draw(_pauseMessage);
	}

	// Display the drawn objects.
	_window->display();
}
