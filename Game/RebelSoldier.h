#pragma once
#include "Enemy.h"
#include "structs.h"
#include "Vector2f.h"
#include "Sprite.h"

class RebelSoldier : public Enemy
{
public:
	explicit RebelSoldier(const Point2f& position, const Rectf& boundary);
	virtual ~RebelSoldier();

	RebelSoldier(const RebelSoldier&) = delete;
	RebelSoldier& operator=(const RebelSoldier&) = delete;
	RebelSoldier(RebelSoldier&&) = delete;
	RebelSoldier& operator=(RebelSoldier&&) = delete;

	virtual void Update(float elapsedSeconds) override;
	virtual void Draw() const override;
	virtual void DrawDebug() const override;
	virtual Rectf GetHitbox() const override;
	virtual void Hit(int damage) override;
	virtual bool NeedsToBeDeleted() const override;

private:
	enum class ActionState
	{
		idle,
		moving
	};

	enum class Input
	{
		nothing,
		right,
		left,
		up
	};

	static int m_InstanceCounter;
	static const Texture* m_PtrIdleSpriteSheet;
	static const Texture* m_PtrWalkingSpriteSheet;
	static const Texture* m_PtrJumpingSpriteSheet;
	static const Texture* m_PtrDyingSpriteSheet;
	static const Vector2f m_InitialVelocity;
	static const Vector2f m_Acceleration;
	static const float m_InputInterval;
	static const int m_MaxHealth;

	Sprite m_IdleSprite;
	Sprite m_WalkingSprite;
	Sprite m_JumpingSprite;
	Sprite m_DyingSprite;
	Vector2f m_Velocity;
	ActionState m_ActionState;
	Input m_Input;
	Rectf m_Hitbox;
	bool m_IsLookingRight;
	float m_CurrentInputInterval;
	bool m_IsDying;
	int m_Health;
	const Rectf m_Boundary;

	bool StateCheckIdle();
	bool StateCheckMoving();
	void UpdatePhysics(float elapsedSeconds);
	void DrawSprite() const;
	void UpdateSprites(float elapsedSeconds);
	void InputHandeling();
	void UpdateInput();
};