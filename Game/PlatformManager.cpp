#include "pch.h"
#include "PlatformManager.h"
#include "Platform.h"
#include "SVGParser.h"

PlatformManager::PlatformManager() :
	m_Platforms{}
{
	m_Platforms.push_back(new Platform{ Rectf{ 860.0f, 60.0f, 60.0f, 2.0f } });
	m_Platforms.push_back(new Platform{ Rectf{ 940.0f, 100.0f, 170.0f, 2.0f } });
	m_Platforms.push_back(new Platform{ Rectf{ 1115.0f, 60.0f, 60.0f, 2.0f } });
	m_Platforms.push_back(new Platform{ Rectf{ 1175.0f, 102.0f, 140.0f, 2.0f } });
	m_Platforms.push_back(new Platform{ Rectf{ 1360.0f, 102.0f, 160.0f, 2.0f } });
	m_Platforms.push_back(new Platform{ Rectf{ 1530.0f, 62.0f, 65.0f, 2.0f } });
	m_Platforms.push_back(new Platform{ Rectf{ 2075.0f, 94.0f, 70.0f, 2.0f } });
	m_Platforms.push_back(new Platform{ Rectf{ 2160.0f, 142.0f, 40.0f, 2.0f } });
	m_Platforms.push_back(new Platform{ Rectf{ 2265.0f, 334 - 240.0f, 70.0f, 2.0f } });
	m_Platforms.push_back(new Platform{ Rectf{ 2352.0f, 334 - 201.0f, 40.0f, 2.0f } });
	m_Platforms.push_back(new Platform{ Rectf{ 2396.0f, 334 - 192.0f, 140.0f, 2.0f } });
	m_Platforms.push_back(new Platform{ Rectf{ 2463.0f, 334 - 231.0f, 35.0f, 2.0f } });
	m_Platforms.push_back(new Platform{ Rectf{ 2446.0f, 334 - 271.0f, 35.0f, 2.0f } });
	m_Platforms.push_back(new Platform{ Rectf{ 2584.0f, 334 - 232.0f, 75.0f, 2.0f } });
	m_Platforms.push_back(new Platform{ Rectf{ 2695.0f, 334 - 191.0f, 50.0f, 2.0f } });
	m_Platforms.push_back(new Platform{ Rectf{ 3872.0f, 188.0f, 30.0f, 2.0f } });
	m_Platforms.push_back(new Platform{ Rectf{ 3905.0f, 220.0f, 41.0f, 2.0f } });
}

PlatformManager::~PlatformManager()
{
	for (auto ptrPlatform : m_Platforms)
	{
		delete ptrPlatform;
	}

	m_Platforms.clear();
}

void PlatformManager::HandleCollision(Rectf& actorHitbox, Vector2f& actorVelocity) const
{
	for (auto ptrPlatform : m_Platforms)
	{
		ptrPlatform->HandleCollision(actorHitbox, actorVelocity);
	}
}

bool PlatformManager::IsOnGround(const Rectf& actorHitbox, const Vector2f& actorVelocity) const
{
	for (auto ptrPlatform : m_Platforms)
	{
		if (ptrPlatform->IsOnGround(actorHitbox, actorVelocity))
		{
			return true;
		}
	}
	
	return false;
}

void PlatformManager::DrawDebug() const
{
	for (auto ptrPlatform : m_Platforms)
	{
		ptrPlatform->DrawDebug();
	}
}