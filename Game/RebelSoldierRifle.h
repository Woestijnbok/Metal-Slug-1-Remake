#pragma once
#include "Enemy.h"
#include "Texture.h"
#include "Sprite.h"
#include "Vector2f.h"

class RebelSoldierRifle final : public Enemy
{
public:
	explicit RebelSoldierRifle(const Point2f& position);
	~RebelSoldierRifle();

	RebelSoldierRifle(const RebelSoldierRifle&) = delete;
	RebelSoldierRifle& operator=(const RebelSoldierRifle&) = delete;
	RebelSoldierRifle(RebelSoldierRifle&&) = delete;
	RebelSoldierRifle& operator=(RebelSoldierRifle&&) = delete;

	virtual void Update(float elapsedSeconds) override;
	virtual void Draw() const override;
	virtual void DrawDebug() const override;
	virtual Rectf GetHitbox() const override;
	virtual void Hit(int damage) override;
	virtual bool NeedsToBeDeleted() const override;

private:
	enum class ActionState
	{
		spawning,
		idle,
		shooting,
		reloading,
		dying,
		dead
	};

	static int m_InstanceCounter;
	static const Texture* m_PtrIdleSpriteSheet;
	static const Texture* m_PtrShootingSpriteSheet;
	static const Texture* m_PtrReloadingSpriteSheet;
	static const float m_ShootingInterval;
	static const int m_MaxHealth;
	static const Vector2f m_Acceleration;

	Sprite m_IdleSprite;
	Sprite m_ShootingSprite;
	Sprite m_ReloadingSprite;
	ActionState m_ActionState;
	Rectf m_Hitbox;
	bool m_IsLookingRight;
	float m_FlickerTime;
	const float m_MaxFlickerTime;
	float m_DyingTime;
	const float m_MaxDyingTime;
	bool m_CanDraw;
	int m_Health;
	Vector2f m_Velocity;
	Rectf m_DetectionRect;
	const int m_ClipSize;
	int m_CurrentClip;

	void DrawSprite() const;
	void UpdateSprites(float elapsedSeconds);
	void UpdateSpawning(float elapsedSeconds);
	void UpdateIdle(float elapsedSeconds);
	void UpdateShooting(float elapsedSeconds);
	void UpdateReloading(float elapsedSeconds);
	void UpdateDying(float elapsedSeconds);
	void LookAtPlayer();
	void Shoot();
};