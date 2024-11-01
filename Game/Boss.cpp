#include <iostream>
#include "base.h"
#include "Boss.h"
#include "utils.h"
#include "Plasma.h"
#include "ProjectileManager.h"
#include "Avatar.h"
#include "LaserBolt.h"


Boss::Boss() :
	m_State{ State::sleeping },
	m_Hitbox{4090.0f, 0.0f, 63.0f, 336.0f },
	m_Detectionbox{ 3852.0f, 112.0f, 300.0f, 224.0f },
	m_MaxHealth{ 200 },
	m_Health{ m_MaxHealth },
	m_ProcentageWhenDamaged{ 40 },
	m_IsDamaged{ false },
	m_CannonIsAtTop{ false },
	m_ClothVelocity{ 40.0f, 0.0f },
	m_ClothPosition{ 245.0f, 62.0f },
	m_MainTexture{ "Images/Boss/Main Texture.png" },
	m_SpokesTexture{ "Images/Boss/Spokes Texture.png" },
	m_PilotCabinetTexture{ "Images/Boss/Pilot Cabinet Texture.png" },
	m_PilotTexture{ "Images/Boss/Pilot Sprite.png" },
	m_MovingCannonTexture{ "Images/Boss/Moving Cannon Sprite.png" },
	m_AttackFiringHighTexture{ "Images/Boss/Attack Firing High Sprite.png" },
	m_AttackFiringLowTexture{ "Images/Boss/Attack Firing Low Sprite.png" },
	m_AttackLaserLowTexture{ "Images/Boss/Attack Laser Low Sprite.png" },
	m_BreakdownTexture{ "Images/Boss/Breakdown Sprite.png" },
	m_ChargeFiringHighTexture{ "Images/Boss/Charge Firing High Sprite.png" },
	m_ChargeFiringLowTexture{ "Images/Boss/Charge Firing Low Sprite.png" },
	m_ChargeLaserLowTexture{ "Images/Boss/Charge Laser Low Sprite.png" },
	m_ClothTexture{ "Images/Boss/Cloth Sprite.png" },
	m_DamagedPilotCabinetTexture{ "Images/Boss/Damaged Pilot Cabinet Texture.png" },
	m_DamagedSideTexture{ "Images/Boss/Damaged Side Texture.png" },
	m_DamagedSpokesTexture{ "Images/Boss/Damaged Spokes Texture.png" },
	m_DamagedCannonTexture{ "Images/Boss/Destroyed Cannon Texture.png" },
	m_PilotSprite{ &m_PilotTexture, 7, 2, 4, 1.5f / 7.0f },
	m_MovingCannonSprite{ &m_MovingCannonTexture, 19, 4, 5, 2.0f / 19.0f },
	m_AttackFiringHighSprite{ &m_AttackFiringHighTexture, 8, 2, 4, 1.0f / 8.0f },
	m_AttackFiringLowSprite{ &m_AttackFiringLowTexture, 8, 2, 4, 1.0f / 8.0f },
	m_AttackLaserLowSprite{ &m_AttackLaserLowTexture, 10, 2, 5, 1.0f / 10.0f },
	m_BreakdownSprite{ &m_BreakdownTexture, 5, 2, 3, 1.0f / 5.0f },
	m_ChargeFiringHighSprite{ &m_ChargeFiringHighTexture, 9, 3, 3, 1.0f / 9.0f },
	m_ChargeFiringLowSprite{ &m_ChargeFiringLowTexture, 9, 3, 3, 1.0f / 9.0f },
	m_ChargeLaserLowSprite{ &m_ChargeLaserLowTexture, 2, 1, 2, 0.125f },
	m_ClothSprite{ &m_ClothTexture, 16, 4, 4, 2.0f / 16.0f },
	m_MaxFiringAttacks{ 3 },
	m_AmountOfFiringAttacks{ 0 },
	m_ChanceLaserAttack{ 50 },
	m_LaserAttackActive{ false }
{
	m_ClothSprite.SetMaxNumberOfCycles(1);
	m_MovingCannonSprite.SetMaxNumberOfCycles(1);
	m_ChargeFiringHighSprite.SetMaxNumberOfCycles(1);
	m_ChargeFiringLowSprite.SetMaxNumberOfCycles(1);
	m_AttackFiringHighSprite.SetMaxNumberOfCycles(1);
	m_AttackFiringLowSprite.SetMaxNumberOfCycles(1);
	m_ChargeLaserLowSprite.SetMaxNumberOfCycles(5);
	m_AttackLaserLowSprite.SetMaxNumberOfCycles(1);
	m_BreakdownSprite.SetMaxNumberOfCycles(1);
}

