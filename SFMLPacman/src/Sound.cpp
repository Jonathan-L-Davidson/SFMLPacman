#include "Sound.h"

Sound::Sound() {
	_buffer = new sf::SoundBuffer;
	_sound = new sf::Sound;
	_music = new sf::Music;

	_resourceDir = resourceDir;

	_sound->setBuffer(*_buffer);
}
Sound::~Sound() {
	delete _buffer;
	delete _sound;
	delete _music;
}

void Sound::PlaySound(const std::string& input) {
	_buffer->loadFromFile(_resourceDir + "sounds/" + input);
	_sound->play();
}

void Sound::PlayMusic(const std::string& input, bool loop) {
	_music->openFromFile(_resourceDir + "music/" + input);
	_music->play();
}

void Sound::StopMusic() {
	_music->stop();
}

void Sound::PauseMusic() {
	_music->pause();
}

void Sound::ResumeMusic() {
	_music->play();
}
