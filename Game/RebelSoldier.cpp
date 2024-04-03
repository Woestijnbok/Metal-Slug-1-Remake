#include "pch.h"
#include "RebelSoldier.h"
#include "utils.h"
#include "Texture.h"
#include "Level.h"
#include "Avatar.h"
#include "EnemyManager.h"
#include "ProjectileManager.h"
#include "SoundManager.h"

int RebelSoldier::m_InstanceCounter{ 0 };
const Texture* RebelSoldier::m_PtrIdleSpriteSheet{ nullptr };
const Texture* RebelSoldier::m_PtrWalkingSpriteSheet{ nullptr };
const Texture* RebelSoldier::m_PtrJumpingSpriteSheet{ nullptr };
const Texture* RebelSoldier::m_PtrDyingSpriteSheet{ nullptr };
const Vector2f RebelSoldier::m_InitialVelocity{ 175.0f, 350.0f };
const Vector2f RebelSoldier::m_Acceleration{ 0.0f, -981.0f };
const float RebelSoldier::m_InputInterval{ 1.0f };
const int RebelSoldier::m_MaxHealth{ 40 };

RebelSoldier::RebelSoldier(const Point2f& position, const Rectf& boundary) :
	Enemy{},
	m_IdleSprite{ m_PtrIdleSpriteSheet, 4, 2, 2, 1.0f / 4.0f },
	m_WalkingSprite{ m_PtrWalkingSpriteSheet, 12, 3, 4, 1.0f / 12.0f },
	m_JumpingSprite{ m_PtrJumpingSpriteSheet, 7, 2, 4, 1.0f / 7.0f },
	m_DyingSprite{ m_PtrDyingSpriteSheet, 15, 3, 5, 1.0f / 15.0f },
	m_Velocity{ 0.0f, 0.0f },
	m_ActionState{ ActionState::moving },
	m_Input{ Input::nothing },
	m_Hitbox{ position.x, position.y, 0.0f, 0.0f },
	m_IsLookingRight{ true },
	m_CurrentInputInterval{ 0.0f },
	m_IsDying{ false },
	m_Health{ m_MaxHealth },
	m_Boundary{ boundary }
{
	if (m_InstanceCounter == 0)
	{
		m_PtrWalkingSpriteSheet = new Texture { "Images/Enemies/Rebel Soldier/Walking Sprite.png" };
		m_PtrIdleSpriteSheet = new Texture { "Images/Enemies/Rebel Soldier/Idle Sprite.png" };
		m_PtrJumpingSpriteSheet = new Texture { "Images/Enemies/Rebel Soldier/Jumping Sprite.png" };
		m_PtrDyingSpriteSheet = new Texture { "Images/Enemies/Rebel Soldier/Dying Sprite.png" };

		m_IdleSprite.SetTexture(m_PtrIdleSpriteSheet);
		m_WalkingSprite.SetTexture(m_PtrWalkingSpriteSheet);
		m_JumpingSprite.SetTexture(m_PtrJumpingSpriteSheet);
		m_DyingSprite.SetTexture(m_PtrDyingSpriteSheet);
	}

	m_Hitbox.width = m_IdleSprite.GetWidthFrame();
	m_Hitbox.height = m_IdleSprite.GetHeightFrame();

	++m_InstanceCounter;
}

RebelSoldier::~RebelSoldier()
{
	if(m_InstanceCounter == 1)
	{ 
		delete m_PtrWalkingSpriteSheet;
		delete m_PtrIdleSpriteSheet;
		delete m_PtrJumpingSpriteSheet;
		delete m_PtrDyingSpriteSheet;
	}

	--m_InstanceCounter;
}

void RebelSoldier::Update(float elapsedSeconds)
{
	// The StateCheck functions return true if they switched the action state

	m_CurrentInputInterval += elapsedSeconds;
	if (m_CurrentInputInterval > m_InputInterval)
	{
		UpdateInput();
		m_CurrentInputInterval = 0.0f;
	}

	switch (m_ActionState)
	{
		case ActionState::idle:
			if (StateCheckIdle()) // switched action state
			{
				m_IdleSprite.Reset();
			}
			break;
		case ActionState::moving:
			if (!StateCheckMoving()) // didnt switch actions state
			{
				if (!m_IsDying)
				{
					InputHandeling();
				}

				UpdatePhysics(elapsedSeconds);
				m_PtrLevel->HandleCollision(m_Hitbox, m_Velocity);
			}
			else
			{
				m_JumpingSprite.Reset();
				m_WalkingSprite.Reset();
			}
			break;
	}

	UpdateSprites(elapsedSeconds);
}

