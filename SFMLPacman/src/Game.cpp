#include "headers/Game.h"
#include "headers/Entities.h"
#include "headers/Game.h"
#include "headers/Sound.h"
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

	LoadLevel(); // Load Hell.

	LoadExtras(); // Misc/Unsorted things.

	srand(time(NULL));
	for (int i = 0; i < munchieAmount; i++) {
		float& X = _res.x;
		float& Y = _res.y;
		_munchies[i]->SetPosition(sf::Vector2f(rand() % static_cast<int>(X), rand() % static_cast<int>(Y)));
	}

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

		switch (_gameState) {
			case STARTING:
				StartGame();
				break;
			case FROZEN:
				if (_timeFrozen <= 0) {
					_gameState = RUNNING;
					_clock->restart();
				}
				_timeFrozen--;
				break;
			case RUNNING:
				UpdateEntities();
				break;
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

void Game::LoadLevel() {

	// Used from S2D Platformer.

	// --- S2D PLATFORMER CODE START ---
	// Load the level and ensure all of the lines are the same length.
	int width;
	std::vector<std::string>* lines = new std::vector<std::string>();
	std::fstream stream;
	std::stringstream ss;
	ss << _resourceDir + "level.txt";
	stream.open(ss.str(), std::fstream::in);

	char* line = new char[256];
	stream.getline(line, 256);
	std::string* sline = new std::string(line);
	width = sline->size();
	std::cout << width;
	while (!stream.eof())
	{
		lines->push_back(*sline);
		if (sline->size() != width)
			std::cout << "Bad Level Load\n";
		stream.getline(line, 256);
		delete sline;
		sline = new std::string(line);
	}

	delete[] line;
	delete sline;

	// Allocate the tile grid.
	_tiles = new std::vector<std::vector<Tile*>>(width, std::vector<Tile*>(lines->size()));

	// Loop over every tile position,
	for (int y = 0; y < _tiles->at(0).size(); y++)
	{
		for (int x = 0; x < width; x++)
		{
			// to load each tile.
			char tileType = (*lines)[y].at(x);

			// Edit: to work with my Tile system. - Jon
			(*_tiles)[x][y] = new Tile(); 
			(*_tiles)[x][y]->LoadTile(TileCharToType(tileType), sf::Vector2i(x, y), this);
		}
	}

	delete lines;
	// --- S2D PLATFORMER CODE END ---

}

void Game::LoadExtras() {

	_score = 0;

	_clock = new sf::Clock;

	_deltaTime = _clock->restart().asSeconds();

	_gameState = MENU;

	_sound = new Sound;

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
		if (!_munchies[i]->IsEaten())	_munchies[i]->HandleCollision(_score, _pacman, this);
	}

	for (int i = 0; i < pelletAmount; i++) {
		if (!_pellets[i]->IsEaten()) {
			_pellets[i]->UpdateSprite();
			_pellets[i]->HandleCollision(_score, _pacman, this);
		}
	}

	for (int i = 0; i < ghostAmount; i++) {
		_ghosts[i]->UpdateGhost();
		_ghosts[i]->HandleCollision(_pacman, this);
	}

	if (!_fruit->IsEaten())	_fruit->HandleCollision(_score, _pacman, this);

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
		if (event.type == sf::Event::KeyPressed) {
			if ((event.key.code == sf::Keyboard::Space) && _gameState == MENU) {
				// Start the game 
				_sound->PlayMusic("startingmusic.wav", 0);
				_gameState = STARTING;
			}

			if ((event.key.code == sf::Keyboard::P) && !_pauseButtonBuffer) {
				if (_gameState == RUNNING) {
					Pause();
				}
				else if (_gameState == PAUSED) {
					UnPause();
				}
			}
		}

		if (((event.type == sf::Event::KeyReleased) && (event.key.code == sf::Keyboard::P)))	_pauseButtonBuffer = false;
	}
}

void Game::StartGame() {
	if (_sound->GetMusicState() != 2) { // 2 = Playing
		_gameState = RUNNING;
		_clock->restart();
	}
}

void Game::Pause() {
	_gameState = PAUSED;
	_pauseButtonBuffer = true;

	_messageString->assign("GAME PAUSED");
	_pauseMessage->setString(*_messageString);
	ResetOrigin(_pauseMessage);
	_pauseMessage->setPosition(_res.x / 2, _res.y / 2);
	_messageString->append("\nPress P to continue.\n\nPress R to restart.");
	
	_sound->PlaySound("pause.wav");
}

void Game::UnPause() {
	_gameState = RUNNING;
	_clock->restart();
	_sound->PlaySound("unpause.wav");
}

void Game::FreezeGame(const int& time) {
	if (_gameState == FROZEN) return;

	_gameState = FROZEN;
	_timeFrozen = time;
}

void Game::ScareGhosts() {
	for (int i = 0; i < ghostAmount; i++) {
		_ghosts[i]->SetScared();
	}
	
	_scaredTimer = scaredTime;

}

void Game::PlaySound(const std::string& input) {
	_sound->PlaySound(input);
}

TileType Game::TileCharToType(char& type) {
	switch (type) {
		case 'P':
			return PACMAN;
			break;
		case '#':
			return MUNCHIE;
			break;
		case '@':
			return PELLET;
			break;
		case 'G':
			return GHOST;
			break;
		case 'D':
			return GHOSTDOOR;
			break;
		case 'F':
			return FRUIT;
			break;
		case 'S':
			return WALLS;
			break;
		case 'T':
			return WALLT;
			break;
		case 'C':
			return WALLC;
			break;
		case 'E':
			return WALLE;
			break;
		default:
			return MUNCHIE;
			break;
	}
}


sf::Text* Game::ResetOrigin(sf::Text* text) {
		sf::FloatRect textRect = text->getLocalBounds();
		text->setOrigin(textRect.left + textRect.width / 2.0f, textRect.top + textRect.height / 2.0f);
		return text;
}
