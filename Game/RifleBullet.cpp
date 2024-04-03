#include "pch.h"
#include "RifleBullet.h"
#include "utils.h"

int RifleBullet::m_InstanceCounter{ 0 };
const Texture* RifleBullet::m_PtrTexture{ nullptr };
const Vector2f RifleBullet::m_Velocity{ 300.0f, 0.0f };
const int RifleBullet::m_Damage{ 20 };

RifleBullet::RifleBullet(const Direction direction, const Point2f& position) :
	m_Hitbox{ position.x, position.y, 0.0f, 0.0f },
	m_Direction{ direction }
{
	if (m_InstanceCounter == 0)
	{
		m_PtrTexture = new Texture{ "Images/Enemies/Rebel Soldier Rifle/Bullet.png" };
	}

	m_Hitbox.width = m_PtrTexture->GetWidth();
	m_Hitbox.height = m_PtrTexture->GetHeight();

	++m_InstanceCounter;
}

RifleBullet::~RifleBullet()
{
	if (m_InstanceCounter == 1)
	{
		delete m_PtrTexture;
	}

	--m_InstanceCounter;
}

void RifleBullet::Draw() const
{
	m_PtrTexture->Draw(m_Hitbox);
}

void RifleBullet::DrawDebug() const
{
	utils::FillRect(m_Hitbox);
}

void RifleBullet::Update(float elapsedSeconds)
{
	switch (m_Direction)
	{
	case Direction::right:
		m_Hitbox.left += elapsedSeconds * m_Velocity.x;
		break;
	case Direction::left:
		m_Hitbox.left -= elapsedSeconds * m_Velocity.x;
		break;
	}
}

const Rectf& RifleBullet::GetHitbox() const
{
	return m_Hitbox;
}

int RifleBullet::GetDamage() const
{
	return m_Damage;
}