void Boss::Update(float elapsedSeconds)
{
	UpdateDefault(elapsedSeconds);

	switch (m_State)
	{
		case State::sleeping:
			UpdateSleeping(elapsedSeconds);
			break;
		case State::starting:
			UpdateStarting(elapsedSeconds);
			break;
		case State::moving:
			UpdateMoving(elapsedSeconds);
			break;
		case State::charging:
			UpdateCharging(elapsedSeconds);
			break;
		case State::shooting:
			UpdateShooting(elapsedSeconds);
			break;
		case State::restoring:
			UpdateRestoring(elapsedSeconds);
			break;
		case State::dying:
			UpdateDying(elapsedSeconds);
			break;
		case State::dead:
			UpdateDead(elapsedSeconds);
			break;
	}
}

void Boss::Draw() const
{
	glPushMatrix();
		glTranslatef(3768.0f, 80.0f, 0.0f);
		DrawDefault();
		switch (m_State)
		{
			case State::sleeping:
				DrawSleeping();
				break;
			case State::starting:
				DrawStarting();
				break;
			case State::moving:
				DrawMoving();
				break;
			case State::charging:
				DrawCharging();
				break;
			case State::shooting:
				DrawShooting();
				break;
			case State::restoring:
				DrawRestoring();
				break;
			case State::dying:
				DrawDying();
				break;
			case State::dead:
				DrawDead();
				break;
		}
	glPopMatrix();
}

void Boss::DrawDebug() const
{
	utils::FillRect(m_Hitbox);
}

Rectf Boss::GetHitbox() const
{
	return m_Hitbox;
}

void Boss::Hit(int damage)
{
	if (m_State != State::sleeping && m_State != State::starting && m_State != State::dying && m_State != State::dead)	// is in a sate where it can get shot
	{
		m_Health -= damage;

		
		if (!m_IsDamaged)
		{
			int procentage{ int(floor(float(m_Health) / float(m_MaxHealth) * 100)) };
			m_IsDamaged = procentage <= m_ProcentageWhenDamaged;
		}

		if (m_Health <= 0)
		{
			m_State = State::dying;
		}
	}
}

void Boss::Shoot() const
{
	m_PtrSoundManager->PlasmaShot();
	const Rectf playerHitbox{ m_PtrPlayer->GetHitbox() };
	Point2f start{ 3768.0f, 80.0f };

	if (m_CannonIsAtTop)
	{
		start.x += 270.0f;
		start.y += 161.0f;
	}
	else
	{
		start.x += 270.0f;
		start.y += 123.0f;
	}

	const Point2f target{ playerHitbox.left + (playerHitbox.width / 2.0f), playerHitbox.bottom + (playerHitbox.height / 2.0f) };
	const float height{ 30.0f };																										// max height of the projectile trajectory
	Vector2f velocity{ GetPlasmaVelocity(start, target, height, velocity) };

	m_PtrProjectileManager->Pushback(new Plasma{ start, velocity });
}

void Boss::ShootLaserBolt() const
{
	m_PtrSoundManager->PlasmaBeam();
	Point2f start{ 3768.0f, 80.0f };
	start.x += 176.0f;
	start.y += 80.0f;

	m_PtrProjectileManager->Pushback(new LaserBolt{ start });
}

Vector2f Boss::GetPlasmaVelocity(const Point2f& A, const Point2f& B, float maxH, Vector2f& velocity) const
{
	// setting the calculating the distance from A to maxH
	const float h{ (A.y > B.y) ? maxH : B.y - A.y + maxH };

	// Calculating initial velocity in y direction
	const float dy{ B.y - A.y };
	const float ay{ -98.1f };
	float s1{ +sqrtf(-2 * ay * h) };
	float s2{ -sqrtf(-2 * ay * h) };
	const float vy{ (s1 > s2) ? s1 : s2 };

	// Calculating the time it takes to reach the y coord of the targt with the initial y velocity
	const float d{ powf(vy, 2) - 2 * ay * (-dy) };
	float t{};
	if (d >= 0.0f)
	{
		s1 = (-vy + sqrtf(d)) / ay;
		s2 = (-vy - sqrtf(d)) / ay;
		t = (s1 > s2) ? s1 : s2;
	}

	// Calculating the initial velocity in x direction
	const float dx{ B.x - A.x };
	const float vx{ dx / t };

	// Returning the initial velocity
	return Vector2f{ vx, vy };
}

