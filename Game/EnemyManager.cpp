#include "base.h"
#include "EnemyManager.h"
#include "utils.h"
#include "Enemy.h"
#include "Level.h"
#include "Avatar.h"
#include "ProjectileManager.h"
#include "Projectile.h"
#include "SoundManager.h"

EnemyManager::~EnemyManager()
{
	for (auto ptrEnemy : m_Enemies)
	{
		delete ptrEnemy;
	}

	m_Enemies.clear();
}

void EnemyManager::Update(float elapsedSeconds)
{
	for (auto ptrEnemy : m_Enemies)
	{
		ptrEnemy->Update(elapsedSeconds);

		if (ptrEnemy->NeedsToBeDeleted())
		{
			Pop(ptrEnemy);
		}
	}
}

void EnemyManager::Draw() const
{
	for (auto ptrEnemy : m_Enemies)
	{
		ptrEnemy->Draw();
	}
}

void EnemyManager::DrawDebug() const
{
	const Color4f red{ 1.0f, 0.0f, 0.0f, 0.7f };
	utils::SetColor(red);

	for (auto ptrEnemy : m_Enemies)
	{
		ptrEnemy->DrawDebug();
	}
}

void EnemyManager::Pushback(Enemy* const ptrEnemy)
{
	m_Enemies.push_back(ptrEnemy);
}

void EnemyManager::Pop(Enemy* ptrEnemy)
{
	for (auto& ptr : m_Enemies)
	{
		if (ptr == ptrEnemy)
		{
			delete ptr;
			ptrEnemy = nullptr; // To be sure we are not trying to read at a deleted object location
			ptr = m_Enemies[m_Enemies.size() - 1];
			m_Enemies.pop_back();

			return;
		}
	}

	delete ptrEnemy;
	ptrEnemy = nullptr;
}

bool EnemyManager::IsAnyEnemyHit(const Projectile* const ptrProjectile) const
{
	for (auto ptrEnemy : m_Enemies)
	{
		if (utils::IsOverlapping(ptrEnemy->GetHitbox(), ptrProjectile->GetHitbox()))
		{
			ptrEnemy->Hit(ptrProjectile->GetDamage());
			return true;
		}
	}

	return false;
}

void EnemyManager::Reset()
{
	for (auto ptrEnemy : m_Enemies)
	{
		delete ptrEnemy;
	}

	m_Enemies.clear();
}