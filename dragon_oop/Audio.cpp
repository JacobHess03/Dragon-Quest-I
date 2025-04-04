// ----------------------------------------------------------------
// From "Algorithms and Game Programming" in C++ by Alessandro Bria
// Copyright (C) 2023 Alessandro Bria (a.bria@unicas.it). 
// All rights reserved.
// 
// Released under the BSD License
// See LICENSE in root directory for full details.
// ----------------------------------------------------------------

#include "Audio.h"
#include "SDL.h"
#include "fileUtils.h"
#include <iostream>

using namespace agp;

Audio* Audio::instance()
{
	static Audio uniqueInstance;

	return &uniqueInstance;
}

Audio::Audio()
{
	if (SDL_Init(SDL_INIT_AUDIO))
		throw SDL_GetError();

	if(Mix_OpenAudio(MIX_DEFAULT_FREQUENCY, MIX_DEFAULT_FORMAT, MIX_DEFAULT_CHANNELS, 512))
		throw Mix_GetError();

	auto soundFiles = getFilesInDirectory("Audio");
	for (auto& f : soundFiles)
	{
		std::string name = getFileName(f, false);

		Mix_Chunk* chunk = Mix_LoadWAV(("Audio/" + f).c_str());
		if (!chunk)
			std::cerr << Mix_GetError() << "\n";
		else
			_sounds[name] = chunk;
	}

	auto musicFiles = getFilesInDirectory("Audio");
	for (auto& f : musicFiles)
	{
		std::string name = getFileName(f, false);

		Mix_Music* music = Mix_LoadMUS(("Audio/" + f).c_str());
		if (!music)
			std::cerr << Mix_GetError() << "\n";
		else
			_musics[name] = music;
		

	}
	std::cout << "Chunk size: " << _sounds.size() << std::endl;
}

Audio::~Audio()
{
	for (auto& entry : _musics)
		Mix_FreeMusic(entry.second);
	for (auto& entry : _sounds)
		Mix_FreeChunk(entry.second);
	Mix_CloseAudio();
}

void Audio::playSound(const std::string& id, int loops)
{
	if (_sounds.find(id) == _sounds.end())
	{
		std::cerr << "Cannot find sound \"" << id << "\"\n";
		return;
	}
	Mix_PlayChannel(-1, _sounds[id], loops);
}

void Audio::playMusic(const std::string& id, int loops)
{
	if (_musics.find(id) == _musics.end())
	{
		std::cerr << "Cannot find music \"" << id << "\"\n";
		return;
	}
	
	Mix_PlayMusic(_musics[id], loops);
}

void Audio::resumeMusic()
{
	Mix_ResumeMusic();
}

void Audio::pauseMusic()
{
	Mix_PauseMusic();
}


void Audio::haltMusic()
{
	Mix_HaltMusic();
}
void Audio::setMusicVolume(int n) {
	Mix_VolumeMusic(n);

}
void Audio::setChunkVolume(int n,int volume) {
	for (auto& entry : _sounds)
		volume=Mix_VolumeChunk(entry.second, n);
}
int Audio::getChunkVolume() {
	return Mix_Volume(-1,-1);

}
int Audio::getMusicVolume() {
	return Mix_VolumeMusic(-1);
}