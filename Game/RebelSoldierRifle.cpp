#include "pch.h"
#include "RebelSoldierRifle.h"
#include "utils.h"
#include "Level.h"
#include "Avatar.h"
#include "ProjectileManager.h"
#include "RifleBullet.h"
#include "Enumerations.h"

int RebelSoldierRifle::m_InstanceCounter{ 0 };
const Texture* RebelSoldierRifle::m_PtrIdleSpriteSheet{ nullptr };
const Texture* RebelSoldierRifle::m_PtrShootingSpriteSheet{ nullptr };
const Texture* RebelSoldierRifle::m_PtrReloadingSpriteSheet{ nullptr };
const float RebelSoldierRifle::m_ShootingInterval{ 0.0f };
const int RebelSoldierRifle::m_MaxHealth{ 40 };
const Vector2f RebelSoldierRifle::m_Acceleration{ 0.0f, -981.0f };

RebelSoldierRifle::RebelSoldierRifle(const Point2f& position) :
	m_IdleSprite{ m_PtrIdleSpriteSheet, 4, 2, 2, 0.225f },
	m_ShootingSprite{ m_PtrShootingSpriteSheet, 20, 4, 5, 0.125f },
	m_ReloadingSprite{ m_PtrReloadingSpriteSheet, 12, 3, 4, 0.225f },
	m_ActionState{ ActionState::spawning },
	m_Hitbox{ position.x, position.y, 0.0f, 0.0f },
	m_IsLookingRight{ false },
	m_FlickerTime{ 0.0f },
	m_MaxFlickerTime{ 0.1f },
	m_DyingTime{ 0.0f },
	m_MaxDyingTime{ 0.7f },
	m_CanDraw{ true },
	m_Health{ m_MaxHealth },
	m_Velocity{ 0.0f, 0.0f },
	m_DetectionRect{ position.x, position.x, 100.0f, 100.0f },
	m_ClipSize{ 2 },
	m_CurrentClip{ m_ClipSize }
{
	if (m_InstanceCounter == 0)
	{
		m_PtrIdleSpriteSheet = new Texture{ "Images/Enemies/Rebel Soldier Rifle/Idle.png" };
		m_PtrShootingSpriteSheet = new Texture{ "Images/Enemies/Rebel Soldier Rifle/Shooting.png" };
		m_PtrReloadingSpriteSheet = new Texture{ "Images/Enemies/Rebel Soldier Rifle/Reloading.png" };

		m_IdleSprite.SetTexture(m_PtrIdleSpriteSheet);
		m_ShootingSprite.SetTexture(m_PtrShootingSpriteSheet);
		m_ReloadingSprite.SetTexture(m_PtrReloadingSpriteSheet);
	}

	m_Hitbox.width = m_IdleSprite.GetWidthFrame();
	m_Hitbox.height = m_IdleSprite.GetHeightFrame();

	m_ShootingSprite.SetMaxNumberOfCycles(1);
	m_ReloadingSprite.SetMaxNumberOfCycles(1);

	++m_InstanceCounter;
}

RebelSoldierRifle::~RebelSoldierRifle()
{
	if (m_InstanceCounter == 1)
	{
		delete m_PtrIdleSpriteSheet;
		delete m_PtrShootingSpriteSheet;
		delete m_PtrReloadingSpriteSheet;

		m_PtrIdleSpriteSheet = nullptr;
		m_PtrShootingSpriteSheet = nullptr;
		m_PtrReloadingSpriteSheet = nullptr;
	}

	--m_InstanceCounter;
}

void RebelSoldierRifle::Update(float elapsedSeconds)
{
	switch (m_ActionState)
	{
		case ActionState::spawning:
			UpdateSpawning(elapsedSeconds);
			break;
		case ActionState::idle:
			UpdateIdle(elapsedSeconds);
			break;
		case ActionState::shooting:
			UpdateShooting(elapsedSeconds);
			break;
		case ActionState::reloading:
			UpdateReloading(elapsedSeconds);
			break;
		case ActionState::dying:
			UpdateDying(elapsedSeconds);
			break;
		case ActionState::dead:
			break;
	}

	UpdateSprites(elapsedSeconds);
	LookAtPlayer();
}

void RebelSoldierRifle::Draw() const
{
	glPushMatrix();
		glTranslatef(m_Hitbox.left, m_Hitbox.bottom, 0.0f);
		if (m_IsLookingRight)
		{
			glScalef(-1.0f, 1.0f, 1.0f);
			glTranslatef(-m_Hitbox.width, 0.0f, 0.0f); // to fix it from jumping to the left
		}
		DrawSprite();
	glPopMatrix();
}

