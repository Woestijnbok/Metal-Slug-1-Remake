#include "base.h"
#include "PowerUpManager.h"
#include "SoundEffect.h"

PowerUpManager::PowerUpManager() :
	m_pItems{},
	m_PtrPowerUpHitSoundEffect{ new SoundEffect{ "Sounds/powerUp.mp3" } }
{
}

PowerUpManager::~PowerUpManager()
{
	for (PowerUp* ptrPowerUp : m_pItems)
	{
		delete ptrPowerUp;
	}

	m_pItems.clear();
}

PowerUp* PowerUpManager::AddItem(const Point2f& center, PowerUp::Type type)
{
	PowerUp* ptrPowerUp = new PowerUp{ center, type };
	m_pItems.push_back(ptrPowerUp);
	return ptrPowerUp;
}

void PowerUpManager::Update(float elapsedSec)
{
	for (PowerUp* ptrPowerUp : m_pItems)
	{
		ptrPowerUp->Update(elapsedSec);
	}
}

void PowerUpManager::Draw() const
{
	for (PowerUp* ptrPowerUp : m_pItems)
	{
		ptrPowerUp->Draw();
	}
}

size_t PowerUpManager::Size() const
{
	return m_pItems.size();
}

bool PowerUpManager::HitItem(const Rectf& rect)
{
	for (int index{}; index < Size(); ++index)
	{
		if (m_pItems[index]->IsOverlapping(rect))
		{
			delete m_pItems[index];
			m_pItems[index] = nullptr;

			m_pItems[index] = m_pItems[Size() - 1];
			m_pItems.pop_back();
			m_PtrPowerUpHitSoundEffect->Play(0);

			return true;
		}
	}

	return false;
}