void Boss::UpdateDefault(float elapsedSeconds)
{
	m_PilotSprite.Update(elapsedSeconds);
}

void Boss::DrawDefault() const
{
	if (m_State != State::dying && m_State != State::dead)
	{
		m_MainTexture.Draw();
		m_PilotSprite.Draw(Point2f{ 343.0f, 143.0f });
		m_PilotCabinetTexture.Draw(Point2f{ 328.0f, 104.0f });
		

		if (m_IsDamaged)
		{
			m_DamagedSpokesTexture.Draw(Point2f{ 225.0f, 221.0f });
			m_DamagedSpokesTexture.Draw(Point2f{ 57.0f, 221.0f });
			m_DamagedPilotCabinetTexture.Draw(Point2f{ 320.0f, 96.0f });
			m_DamagedSideTexture.Draw(Point2f{ 288.0f, 128.0f });
		}
		else
		{
			m_SpokesTexture.Draw(Point2f{ 60.0f, 216.0f });
			m_SpokesTexture.Draw(Point2f{ 228.0f, 216.0f });
		}
	}

}

void Boss::UpdateSleeping(float elapsedSeconds)
{
	if (utils::IsOverlapping(m_Detectionbox, m_PtrPlayer->GetHitbox()))
	{
		m_State = State::starting;
		m_PtrSoundManager->SetBossMusic();
	}
}

void Boss::UpdateStarting(float elapsedSeconds)
{
	m_ClothPosition.x += elapsedSeconds * m_ClothVelocity.x;
	m_ClothSprite.Update(elapsedSeconds);

	if (m_ClothPosition.x > 384.0f)
	{
		m_State = State::moving;
	}
}

void Boss::UpdateMoving(float elapsedSeconds)
{
	m_MovingCannonSprite.Update(elapsedSeconds);

	if (m_MovingCannonSprite.Finished())
	{
		if (!m_MovingCannonSprite.IsInverted()) // was going up
		{
			m_MovingCannonSprite.Reset();
			m_MovingCannonSprite.Invert();
			m_MovingCannonSprite.SetCurrentFrame(m_MovingCannonSprite.GetTotalFrames() - 1);
		}
		else // was going down
		{
			m_MovingCannonSprite.Reset();
		}

		m_State = State::charging;
		m_CannonIsAtTop = !m_CannonIsAtTop;

		if (!m_CannonIsAtTop)
		{
			m_LaserAttackActive = (rand() % 101) <= m_ChanceLaserAttack;
		}
	}
}

void Boss::UpdateCharging(float elapsedSeconds)
{
	if(!m_LaserAttackActive)
	{ 
		if (m_CannonIsAtTop)
		{
			m_ChargeFiringHighSprite.Update(elapsedSeconds);
			if (m_ChargeFiringHighSprite.Finished())
			{
				m_ChargeFiringHighSprite.Reset();
				m_State = State::shooting;
				++m_AmountOfFiringAttacks;
				Shoot();
			}
		}
		else
		{
			m_ChargeFiringLowSprite.Update(elapsedSeconds);
			if (m_ChargeFiringLowSprite.Finished())
			{
				m_ChargeFiringLowSprite.Reset();
				m_State = State::shooting;
				++m_AmountOfFiringAttacks;
				Shoot();
			}
		}
	}
	else
	{
		m_ChargeLaserLowSprite.Update(elapsedSeconds);
		if (m_ChargeLaserLowSprite.Finished())
		{
			m_ChargeLaserLowSprite.Reset();
			m_State = State::shooting;
			ShootLaserBolt();
		}
	}
}

