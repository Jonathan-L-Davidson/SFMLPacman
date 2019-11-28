#include "Game.h"
#include "Entities.h"
#include "Tile.h"
#include <algorithm>
#include <fstream>

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

	delete _tiles;

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

void Game::LoadTiles(int levelIndex)
{
	// Load the level and ensure all of the lines are the same length.
	int width;
	std::vector<std::string>* lines = new std::vector<std::string>();

	std::fstream stream;

	std::string ss;
	ss = _resourceDir + std::to_string(levelIndex) + ".txt";
	stream.open(ss, std::fstream::in);

	char* line = new char[256];
	stream.getline(line, 256);
	std::string* sline = new std::string(line);
	width = sline->size();
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
	for (int y = 0; y < GetHeight(); ++y)
	{
		for (int x = 0; x < GetWidth(); ++x)
		{
			// to load each tile.
			char tileType = lines->at(y)[x];
			(*_tiles)[x][y] = LoadTile(tileType, x, y);
		}
	}

	delete lines;
}

Tile* Game::LoadTile(const char tileType, int x, int y)
{
	switch (tileType)
	{
		// Blank space
	case '.':
		return new Tile(nullptr, TileCollision::Passable);

		// Munchie
	case 'M':
		return LoadTile("Munchie", TileCollision::Passable);

		// Floating platform
	case 'C':
		return LoadTile("Cherry", TileCollision::Passable);

		// Various enemies
	case 'G':
		return LoadGhostStartTile(x, y);
		
		// Wall
	case '#':
		return LoadTile("Wall", TileCollision::Impassable);

		// Player 1 start point
	case '1':
		return LoadStartTile(x, y);

		// Unknown tile type character
	default:
		std::cout << "Unsupported tile type character " << tileType;
		return nullptr;
	}
}

Tile* Game::LoadTile(const char name, TileCollision collision)
{
	std::string ss;
	ss = "Content/Tiles/" + name + ".png";

	sf::Texture* tex = new sf::Texture;
	tex->loadFromFile(ss);
	sf::Sprite* sprite = new sf::Sprite;
	sprite->setTexture(*tex);
	return new Tile(sprite, collision);
}

Tile* Game::LoadStartTile(int x, int y)
{
	if (_pacman != nullptr)
		std::cout << "A level may only have one starting point.";

	
	_pacman->SetPosition(sf::Vector2f(x, y));

	return new Tile(nullptr, TileCollision::Passable);
}


Tile* Game::LoadGhostStartTile(int x, int y)
{
	/* TO DO - Program ghosties
	Vector2 position = RectangleExtensions::GetBottomCenter(&(GetBounds(x, y)));
	_enemies.push_back(new Enemy(this, position, spriteSet));

	return new Tile(nullptr, TileCollision::Passable);
	*/
}

/*
Tile* Game::LoadEdibleTile(int x, int y, EdibleType tileType)
{
	sf::Vector2i position = sf::Vector2i(x, y);
	_edibles.push_back(new Edible(this, new Vector2(position.X, position.Y)));

	return new Tile(nullptr, TileCollision::Passable);
}*/

TileCollision Game::GetCollision(int x, int y)
{
	// Prevent escaping past the level ends.
	if (x < 0 || x >= GetWidth())
		return TileCollision::Impassable;
	// Allow jumping past the level top and falling through the bottom.
	if (y < 0 || y >= GetHeight())
		return TileCollision::Passable;

	return _tiles->at(x).at(y)->Collision;
}

