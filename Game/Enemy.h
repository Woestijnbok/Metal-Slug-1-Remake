#pragma once

class EnemyManager;
class ProjectileManager;
class Level;
class Avatar;
class SoundManager;

class Enemy
{
public:
	explicit Enemy() = default;
	virtual ~Enemy() = default;

	Enemy(const Enemy&) = delete;
	Enemy& operator=(const Enemy&) = delete;
	Enemy(Enemy&&) = delete;
	Enemy& operator=(Enemy&&) = delete;

	virtual void Update(float elapsedSeconds) = 0;
	virtual void Draw() const = 0;
	virtual void DrawDebug() const = 0;
	virtual Rectf GetHitbox() const = 0;
	virtual void Hit(int damage) = 0;
	virtual bool NeedsToBeDeleted() const = 0;

	static void SetGameInformation(const Level& level, const Avatar& player, const EnemyManager& enemyManager, ProjectileManager& projectileManager, SoundManager& soundManager);

protected:
	static const Level* m_PtrLevel;
	static const Avatar* m_PtrPlayer;
	static const EnemyManager* m_PtrEnemyManager;
	static ProjectileManager* m_PtrProjectileManager;
	static SoundManager* m_PtrSoundManager;

private:

};