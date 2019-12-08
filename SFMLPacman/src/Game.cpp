#include "headers/Game.h"
#include "headers/Entities.h"
#include <algorithm>
#include <fstream>
#include <cstdlib>

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

	delete _munchies;
	delete _pacman;

	delete _font;
	delete _pauseMessage;
	delete _messageString;
	delete _menuBackground;
}

void Game::LoadGame() {

	LoadWindow(); // Load the window.
	
	LoadText();   // Load the text.

	LoadEntities(); // Misc/Unsorted things.

	LoadExtras(); // Misc/Unsorted things.

	srand(time(NULL));
	for (int i = 0; i < munchieAmount; i++) {
		float& X = _res.x;
		float& Y = _res.y;
		_munchies[i]->SetPosition(sf::Vector2f(rand() % static_cast<int>(X), rand() % static_cast<int>(Y)));
	}

	srand(time(NULL));
	for (int i = 0; i < pelletAmount; i++) {
		float& X = _res.x;
		float& Y = _res.y;
		_pellets[i]->SetPosition(sf::Vector2f(rand() % static_cast<int>(X), rand() % static_cast<int>(Y)));
	}

	_fruit = new Fruit(APPLE);

	_fruit->SetPosition(sf::Vector2f(300, 300));

}

void Game::Update() {

	while (_window->isOpen()) {

		UpdateEvent();

		// MAIN GAME LOOP.
		if (_gameState == RUNNING && _gameState != PAUSED)
		{
			UpdateEntities();
		}

		Draw();
	}

}
void Game::Draw() {

	// Clear all drawn objects.
	_window->clear();

	// Drawing objects goes here!
	if (_gameState != MENU) {

		for (int i = 0; i < munchieAmount; i++) {
			if (!_munchies[i]->IsEaten())	_window->draw(_munchies[i]->GetSprite());
		}

		for (int i = 0; i < pelletAmount; i++) {
			if (!_pellets[i]->IsEaten())	_window->draw(_pellets[i]->GetSprite());
		}

		for (int i = 0; i < ghostAmount; i++) {
			_window->draw(_ghosts[i]->GetSprite());
		}

		_window->draw(_pacman->GetSprite());
		if (!_fruit->IsEaten())	_window->draw(_fruit->GetSprite());
		

		if (_gameState == PAUSED) {
			_window->draw(*_menuBackground);
			_window->draw(*_pauseMessage);
		}
	} else {
		_window->draw(*_menuBackground);
		_window->draw(*_pauseMessage);
	}

	// Display the drawn objects.
	_window->display();
}

void Game::PauseGame() {
	_gameState = PAUSED;
}


void Game::LoadWindow() {

	_view = new sf::View;

	_videomode = new sf::VideoMode(_res.x, _res.y, 32);
	_window = new sf::RenderWindow(*_videomode, "Pacman", sf::Style::Titlebar | sf::Style::Close);
	_window->setFramerateLimit(60);
}

void Game::LoadText() {

	_font = new sf::Font;

	_font->loadFromFile(_resourceDir + "Fonts/sansation.ttf");
	
	_pauseMessage = new sf::Text;

	_messageString = new std::string;

	_pauseMessage->setFont(*_font);
	_pauseMessage->setCharacterSize(40);

	_messageString->assign("Welcome to Pacman!\nPress space to start the game");

	_pauseMessage->setString(*_messageString);
	_pauseMessage->setFillColor(sf::Color::White);

	ResetOrigin(_pauseMessage);

	_pauseMessage->setPosition(_res.x / 2, _res.y / 2);

	_menuBackground = new sf::RectangleShape;
	_menuBackground->setSize(sf::Vector2f(_res.x, _res.y));
	_menuBackground->setFillColor(sf::Color(30, 30, 30, 130));
}

void Game::LoadEntities() {

	_pacman = new Pacman;

	for (int i = 0; i < munchieAmount; i++) {
		_munchies[i] = new Munchie;
	}

	for (int i = 0; i < pelletAmount; i++) {
		_pellets[i] = new PowerPellet;
	}

	for (int i = 0; i < ghostAmount; i++) {

		GhostType type(BLINKY);
		int typeGetter = (i + 1) % 4;

		switch (typeGetter) {
			case 0:
				type = BLINKY;
				break;
			case 1:
				type = INKY;
				break;
			case 2:
				type = PINKY;
				break;
			case 3:
				type = CLYDE;
				break;
		}

		_ghosts[i] = new Ghost(type);
		_ghosts[i]->SetPosition(sf::Vector2f(50.f * i + 32, _res.y / 2));
	}
}

void Game::LoadExtras() {

	_score = 0;

	_clock = new sf::Clock;

	_deltaTime = _clock->restart().asSeconds();

	_gameState = MENU;

}

void Game::UpdateEntities() {
	// Every tick, reset deltaTime.
	_deltaTime = _clock->restart().asSeconds();
	
	if (_scaredTimer > 0) {
		_scaredTimer--;
		if (!_scaredTimer) {
			for (int i = 0; i < ghostAmount; i++) {
				_ghosts[i]->CalmGhost();
			}
		}
	}

	for (int i = 0; i < munchieAmount; i++) {
		if(!_munchies[i]->IsEaten())	_munchies[i]->HandleCollision(_score, _pacman);
	}

	for (int i = 0; i < pelletAmount; i++) {
		if (!_pellets[i]->IsEaten())	_pellets[i]->HandleCollision(_score, _pacman, this);
	}
	
	for (int i = 0; i < ghostAmount; i++) {
		_ghosts[i]->UpdateGhost();
		_ghosts[i]->HandleCollision(_pacman);
	}

	if (!_fruit->IsEaten())	_fruit->HandleCollision(_score, _pacman);

	_pacman->UpdatePacman(_deltaTime);
}

void Game::UpdateEvent() {
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

				_messageString->assign("GAME PAUSED");
				_pauseMessage->setString(*_messageString);
				ResetOrigin(_pauseMessage);
				_pauseMessage->setPosition(_res.x / 2, _res.y / 2);
				_messageString->append("\nPress P to continue.\n\nPress R to restart.");

			}
			else if (_gameState == PAUSED) {
				_gameState = RUNNING;
				_clock->restart();
			}
		}

		if (((event.type == sf::Event::KeyReleased) && (event.key.code == sf::Keyboard::P)))	_pauseButtonBuffer = false;
	}
}


void Game::ScareGhosts() {
	for (int i = 0; i < ghostAmount; i++) {
		_ghosts[i]->SetScared();
	}
	
	_scaredTimer = scaredTime;

}


sf::Text* Game::ResetOrigin(sf::Text* text) {
		sf::FloatRect textRect = text->getLocalBounds();
		text->setOrigin(textRect.left + textRect.width / 2.0f, textRect.top + textRect.height / 2.0f);
		return text;
}