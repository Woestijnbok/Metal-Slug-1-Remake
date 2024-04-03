#include "pch.h"
#include "SoundManager.h"

SoundManager::SoundManager() :
	m_Effects{},
	m_Streams{}
{
	// Initializing background music
	m_Streams["Default"] = new SoundStream{ "Sound/General Music.mp3" };
	m_Streams["Boss"] = new SoundStream{ "Sound/Boss Music.mp3" };
	m_Streams["Default"]->SetVolume(5);
	m_Streams["Boss"]->SetVolume(5);
	m_Streams["Default"]->Play(true);

	// Initiazling sound effects
	m_Effects["Player Death"] = new SoundEffect{ "Sound/Player Death.mp3" };
	m_Effects["Enemy Death"] = new SoundEffect{ "Sound/Enemy Death.mp3" };
	m_Effects["Pistol Shot"] = new SoundEffect{ "Sound/Gun Shot.mp3" };
	m_Effects["Rifle Shot"] = new SoundEffect{ "Sound/Rifle Shot.mp3" };
	m_Effects["Plasma Shot"] = new SoundEffect{ "Sound/Plasma Shot.mp3" };
	m_Effects["Plasma Beam"] = new SoundEffect{ "Sound/Plasma Beam.mp3" };
	m_Effects["Menu Click"] = new SoundEffect{ "Sound/Menu Click.wav" };
	m_Effects["Player Death"]->SetVolume(20);
	m_Effects["Enemy Death"]->SetVolume(5);
	m_Effects["Pistol Shot"]->SetVolume(5);
	m_Effects["Rifle Shot"]->SetVolume(5);
	m_Effects["Plasma Shot"]->SetVolume(5);
	m_Effects["Plasma Beam"]->SetVolume(40);
	m_Effects["Menu Click"]->SetVolume(20);
}

SoundManager::~SoundManager()
{
	for (auto& effect : m_Effects)
	{
		delete effect.second;
		effect.second = nullptr;
	}

	for (auto& stream : m_Streams)
	{
		delete stream.second;
		stream.second = nullptr;
	}
}

void SoundManager::SetBossMusic()
{
	m_Streams["Default"]->Stop();
	m_Streams["Boss"]->Play(true);
}

void SoundManager::PistolShot()
{
	m_Effects["Pistol Shot"]->Play(0);
}

void SoundManager::RifleShot()
{
	m_Effects["Rifle Shot"]->Play(0);
}

void SoundManager::PlasmaShot()
{
	m_Effects["Plasma Shot"]->Play(0);
}

void SoundManager::PlasmaBeam()
{
	m_Effects["Plasma Beam"]->Play(0);
}

void SoundManager::PlayerDeath()
{
	m_Effects["Player Death"]->Play(0);
}

void SoundManager::EnemeyDeath()
{
	m_Effects["Enemy Death"]->Play(0);
}

void SoundManager::ChangeVolume(bool increase)
{
	for (auto& effect : m_Effects)
	{
		if (increase)
		{
			effect.second->SetVolume(effect.second->GetVolume() + 1);
		}
		else
		{
			effect.second->SetVolume(effect.second->GetVolume() - 1);
		}
	}

	for (auto& stream : m_Streams)
	{
		if (increase)
		{
			stream.second->SetVolume(stream.second->GetVolume() + 1);
		}
		else
		{
			stream.second->SetVolume(stream.second->GetVolume() - 1);
		}
	}
}

void SoundManager::MenuClick()
{
	m_Effects["Menu Click"]->Play(0);
}

void SoundManager::Reset()
{
	for (auto& effect : m_Effects)
	{
		effect.second->StopAll();
	}

	for (auto& stream : m_Streams)
	{
		stream.second->Stop();
	}

	m_Streams["Default"]->Play(true);
}