void Boss::UpdateShooting(float elapsedSeconds)
{
	if(!m_LaserAttackActive)
	{
		if (m_CannonIsAtTop)
		{
			m_AttackFiringHighSprite.Update(elapsedSeconds);

			if (m_AttackFiringHighSprite.Finished())
			{
				++m_AmountOfFiringAttacks;
				m_AttackFiringHighSprite.Reset();

				if (m_AmountOfFiringAttacks <= m_MaxFiringAttacks)
				{
					Shoot();
				}
				else
				{
					m_State = State::restoring;
					m_ChargeFiringHighSprite.Invert();
					m_ChargeFiringHighSprite.SetCurrentFrame(m_ChargeFiringHighSprite.GetTotalFrames() - 1);
					m_AmountOfFiringAttacks = 0;
				}
			}
		}
		else
		{
			m_AttackFiringLowSprite.Update(elapsedSeconds);

			if (m_AttackFiringLowSprite.Finished())
			{
				++m_AmountOfFiringAttacks;
				m_AttackFiringLowSprite.Reset();

				if (m_AmountOfFiringAttacks <= m_MaxFiringAttacks)
				{
					Shoot();
				}
				else
				{
					m_State = State::restoring;
					m_ChargeFiringLowSprite.Invert();
					m_ChargeFiringLowSprite.SetCurrentFrame(m_ChargeFiringLowSprite.GetTotalFrames() - 1);
					m_AmountOfFiringAttacks = 0;
				}
			}
		}
	}
	else
	{
		m_AttackLaserLowSprite.Update(elapsedSeconds);

		if (m_AttackLaserLowSprite.Finished())
		{
			m_State = State::moving;
			m_AttackLaserLowSprite.Reset();
			m_LaserAttackActive = false;
		}
	}
}

void Boss::UpdateRestoring(float elapsedSeconds)
{
	if (m_CannonIsAtTop)
	{
		m_ChargeFiringHighSprite.Update(elapsedSeconds);

		if (m_ChargeFiringHighSprite.Finished())
		{
			m_ChargeFiringHighSprite.Reset();
			m_State = State::moving;
		}
	}
	else
	{
		m_ChargeFiringLowSprite.Update(elapsedSeconds);

		if (m_ChargeFiringLowSprite.Finished())
		{
			m_ChargeFiringLowSprite.Reset();
			m_State = State::moving;
		}
	}
}

void Boss::UpdateDying(float elapsedSeconds)
{
	m_BreakdownSprite.Update(elapsedSeconds);

	if (m_BreakdownSprite.Finished())
	{
		m_State = State::dead;
	}
}

void Boss::UpdateDead(float elapsedSeconds)
{

}

void Boss::DrawSleeping() const
{
	m_MovingCannonSprite.Draw(Point2f{ 256.0f, 83.0f });
}

void Boss::DrawStarting() const
{
	m_ClothSprite.Draw(m_ClothPosition);
	m_MovingCannonSprite.Draw(Point2f{ 256.0f, 83.0f });
}

void Boss::DrawMoving() const
{
	m_MovingCannonSprite.Draw(Point2f{ 256.0f, 83.0f });
}

void Boss::DrawCharging() const
{
	if (!m_LaserAttackActive)
	{
		if (m_CannonIsAtTop)
		{
			m_ChargeFiringHighSprite.Draw(Point2f{ 248.0f, 119.0f });
		}
		else
		{
			m_ChargeFiringLowSprite.Draw(Point2f{ 250.0f, 82.0f });
		}
	}
	else
	{
		m_ChargeLaserLowSprite.Draw(Point2f{ 224.0f, 81.0f });
	}
}

void Boss::DrawShooting() const
{
	if (!m_LaserAttackActive)
	{
		if (m_CannonIsAtTop)
		{
			m_AttackFiringHighSprite.Draw(Point2f{ 249.0f, 121.0f });
		}
		else
		{
			m_AttackFiringLowSprite.Draw(Point2f{ 250.0f, 82.0f });
		}
	}
	else
	{
		m_AttackLaserLowSprite.Draw(Point2f{ 238.0f, 83.0f });
	}
}

void Boss::DrawRestoring() const
{
	if (m_CannonIsAtTop)
	{
		m_ChargeFiringHighSprite.Draw(Point2f{ 248.0f, 119.0f });
	}
	else
	{
		m_ChargeFiringLowSprite.Draw(Point2f{ 250.0f, 82.0f });
	}
}

void Boss::DrawDying() const
{
	m_BreakdownSprite.Draw();
	m_DamagedCannonTexture.Draw(Point2f{ 266.0f, 96.0f });
	m_DamagedSpokesTexture.Draw(Point2f{ 225.0f, 221.0f });
}

void Boss::DrawDead() const
{
	m_BreakdownSprite.Draw();
	m_DamagedCannonTexture.Draw(Point2f{ 266.0f, 96.0f });
	m_DamagedSpokesTexture.Draw(Point2f{ 225.0f, 221.0f });
}

bool Boss::NeedsToBeDeleted() const
{
	return false;
}