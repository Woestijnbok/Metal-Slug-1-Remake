#pragma once
#include "Enemy.h"
#include "Sprite.h"
#include "Vector2f.h"
#include "structs.h"

class Texture;

class Boss final : public Enemy
{
public:
	explicit Boss();
	virtual ~Boss() = default;

	Boss(const Boss&) = delete;
	Boss& operator=(const Boss&) = delete;
	Boss(Boss&&) = delete;
	Boss& operator=(Boss&&) = delete;

	virtual void Update(float elapsedSeconds) override;
	virtual void Draw() const override;
	virtual void DrawDebug() const override;
	virtual Rectf GetHitbox() const override;
	virtual void Hit(int damage) override;
	virtual bool NeedsToBeDeleted() const override;

private:
	enum class State
	{
		sleeping,
		starting,
		moving,
		charging,
		shooting,
		restoring,
		dying,
		dead
	};

	State m_State;
	const Rectf m_Hitbox;
	const Rectf m_Detectionbox;
	const int m_MaxHealth;
	int m_Health;
	const int m_ProcentageWhenDamaged;
	bool m_IsDamaged;
	bool m_CannonIsAtTop;
	Point2f m_ClothPosition;
	const Vector2f m_ClothVelocity;
	const int m_MaxFiringAttacks;
	int m_AmountOfFiringAttacks;
	int m_ChanceLaserAttack;
	bool m_LaserAttackActive;
	#pragma region Textures
	const Texture m_MainTexture;
	const Texture m_SpokesTexture;
	const Texture m_PilotCabinetTexture;
	const Texture m_PilotTexture;
	const Texture m_MovingCannonTexture;
	const Texture m_AttackFiringHighTexture;
	const Texture m_AttackFiringLowTexture;
	const Texture m_AttackLaserLowTexture;
	const Texture m_BreakdownTexture;
	const Texture m_ChargeFiringHighTexture;
	const Texture m_ChargeFiringLowTexture;
	const Texture m_ChargeLaserLowTexture;
	const Texture m_ClothTexture;
	const Texture m_DamagedPilotCabinetTexture;
	const Texture m_DamagedSideTexture;
	const Texture m_DamagedSpokesTexture;
	const Texture m_DamagedCannonTexture;
	#pragma endregion
	#pragma region Sprites
	Sprite m_PilotSprite;
	Sprite m_MovingCannonSprite;
	Sprite m_AttackFiringHighSprite;
	Sprite m_AttackFiringLowSprite;
	Sprite m_AttackLaserLowSprite;
	Sprite m_BreakdownSprite;
	Sprite m_ChargeFiringHighSprite;
	Sprite m_ChargeFiringLowSprite;
	Sprite m_ChargeLaserLowSprite;
	Sprite m_ClothSprite;
	#pragma endregion

	void Shoot() const;
	void ShootLaserBolt() const;
	Vector2f GetPlasmaVelocity(const Point2f& A, const Point2f& B, float maxH, Vector2f& velocity) const;
	void UpdateDefault(float elapsedSeconds);
	void DrawDefault() const;
	void UpdateSleeping(float elapsedSeconds);
	void UpdateStarting(float elapsedSeconds);
	void UpdateMoving(float elapsedSeconds);
	void UpdateCharging(float elapsedSeconds);
	void UpdateShooting(float elapsedSeconds);
	void UpdateRestoring(float elapsedSeconds);
	void UpdateDying(float elapsedSeconds);
	void UpdateDead(float elapsedSeconds);
	void DrawSleeping() const;
	void DrawStarting() const;
	void DrawMoving() const;
	void DrawCharging() const;
	void DrawShooting() const;
	void DrawRestoring() const;
	void DrawDying() const;
	void DrawDead() const;
};