#include "pch.h"
#include "Plasma.h"
#include "utils.h"

int Plasma::m_InstanceCounter{ 0 };
const Texture* Plasma::m_PtrTexture{ nullptr };
const Vector2f Plasma::m_Acceleration{ 0.0f, -98.1f };
const int Plasma::m_Damage{ 20 };

Plasma::Plasma(const Point2f& position, const Vector2f& velocity) :
	m_Hitbox{ position.x, position.y , 0.0f, 0.0f },
	m_Velocity{ velocity },
	m_Sprite{ m_PtrTexture, 3, 1, 3, 0.25f }
{
	if (m_InstanceCounter == 0)
	{
		m_PtrTexture = new Texture{ "Images/Boss/Firing Bullet Sprite.png" };
		m_Sprite.SetTexture(m_PtrTexture);
	}

	m_Hitbox.width = m_Sprite.GetWidthFrame();
	m_Hitbox.height = m_Sprite.GetHeightFrame();

	++m_InstanceCounter;
}

Plasma::~Plasma()
{
	if (m_InstanceCounter == 1)
	{
		delete m_PtrTexture;
	}

	--m_InstanceCounter;
}

void Plasma::Draw() const
{
	m_Sprite.Draw(Point2f{ m_Hitbox.left, m_Hitbox.bottom });
}

void Plasma::DrawDebug() const
{
	utils::FillRect(m_Hitbox);
}

void Plasma::Update(float elapsedSeconds)
{
	m_Sprite.Update(elapsedSeconds);

	m_Velocity += elapsedSeconds * m_Acceleration;
	m_Hitbox.left += elapsedSeconds * m_Velocity.x;
	m_Hitbox.bottom += elapsedSeconds * m_Velocity.y;
}

const Rectf& Plasma::GetHitbox() const
{
	return m_Hitbox;
}

int Plasma::GetDamage() const
{
	return m_Damage;
}