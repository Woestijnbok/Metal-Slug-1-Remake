#include <iostream>
#include "pch.h"
#include "Avatar.h"
#include "utils.h"
#include "Bullet.h"

Avatar::Avatar() :
	m_Leg{ Leg::State::jumping },
	m_Torso{ Torso::State::jumping },
	m_HorizontalVelocity{ 300.0f },
	m_VerticalVelocity{ 350.0f },
	m_CurrentVelocity{ 0.0f, 0.0f },
	m_Acceleration{ 0.0f, -981.0f },
	m_ActionState{ ActionState::moving },
	m_Hitbox{ 100.0f, 250.0f, 31.0f, 39.0f },
	m_Direction{ Direction::right },
	m_IsShooting{ false },
	m_MaxHealth{ 100 },
	m_Health{ m_MaxHealth },
	m_MaxLives{ 3 },
	m_Lives{ m_MaxLives },
	m_PtrLevel{ nullptr },
	m_PtrProjectileManager{ nullptr },
	m_PtrSoundManager{ nullptr },
	m_PtrHud{ nullptr },
	m_IsRespawning{ false },
	m_MaxRespawnTime{ 1.6f },
	m_RespawnTime{ 0.0f },
	m_FlickerTime{ 0.0f },
	m_CanDraw{ false }
{
	
}

void Avatar::SetGameInformation(const Level& level, ProjectileManager& projectileManager, SoundManager& soundManager, Hud& hud)
{
	m_PtrLevel = &level;
	m_PtrProjectileManager = &projectileManager;
	m_PtrSoundManager = &soundManager;
	m_PtrHud = &hud;
}

void Avatar::Update(float elapsedSeconds, const Uint8* const ptrKeyboardState)
{
	switch (m_ActionState)
	{
		case ActionState::idle:
			StateCheckIdle(ptrKeyboardState);
			break;
		case ActionState::moving:
			if (!StateCheckMoving(ptrKeyboardState)) // didn't switch actions state
			{
				InputHandeling(ptrKeyboardState);
				UpdatePhysics(elapsedSeconds);
				m_PtrLevel->HandleCollision(m_Hitbox, m_CurrentVelocity);
			}
			break;
	}

	UpdateLeg(elapsedSeconds);
	UpdateTorso(elapsedSeconds);
	UpdateRespawning(elapsedSeconds);
}

void Avatar::Draw() const
{
	if (!m_IsRespawning || m_CanDraw)
	{
		glPushMatrix();
			glTranslatef(m_Hitbox.left, m_Hitbox.bottom, 0.0f);
			if (m_Direction == Direction::left)
			{
				glScalef(-1.0f, 1.0f, 1.0f);
				glTranslatef(-m_Hitbox.width, 0.0f, 0.0f); // to fix it from jumping to the left
			}
			m_Leg.Draw();
			m_Torso.Draw();
		glPopMatrix();
	}
}

Rectf Avatar::GetHitbox() const
{
	return m_Hitbox;
}

bool Avatar::StateCheckIdle(const Uint8* const ptrKeyboardState)
{
	if (m_PtrLevel->IsOnGround(m_Hitbox, m_CurrentVelocity))
	{
		if (ptrKeyboardState[SDL_SCANCODE_D] || ptrKeyboardState[SDL_SCANCODE_A] || ptrKeyboardState[SDL_SCANCODE_W])
		{
				m_ActionState = ActionState::moving;

				return true;
		}
	}
	
	return false;
}

bool Avatar::StateCheckMoving(const Uint8* const ptrKeyboardState)
{
	if (!ptrKeyboardState[SDL_SCANCODE_D] && !ptrKeyboardState[SDL_SCANCODE_A] && !ptrKeyboardState[SDL_SCANCODE_W])
	{
		if (m_PtrLevel->IsOnGround(m_Hitbox, m_CurrentVelocity))
		{
			m_ActionState = ActionState::idle;
			m_CurrentVelocity = Vector2f{ 0.0f, 0.0f };
			return true;
		}
	}

	return false;
}

void Avatar::UpdatePhysics(float elapsedSeconds)
{
	m_CurrentVelocity.x += (elapsedSeconds * m_Acceleration.x);
	m_CurrentVelocity.y += (elapsedSeconds * m_Acceleration.y);

	m_Hitbox.left += (m_CurrentVelocity.x * elapsedSeconds);
	m_Hitbox.bottom += (m_CurrentVelocity.y * elapsedSeconds);

	const Rectf boundaries{ m_PtrLevel->GetBoundaries() };

	if (m_Hitbox.left < boundaries.left)
	{
		m_Hitbox.left = boundaries.left;
	}
	else if ((m_Hitbox.left + m_Hitbox.width) > (boundaries.left + boundaries.width))
	{
		m_Hitbox.left = (boundaries.left + boundaries.width) - m_Hitbox.width;
	}
}