void RebelSoldierRifle::DrawDebug() const
{
	utils::FillRect(m_Hitbox);
	utils::FillRect(m_DetectionRect);
}

Rectf RebelSoldierRifle::GetHitbox() const
{
	return m_Hitbox;
}

void RebelSoldierRifle::Hit(int damage)
{
	if (int(m_ActionState) < int(ActionState::dying))	// is not dying or dead
	{
		m_Health -= damage;

		if (m_Health <= 0)
		{
			m_PtrSoundManager->EnemeyDeath();
			m_ActionState = ActionState::dying;
		}
	}
}

bool RebelSoldierRifle::NeedsToBeDeleted() const
{
	return m_ActionState == ActionState::dead;
}

void RebelSoldierRifle::DrawSprite() const
{
	switch (m_ActionState)
	{
		case ActionState::spawning:
			m_IdleSprite.Draw();
			break;
		case ActionState::idle:
			m_IdleSprite.Draw();
			break;
		case ActionState::shooting:
			m_ShootingSprite.Draw();
			break;
		case ActionState::reloading:
			m_ReloadingSprite.Draw();
			break;
		case ActionState::dying:
			if (m_CanDraw) m_IdleSprite.Draw();
			break;
		case ActionState::dead:
			break;
	}
}

void RebelSoldierRifle::UpdateSprites(float elapsedSeconds)
{
	switch (m_ActionState)
	{
		case ActionState::spawning:
			m_IdleSprite.Update(elapsedSeconds);
			break;
		case ActionState::idle:
			m_IdleSprite.Update(elapsedSeconds);
			break;
		case ActionState::shooting:
			m_ShootingSprite.Update(elapsedSeconds);
			break;
		case ActionState::reloading:
			m_ReloadingSprite.Update(elapsedSeconds);
			break;
		case ActionState::dying:
			m_IdleSprite.Update(elapsedSeconds);
			break;
		case ActionState::dead:
			break;
	}
}

void RebelSoldierRifle::UpdateSpawning(float elapsedSeconds)
{
	m_Velocity += elapsedSeconds * m_Acceleration;
	m_Hitbox.bottom += elapsedSeconds * m_Velocity.y;
	m_PtrLevel->HandleCollision(m_Hitbox, m_Velocity);
	if (m_PtrLevel->IsOnGround(m_Hitbox, m_Velocity)) m_ActionState = ActionState::idle;
}

void RebelSoldierRifle::UpdateIdle(float elapsedSeconds)
{
	if (utils::IsOverlapping(m_DetectionRect, m_PtrPlayer->GetHitbox()))
	{
		m_ActionState = ActionState::shooting;
		Shoot();
	}
}

void RebelSoldierRifle::UpdateShooting(float elapsedSeconds)
{
	if (m_ShootingSprite.Finished())
	{
		m_ShootingSprite.Reset();
		if (m_CurrentClip == 0)
		{
			m_ActionState = ActionState::reloading;
		}
		else
		{
			m_ActionState = ActionState::idle;
		}
	}
}

void RebelSoldierRifle::UpdateReloading(float elapsedSeconds)
{
	if (m_ReloadingSprite.Finished())
	{
		m_ActionState = ActionState::idle;
		m_ReloadingSprite.Reset();
		m_CurrentClip = m_ClipSize;
	}
}

void RebelSoldierRifle::UpdateDying(float elapsedSeconds)
{
	m_FlickerTime += elapsedSeconds;
	m_DyingTime += elapsedSeconds;
	if (m_FlickerTime >= m_MaxFlickerTime)
	{
		m_CanDraw = !m_CanDraw;
		m_FlickerTime = 0.0f;
	}

	if (m_DyingTime >= m_MaxDyingTime) m_ActionState = ActionState::dead;
}

void RebelSoldierRifle::LookAtPlayer()
{
	m_DetectionRect.bottom = m_Hitbox.bottom;

	if (m_Hitbox.left > m_PtrPlayer->GetHitbox().left) // soldier to the right of player
	{
		m_IsLookingRight = false;
		m_DetectionRect.left = m_Hitbox.left - m_DetectionRect.width + m_Hitbox.width;
	}
	else
	{
		m_IsLookingRight = true;
		m_DetectionRect.left = m_Hitbox.left;
	}
}

void RebelSoldierRifle::Shoot()
{
	m_PtrSoundManager->RifleShot();
	Direction direction{ (m_IsLookingRight) ? Direction::right : Direction::left };

	m_PtrProjectileManager->Pushback(new RifleBullet{ direction, Point2f{ m_Hitbox.left, m_Hitbox.bottom + 32.0f } });
	--m_CurrentClip;
}