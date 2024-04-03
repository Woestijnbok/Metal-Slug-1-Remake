#pragma once
#include <vector>

class Projectile;
class Avatar;
class EnemyManager;
class Level;

class ProjectileManager final
{
public:
	explicit ProjectileManager() = default;
	~ProjectileManager();

	ProjectileManager(const ProjectileManager& other) = delete;
	ProjectileManager& operator=(const ProjectileManager& other) = delete;
	ProjectileManager(ProjectileManager&& other) = delete;
	ProjectileManager& operator=(ProjectileManager&& other) = delete;

	void Update(float elapsedSeconds);
	void Draw() const;
	void DrawDebug() const;
	void Pushback(Projectile* const ptrProjectile);
	void SetGameInformation(const Level& level, Avatar& player, EnemyManager& enemyManager);
	void Reset();

private:
	std::vector<Projectile*> m_Projectiles;
	const Level* m_PtrLevel;
	Avatar* m_PtrPlayer;
	EnemyManager* m_PtrEnemyManager;

	void Pop(Projectile* ptrProjectile);
};

