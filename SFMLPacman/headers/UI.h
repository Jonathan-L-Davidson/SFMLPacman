#pragma once
#include "Global.hpp"

class UI {
	private:
		const std::string _resourceDir = resourceDir;

		sf::Font* _font;


		std::string* _1upString;
		std::string* _scoreString;
		std::string* _highScoreString;

		int* gameScore;

	public:

		sf::Text* _1up;
		sf::Text* _score;
		sf::Text* _highScore;

		UI();
		~UI();

		int GetHighScore(int* highscore);

		void Update(int* score);
		void Draw(sf::RenderWindow* window);

};