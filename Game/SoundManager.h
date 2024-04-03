#pragma once
#include "SoundStream.h"
#include "SoundEffect.h"
#include <unordered_map>


class SoundManager final
{
public:
	explicit SoundManager();
	~SoundManager();

	SoundManager(const SoundManager&) = delete;
	SoundManager& operator=(const SoundManager&) = delete;
	SoundManager(SoundManager&&) = delete;
	SoundManager& operator=(SoundManager&&) = delete;

	void SetBossMusic();
	void PistolShot();
	void RifleShot();
	void PlasmaShot();
	void PlasmaBeam();
	void PlayerDeath();
	void EnemeyDeath();
	void ChangeVolume(bool increase);
	void MenuClick();
	void Reset();

private:
	std::unordered_map<std::string, SoundEffect*> m_Effects;
	std::unordered_map<std::string, SoundStream*> m_Streams;
};

