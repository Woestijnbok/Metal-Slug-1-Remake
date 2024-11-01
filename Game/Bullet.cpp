#include "base.h"
#include "Bullet.h"
#include "utils.h"

int Bullet::m_InstanceCounter{ 0 };
const Texture* Bullet::m_PtrTexture{ nullptr };
const Vector2f Bullet::m_Velocity{ 500.0f, 0.0f };
const int Bullet::m_Damage{ 20 };

Bullet::Bullet(const Direction direction, const Point2f& position) :
	m_Hitbox{ position.x, position.y, 0.0f, 0.0f },
	m_Direction{ direction }
{
	if (m_InstanceCounter == 0)
	{
		m_PtrTexture = new Texture{ "Images/Character/Bullet Texture.png" };
	}

	m_Hitbox.width = m_PtrTexture->GetWidth();
	m_Hitbox.height = m_PtrTexture->GetHeight();

	++m_InstanceCounter;
}

Bullet::~Bullet()
{
	if (m_InstanceCounter == 1)
	{
		delete m_PtrTexture;
	}

	--m_InstanceCounter;
}

void Bullet::Draw() const
{
	m_PtrTexture->Draw(m_Hitbox);
}

void Bullet::DrawDebug() const
{
	utils::FillRect(m_Hitbox);
}

void Bullet::Update(float elapsedSeconds)
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

const Rectf& Bullet::GetHitbox() const
{
	return m_Hitbox;
}

int Bullet::GetDamage() const
{
	return m_Damage;
}