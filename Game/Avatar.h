#pragma once
#include "structs.h"
#include "Enumerations.h"
#include "Vector2f.h"
#include "Leg.h"
#include "Torso.h"
#include "ProjectileManager.h"
#include "Level.h"
#include "SoundManager.h"
#include "Hud.h"

class Avatar final
{
public:
	explicit Avatar();
	~Avatar() = default;

	Avatar(const Avatar&) = delete;
	Avatar& operator=(const Avatar&) = delete;
	Avatar(Avatar&&) = delete;
	Avatar& operator=(Avatar&&) = delete;

	void Update(float elapsedSeconds, const Uint8* const ptrKeyboardState);
	void Draw() const;
	void DrawDebug() const;
	Rectf GetHitbox() const;
	void Shoot();
	void Hit(int damage);
	void SetGameInformation(const Level& level, ProjectileManager& projectileManager, SoundManager& soundManager, Hud& hud);
	int GetLives() const;
	void Reset();

private:
	enum class ActionState
	{
		idle,
		moving
	};

	Leg m_Leg;
	Torso m_Torso;
	const float m_HorizontalVelocity;
	const float m_VerticalVelocity;
	Vector2f m_CurrentVelocity;
	const Vector2f m_Acceleration;
	ActionState m_ActionState;
	Rectf m_Hitbox;
	Direction m_Direction;
	bool m_IsShooting;
	const int m_MaxHealth;
	int m_Health;
	int m_MaxLives;
	int m_Lives;
	const Level* m_PtrLevel;
	ProjectileManager* m_PtrProjectileManager;
	SoundManager* m_PtrSoundManager;
	Hud* m_PtrHud;
	bool m_IsRespawning;
	const float m_MaxRespawnTime;
	float m_RespawnTime;
	float m_FlickerTime;
	bool m_CanDraw;

	bool StateCheckIdle(const Uint8* const ptrKeyboardState);
	bool StateCheckMoving(const Uint8* const ptrKeyboardState);
	void UpdatePhysics(float elapsedSeconds);
	void InputHandeling(const Uint8* const ptrKeyboardState);
	void UpdateLeg(const float elapsedSeconds);
	void UpdateTorso(const float elapsedSeconds);
	void UpdateRespawning(const float elapsedSeconds);
};