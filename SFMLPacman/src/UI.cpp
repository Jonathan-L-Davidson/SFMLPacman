#include "UI.h"
#include "Global.hpp"
#include <string>

Resolution _res;

UI::UI() {
	_font = new sf::Font;
	_font->loadFromFile(_resourceDir + "Fonts/sansation.ttf");

	_1up = new sf::Text;
	_score = new sf::Text;
	_highScore = new sf::Text;

	_1up->setFont(*_font);
	_score->setFont(*_font);
	_highScore->setFont(*_font);

	_1upString = new std::string;
	_scoreString = new std::string;
	_highScoreString = new std::string;

	_1up->setString(*_1upString);
	_score->setString(*_scoreString);
	_highScore->setString(*_highScoreString);

	_1up->setPosition(sf::Vector2f(_res.x / 4, 20));
	_score->setPosition(sf::Vector2f(_res.x / 3, 20));
	_score->setPosition(sf::Vector2f(_res.x / 3, 20));


}

void UI::Update(int* score) {
	_scoreString->assign(std::to_string(*score));
}

void UI::Draw(sf::RenderWindow* window) {
	window->draw(*_1up);
	window->draw(*_score);
	window->draw(*_highScore);
}

UI::~UI() {
	delete _1up;
	delete _score;
	delete _highScore;

	delete _1upString;
	delete _scoreString;
	delete _highScoreString;
}