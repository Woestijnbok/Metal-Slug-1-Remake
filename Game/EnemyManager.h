#pragma once
#include <vector>

class Enemy;
class Level;
class Avatar;
class ProjectileManager;
class Projectile;
class SoundManager;

class EnemyManager final
{
public:
	explicit EnemyManager() = default;
	~EnemyManager();

	EnemyManager(const EnemyManager&) = delete;
	EnemyManager& operator=(const EnemyManager&) = delete;
	EnemyManager(EnemyManager&&) = delete;
	EnemyManager& operator=(EnemyManager&&) = delete;

	void Update(float elapsedSeconds);
	void Draw() const;
	void DrawDebug() const;
	void Pushback(Enemy* const ptrEnemy);
	bool IsAnyEnemyHit(const Projectile* const ptrProjectile) const;
	void Reset();

private:
	std::vector<Enemy*> m_Enemies;

	void Pop(Enemy* ptrEnemy);
};