void Avatar::InputHandeling(const Uint8* const ptrKeyboardState)
{
	const bool isOnGround{ m_PtrLevel->IsOnGround(m_Hitbox, m_CurrentVelocity) };

	if (ptrKeyboardState[SDL_SCANCODE_A])
	{
		m_Direction = Direction::left;
		m_CurrentVelocity.x = -m_HorizontalVelocity;
	}

	if (ptrKeyboardState[SDL_SCANCODE_D])
	{
		m_Direction = Direction::right;
		m_CurrentVelocity.x = m_HorizontalVelocity;
	}

	if (ptrKeyboardState[SDL_SCANCODE_W] && isOnGround)
	{
		m_CurrentVelocity.y = m_VerticalVelocity;
	}
}

void Avatar::DrawDebug() const
{
	const Color4f red{ 1.0f, 0.0f, 0.0f, 0.7f };
	utils::SetColor(red);
	utils::FillRect(m_Hitbox);
}

void Avatar::Shoot()
{
	if (!m_IsShooting && !m_IsRespawning)
	{
		switch (m_Direction)
		{
			case Direction::right:
				m_PtrProjectileManager->Pushback(new Bullet{ m_Direction, Point2f{m_Hitbox.left + m_Hitbox.width + 10.0f, m_Hitbox.bottom + (m_Hitbox.height * 2.0f / 3.0f)} });
				break;
			case Direction::left:
				m_PtrProjectileManager->Pushback(new Bullet{ m_Direction, Point2f{m_Hitbox.left - 10.0f, m_Hitbox.bottom + (m_Hitbox.height * 2.0f / 3.0f)} });
				break;
		}

		m_PtrSoundManager->PistolShot();
		m_IsShooting = true;
	}
}

void Avatar::UpdateLeg(const float elapsedSeconds)
{
	if (m_ActionState == ActionState::idle && m_Leg.GetState() != Leg::State::idle)
	{
		m_Leg.SetState(Leg::State::idle);
		m_Leg.Reset();
	}
	else if (m_ActionState == ActionState::moving && m_CurrentVelocity.y != 0.0f && m_Leg.GetState() != Leg::State::jumping)
	{
		m_Leg.SetState(Leg::State::jumping);
		m_Leg.Reset();
	}
	else if(m_ActionState == ActionState::moving && m_CurrentVelocity.y == 0.0f && m_Leg.GetState() != Leg::State::walking)
	{
		m_Leg.SetState(Leg::State::walking);
		m_Leg.Reset();
	}

	m_Leg.Update(elapsedSeconds);
}

void Avatar::UpdateTorso(const float elapsedSeconds)
{
	if (m_IsShooting)
	{
		if (m_Torso.GetState() != Torso::State::shooting)
		{
			m_Torso.SetState(Torso::State::shooting);
			m_Torso.Reset();
		}
		else if(m_Torso.FinishedShooting())
		{
			m_IsShooting = false;
		}
	}
	else if (m_ActionState == ActionState::idle && m_Torso.GetState() != Torso::State::idle)
	{
		m_Torso.SetState(Torso::State::idle);
		m_Torso.Reset();
	}
	else if (m_ActionState == ActionState::moving && m_CurrentVelocity.y != 0.0f && m_Torso.GetState() != Torso::State::jumping)
	{
		m_Torso.SetState(Torso::State::jumping);
		m_Torso.Reset();
	}
	else if(m_ActionState == ActionState::moving && m_CurrentVelocity.y == 0.0f && m_Torso.GetState() != Torso::State::walking)
	{
		m_Torso.SetState(Torso::State::walking);
		m_Torso.Reset();
	}

	m_Torso.Update(elapsedSeconds);
}

void Avatar::Hit(int damage)
{
	if (!m_IsRespawning)
	{
		m_Health -= damage;

		if (m_Health <= 0)
		{
			m_PtrSoundManager->PlayerDeath();
			m_PtrHud->Died();
			m_IsRespawning = true;
			--m_Lives;
		}
	}
}

void Avatar::UpdateRespawning(const float elapsedSeconds)
{
	if(m_IsRespawning)
	{
		m_RespawnTime += elapsedSeconds;
		m_FlickerTime += elapsedSeconds;

		if (m_FlickerTime > 0.1f)
		{
			m_CanDraw = !m_CanDraw;
			m_FlickerTime = 0.0f;
		}

		if (m_RespawnTime >= m_MaxRespawnTime)
		{
			m_IsRespawning = false;
			m_RespawnTime = 0.0f;
			m_CanDraw = false;
			m_Health = m_MaxHealth;
		}
	}
}

int Avatar::GetLives() const
{
	return m_Lives;
}

void Avatar::Reset()
{
	m_Leg.SetState(Leg::State::jumping);
	m_Torso.SetState(Torso::State::jumping);
	m_CurrentVelocity = Vector2f{ 0.0f, 0.0f };
	m_ActionState = ActionState::moving;
	m_Hitbox = Rectf{ 100.0f, 250.0f, 31.0f, 39.0f };
	m_Direction = Direction::right;
	m_IsShooting = false;
	m_Health = m_MaxHealth;
	m_Lives = m_MaxLives;
	m_IsRespawning = false;
	m_RespawnTime = 0.0f;
	m_FlickerTime = 0.0f;
	m_CanDraw = true;
}