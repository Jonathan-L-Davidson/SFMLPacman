// Early iteration of Pacman made from scratch in SFML.
//
// TO DO:
// Organise code into different files.
// Tidy code.
// Follow each week's tutorial.
// Make a more optimised way to open and close pacman's mouth.
// Pause menu.
// UI.
// Map creation.
// Enemies.
// AI.
// Score.
// Smooth edge wraps.


// HEADERS
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <cmath>
#include <ctime>
#include <cstdlib>
#include <iostream>

// GLOBAL CONSTS
#define dirRIGHT 0
#define dirDOWN 32
#define dirLEFT 64
#define dirUP 96

// MISC APPLICATION DEFS
std::string resourcesDir = "resources/";
struct resolution { float x = 800.0f; float y = 600.0f; };

// MAIN
int main() {

	std::srand(static_cast<unsigned int>(std::time(NULL)));


	// Define some constants
	const float pi = 3.14159f;
	const float pacmanSpeed = 150.0f;

	resolution res;


	// Create the window of the application
	sf::RenderWindow window(sf::VideoMode(res.x, res.y, 32), "SFML Pacman", sf::Style::Titlebar | sf::Style::Close);
	window.setVerticalSyncEnabled(true);

	// Load the text font
	sf::Font font;
	if (!font.loadFromFile(resourcesDir + "sansation.ttf"))
		return EXIT_FAILURE;

	sf::Texture pacmanTexture;
	if (!pacmanTexture.loadFromFile(resourcesDir + "Sprites/pacman.tga"))
		return EXIT_FAILURE;

	int openMouth = 32;
	sf::Vector2f pacmanSize(32, 32);

	// Create a sprite that will display the texture
	sf::Sprite pacmanSprite(pacmanTexture);
	pacmanSprite.setTextureRect(sf::IntRect(0, 0, pacmanSize.x, pacmanSize.y));
	pacmanSprite.setPosition(5.0f, 5.0f);
	pacmanSprite.setOrigin(pacmanSize / 2.f);

	int pacmanDirection = dirUP;


	// Initialize the pause message
	sf::Text pauseMessage;
	pauseMessage.setFont(font);
	pauseMessage.setCharacterSize(40);
	pauseMessage.setPosition(170.f, 150.f);
	pauseMessage.setFillColor(sf::Color::White);
	pauseMessage.setString("Welcome to Pacman!\nPress space to start the game");

	sf::Clock clock;
	bool isPlaying = false;
	int frameTicker = 0;

	// Temporary game loop.
	while (window.isOpen())
	{
		// Event value to store incoming events.
		sf::Event event;
		while (window.pollEvent(event))
		{
			// CLOSE WINDOW - ESC / CLOSE WINDOW
			if ((event.type == sf::Event::Closed) ||
				((event.type == sf::Event::KeyPressed) && (event.key.code == sf::Keyboard::Escape)))
			{
				window.close();
				break;
			}

			// If the window resize has changed somehow, force the viewport to be the screen's resolution. Prevents distortion.
			if (event.type == sf::Event::Resized)
			{
				sf::View view;
				view.setSize(res.x, res.y);
				view.setCenter(res.x / 2, res.y / 2);
				window.setView(view);
			}
		
			// PLAY - SPACEBAR
			if (((event.type == sf::Event::KeyPressed) && (event.key.code == sf::Keyboard::Space)))
			{
				if (!isPlaying)
				{
					// Start the game 
					isPlaying = true;
					clock.restart();
				}
			}


		}

		if (isPlaying)
		{
			// Every tick, reset deltaTime.
			float deltaTime = clock.restart().asSeconds();
			

			// Every 75 frames open/close pacman's mouth.
			if (frameTicker > 75) {
				openMouth = openMouth ? 0 : 32; // If openMouth has a value, set it to 0, if not, set it to 32.
				frameTicker = 0;
			}else{
				frameTicker++;
			}

			// MOVE UP - UP ARROW
			if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up) && (pacmanSprite.getPosition().y - pacmanSize.y / 2 > 0))
			{
				pacmanDirection = dirUP;
				pacmanSprite.move(0.f, -pacmanSpeed * deltaTime);
			}

			// MOVE RIGHT - RIGHT ARROW
			if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right) && (pacmanSprite.getPosition().x + pacmanSize.x / 2 < res.x))
			{
				pacmanDirection = dirRIGHT;
				pacmanSprite.move(pacmanSpeed * deltaTime, 0.0f);
			}

			// MOVE LEFT - LEFT ARROW
			if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left) && (pacmanSprite.getPosition().x - pacmanSize.x / 2 > 0))
			{
				pacmanDirection = dirLEFT;
				pacmanSprite.move(-pacmanSpeed * deltaTime, 0.0f);
			}

			// MOVE DOWN - DOWN ARROW
			if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down) && (pacmanSprite.getPosition().y + pacmanSize.y / 2 < res.y))
			{
				pacmanDirection = dirDOWN;
				pacmanSprite.move(0.f, pacmanSpeed * deltaTime);
			}

			// ROTATE - R KEY
			if (sf::Keyboard::isKeyPressed(sf::Keyboard::R))
			{
				pacmanSprite.rotate(7500.0f * deltaTime);
			}

		}



		// Clear all drawn objects.
		window.clear();

		// Drawing objects goes here!

		if (isPlaying)
		{
			// Draw Pacman!
			pacmanSprite.setTextureRect(sf::IntRect(openMouth, pacmanDirection, 32, 32));
			window.draw(pacmanSprite);
			
		}
		else
		{
			// Draw the pause message
			window.draw(pauseMessage);
		}

		// Display the drawn objects.
		window.display();
	}
}