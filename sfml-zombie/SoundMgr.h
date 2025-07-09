#pragma once
#include "Singleton.h"



class SoundMgr : public Singleton<SoundMgr>
{
	friend Singleton<SoundMgr>;
protected:
	SoundMgr() = default;
	~SoundMgr() = default;

	std::vector<sf::SoundBuffer> soundBuffers;
	std::vector<sf::Sound> sounds;
	std::vector<std::string> audioIds;

public:
	void Init();
	void Play(Audio id);
};

#define SOUND_MGR SoundMgr::Instance()
