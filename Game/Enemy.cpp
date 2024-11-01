#include "base.h"
#include "Enemy.h"
#include "EnemyManager.h"
#include "ProjectileManager.h"
#include "Level.h"
#include "Avatar.h"
#include "SoundManager.h"

const Level* Enemy::m_PtrLevel{ nullptr };
const Avatar* Enemy::m_PtrPlayer{ nullptr };
const EnemyManager* Enemy::m_PtrEnemyManager{ nullptr };
ProjectileManager* Enemy::m_PtrProjectileManager{ nullptr };
SoundManager* Enemy::m_PtrSoundManager{ nullptr };

void Enemy::SetGameInformation(const Level& level, const Avatar& player, const EnemyManager& enemyManager, ProjectileManager& projectileManager, SoundManager& soundManager)
{
	m_PtrLevel = &level;
	m_PtrPlayer = &player;
	m_PtrEnemyManager = &enemyManager;
	m_PtrProjectileManager = &projectileManager;
	m_PtrSoundManager = &soundManager;
}