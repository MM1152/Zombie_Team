#include "stdafx.h"
#include "SoundMgr.h"

void SoundMgr::Init()
{
	audioIds.push_back("sound/hit.wav");
	audioIds.push_back("sound/pickup.wav");
	audioIds.push_back("sound/powerup.wav");
	audioIds.push_back("sound/reload.wav");
	audioIds.push_back("sound/reload_failed.wav");
	audioIds.push_back("sound/shoot.wav");
	audioIds.push_back("sound/splat.wav");

	for (int i = 0; i < audioIds.size(); i++) {
		sf::SoundBuffer soundBuffer;
		soundBuffer.loadFromFile(audioIds[i]);
		soundBuffers.push_back(soundBuffer);
	}
	for (int i = 0; i < soundBuffers.size(); i++) {
		sf::Sound sound;
		sound.setBuffer(soundBuffers[i]);
		sounds.push_back(sound);
	}
}

void SoundMgr::Play(Audio id)
{
	sounds[(int)id].play();
}