void RebelSoldier::Draw() const
{
	glPushMatrix();
		glTranslatef(m_Hitbox.left, m_Hitbox.bottom, 0.0f);
		if (!m_IsLookingRight)
		{
			glScalef(-1.0f, 1.0f, 1.0f);
			glTranslatef(-m_Hitbox.width, 0.0f, 0.0f); // to fix it from jumping to the left
		}
		DrawSprite();
	glPopMatrix();
}

void RebelSoldier::DrawDebug() const
{
	utils::FillRect(m_Hitbox);
}

Rectf RebelSoldier::GetHitbox() const
{
	return m_Hitbox;
}

bool RebelSoldier::StateCheckIdle()
{
	if (m_PtrLevel->IsOnGround(m_Hitbox, m_Velocity))
	{
		if (m_Input != Input::nothing)
		{
			m_ActionState = ActionState::moving;

			return true;
		}
	}

	return false;
}

bool RebelSoldier::StateCheckMoving()
{
	if (m_Input == Input::nothing)
	{
		if (m_PtrLevel->IsOnGround(m_Hitbox, m_Velocity))
		{
			m_ActionState = ActionState::idle;
			m_Velocity = Vector2f{ 0.0f, 0.0f };
			return true;
		}
	}

	return false;
}

void RebelSoldier::UpdatePhysics(float elapsedSeconds)
{
	m_Velocity += (elapsedSeconds * m_Acceleration);
	m_Hitbox.left += (m_Velocity.x * elapsedSeconds);
	m_Hitbox.bottom += (m_Velocity.y * elapsedSeconds);

	if (m_Hitbox.left < m_Boundary.left)
	{
		m_Hitbox.left = m_Boundary.left;
	}
	else if ((m_Hitbox.left + m_Hitbox.width) > (m_Boundary.left + m_Boundary.width))
	{
		m_Hitbox.left = (m_Boundary.left + m_Boundary.width) - m_Hitbox.width;
	}
}

void RebelSoldier::DrawSprite() const
{
	if (!m_IsDying)
	{
		switch (m_ActionState)
		{
			case ActionState::idle:
				m_IdleSprite.Draw();
				break;
			case ActionState::moving:
				if (m_Velocity.y != 0.0f)
				{
					m_JumpingSprite.Draw();
				}
				else
				{
					m_WalkingSprite.Draw();
				}
				break;
			}
	}
	else
	{
		m_DyingSprite.Draw();
	}
}

void RebelSoldier::UpdateSprites(float elapsedSeconds)
{
	if (!m_IsDying)
	{
		switch (m_ActionState)
		{
			case ActionState::idle:
				m_IdleSprite.Update(elapsedSeconds);
				break;
			case ActionState::moving:
				if (m_Velocity.y != 0.0f && !m_JumpingSprite.IsAtLastFrame())
				{
					m_JumpingSprite.Update(elapsedSeconds);
				}
				else
				{
					m_WalkingSprite.Update(elapsedSeconds);
				}
				break;
		}
	}
	else
	{
		m_DyingSprite.Update(elapsedSeconds);
	}
}

void RebelSoldier::InputHandeling()
{
	const bool isOnGround{ m_PtrLevel->IsOnGround(m_Hitbox, m_Velocity) };

	switch (m_Input)
	{
		case Input::left:
			m_IsLookingRight = false;
			m_Velocity.x = -m_InitialVelocity.x;
			break;
		case Input::right:
			m_IsLookingRight = true;
			m_Velocity.x = m_InitialVelocity.x;
			break;
		case Input::up:
			if(isOnGround)
			{ 
				m_Velocity.y = m_InitialVelocity.y;
				m_WalkingSprite.Reset();
				m_JumpingSprite.Reset();
				m_Input = Input::nothing;
				m_CurrentInputInterval = 0.0f;
			}
			break;
	}
}

void RebelSoldier::UpdateInput()
{
	const int randomNumber{ rand() % 4 };

	switch(randomNumber)
	{
		case 0:
			m_Input = Input::nothing;
			break;
		case 1:
			m_Input = Input::left;
			break;
		case 2:
			m_Input = Input::right;
			break;
		case 3:
			m_Input = Input::up;
			break;
	}
}

void RebelSoldier::Hit(int damage)
{
	if(m_Health > 0)
	{
		m_Health -= damage;

		if (m_Health <= 0)
		{
			m_PtrSoundManager->EnemeyDeath();
			m_IsDying = true;
			m_IdleSprite.Reset();
			m_JumpingSprite.Reset();
			m_JumpingSprite.Reset();
		}
	}
}

bool RebelSoldier::NeedsToBeDeleted() const
{
	return m_IsDying && m_DyingSprite.IsAtLastFrame();
}