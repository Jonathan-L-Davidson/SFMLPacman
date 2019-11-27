#include "Game.h"
#include "Entities.h"
#include <algorithm>

sf::Text* ResetOrigin(sf::Text* text) {
	sf::FloatRect textRect = text->getLocalBounds();
	text->setOrigin(textRect.left + textRect.width / 2.0f, textRect.top + textRect.height / 2.0f);
	return text;
}

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

	_clock = new sf::Clock;

	munch.SetPosition(sf::Vector2f(_res.x / 2, _res.y / 2));

	_videomode = new sf::VideoMode(_res.x, _res.y, 32);
	_window = new sf::RenderWindow(*_videomode, "Pacman", sf::Style::Titlebar | sf::Style::Close);
	_window->setFramerateLimit(60);

	_font.loadFromFile(_resourceDir + "Fonts/sansation.ttf");

	_pauseMessage.setFont(_font);
	_pauseMessage.setCharacterSize(40);
	_messageString = "Welcome to Pacman!\nPress space to start the game";
	_pauseMessage.setString(_messageString);
	_pauseMessage.setFillColor(sf::Color::White);
	ResetOrigin(&_pauseMessage);
	_pauseMessage.setPosition(_res.x / 2, _res.y / 2);
	_menuBackground.setSize(sf::Vector2f(_res.x, _res.y));
	_menuBackground.setFillColor(sf::Color(30, 30, 30, 130));

	_view = new sf::View;

	_deltaTime = _clock->restart().asSeconds();

	_gameState = MENU;

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
			if (((event.type == sf::Event::KeyPressed) && (event.key.code == sf::Keyboard::Space)) && _gameState == MENU) {
				if (_gameState != RUNNING) {
					// Start the game 
					_gameState = RUNNING;
					_clock->restart();

				}
			}

			// PAUSE - P (Also checks if pauseButton is being held down)
			if (((event.type == sf::Event::KeyPressed) && (event.key.code == sf::Keyboard::P)) && !_pauseButtonBuffer) {
				if (_gameState == RUNNING) {
					_gameState = PAUSED;
					_pauseButtonBuffer = true;

					_messageString = "GAME PAUSED";
					_pauseMessage.setString(_messageString);
					ResetOrigin(&_pauseMessage);
					_pauseMessage.setPosition(_res.x / 2, _res.y / 2);
					_messageString.append("\nPress P to continue.\n\nPress R to restart.");

				} else if (_gameState == PAUSED) {
					_gameState = RUNNING;
					_clock->restart();
				}
			}

			if (((event.type == sf::Event::KeyReleased) && (event.key.code == sf::Keyboard::P)))	_pauseButtonBuffer = false;
		}


		// MAIN GAME LOOP.
		if (_gameState == RUNNING && _gameState != PAUSED)
		{
			// Every tick, reset deltaTime.
			_deltaTime = _clock->restart().asSeconds();

			munch.UpdateMunch();

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
	if (_gameState != MENU) {
		_window->draw(_pacman.GetSprite());

		_window->draw(munch.GetSprite());

		if (_gameState == PAUSED) {
			_window->draw(_menuBackground);
			// Draw the pause message
			_window->draw(_pauseMessage);
		}
	} else {
		// Draw the pause message
		_window->draw(_menuBackground);
		_window->draw(_pauseMessage);
	}

	// Display the drawn objects.
	_window->display();
}

void Game::PauseGame() {
	_gameState = PAUSED;
}

