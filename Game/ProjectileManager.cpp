#include "base.h"
#include "ProjectileManager.h"
#include "iostream"
#include "utils.h"
#include "Avatar.h"
#include "EnemyManager.h"
#include "Projectile.h"
#include "Bullet.h"
#include "Plasma.h"
#include "LaserBolt.h"
#include "Level.h"

void ProjectileManager::SetGameInformation(const Level& level, Avatar& player, EnemyManager& enemyManager)
{
	m_PtrLevel = &level;
	m_PtrPlayer = &player;
	m_PtrEnemyManager = &enemyManager;
}

ProjectileManager::~ProjectileManager()
{
	for (auto ptrProjectile : m_Projectiles)
	{
		delete ptrProjectile;
	}

	m_Projectiles.clear();
}

void ProjectileManager::Update(float elapsedSeconds)
{
	for (auto ptrProjectile : m_Projectiles)
	{
		ptrProjectile->Update(elapsedSeconds);

		const Rectf hitbox{ ptrProjectile->GetHitbox() };

		if (!utils::IsOverlapping(m_PtrLevel->GetBoundaries(), hitbox) || utils::IsOverlapping(m_PtrLevel->GetGround(), hitbox))
		{
			Pop(ptrProjectile);
		}
		else if (dynamic_cast <Bullet*> (ptrProjectile) != nullptr)
		{
			if (m_PtrEnemyManager->IsAnyEnemyHit(ptrProjectile)) // The bullet hit an enemy
			{
				Pop(ptrProjectile);
			}
		}
		else
		{
			if (utils::IsOverlapping(m_PtrPlayer->GetHitbox(), ptrProjectile->GetHitbox())) // The bullet hit the player
			{
				m_PtrPlayer->Hit(ptrProjectile->GetDamage());
				Pop(ptrProjectile);
			}
		}
	}
}

void ProjectileManager::Draw() const
{
	for (auto ptrProjectile : m_Projectiles)
	{
		ptrProjectile->Draw();
	}
}

void ProjectileManager::DrawDebug() const
{
	const Color4f red{1.0f, 0.0f, 0.0f, 1.0f};
	utils::SetColor(red);

	for (auto ptrProjectile : m_Projectiles)
	{
		ptrProjectile->DrawDebug();
	}
}

void ProjectileManager::Pushback(Projectile* const ptrProjectile)
{
	m_Projectiles.push_back(ptrProjectile);
}

void ProjectileManager::Pop(Projectile* ptrProjectile)
{
	for (auto& ptr : m_Projectiles)
	{
		if (ptr == ptrProjectile)
		{
			delete ptr;
			ptrProjectile = nullptr; // To be sure we are not trying to read at a deleted object location
			ptr = m_Projectiles[m_Projectiles.size() - 1];
			m_Projectiles.pop_back();
			return;
		}
	}

	delete ptrProjectile;
	ptrProjectile = nullptr;
}

void ProjectileManager::Reset()
{
	for (auto ptrProjectile : m_Projectiles)
	{
		delete ptrProjectile;
	}

	m_Projectiles.clear();
}