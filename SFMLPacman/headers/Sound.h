#pragma once
#include "Global.hpp"

class Sound {
private:
	sf::SoundBuffer* _buffer;

	sf::Sound* _sound;
	sf::Music* _music;

	std::string _resourceDir;

public:

	Sound();
	~Sound();
	
	void PlaySound(const std::string& input);
	void PlayMusic(const std::string& input, bool loop);
	void StopMusic();
	void PauseMusic();
	void ResumeMusic();
	sf::SoundStream::Status GetMusicState() const { return _music->getStatus(); }

};