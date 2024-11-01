#include "base.h"
#include "LaserBolt.h"
#include "utils.h"

int LaserBolt::m_InstanceCounter{ 0 };
const Texture* LaserBolt::m_PtrTexture{ nullptr };
const int LaserBolt::m_Damage{ 60 };
const Vector2f LaserBolt::m_Velocity{ 300.0f, 0.0f };

LaserBolt::LaserBolt(const Point2f& position) :
	m_Sprite{ m_PtrTexture, 4, 2, 2, 0.125f },
	m_Hitbox{ position.x, position.y, 0.0f, 0.0f }
{
	if (m_InstanceCounter == 0)
	{
		m_PtrTexture = new Texture{ "Images/Boss/Laser Bullet Sprite.png" };
		m_Sprite.SetTexture(m_PtrTexture);
	}
	
	m_Hitbox.width = m_Sprite.GetWidthFrame();
	m_Hitbox.height = m_Sprite.GetHeightFrame();
	++m_InstanceCounter;
}

LaserBolt::~LaserBolt()
{
	if (m_InstanceCounter == 1)
	{
		delete m_PtrTexture;
	}

	--m_InstanceCounter;
}

void LaserBolt::Draw() const
{
	m_Sprite.Draw(Point2f{ m_Hitbox.left, m_Hitbox.bottom });
}

void LaserBolt::DrawDebug() const
{
	utils::FillRect(m_Hitbox);
}

void LaserBolt::Update(float elapsedSeconds)
{
	m_Sprite.Update(elapsedSeconds);
	m_Hitbox.left -= elapsedSeconds * m_Velocity.x;
}

const Rectf& LaserBolt::GetHitbox() const
{
	return m_Hitbox;
}

int LaserBolt::GetDamage() const
{
	return m_Damage;
}