#include "base.h"
#include "Platform.h"
#include "utils.h"

Platform::Platform(const Rectf& hitbox) :
	m_Hitbox{ hitbox }
{

}

void Platform::HandleCollision(Rectf& actorHitbox, Vector2f& actorVelocity) const
{
	if (actorVelocity.y <= 0.0f) // we are falling
	{
		const float margin{ 3.0f };

		if (utils::IsOverlapping(m_Hitbox, actorHitbox))
		{
			if (actorHitbox.bottom >= m_Hitbox.bottom - margin)
			{
				actorHitbox.bottom = m_Hitbox.bottom + m_Hitbox.height;
				actorVelocity.y = 0.0f;
			}
		}
	}
}

bool Platform::IsOnGround(const Rectf& actorHitbox, const Vector2f& actorVelocity) const
{
	if (actorVelocity.y == 0.0f) // we are not falling
	{
		if (actorHitbox.bottom == (m_Hitbox.bottom + m_Hitbox.height))
		{
			return true;
		}
		else
		{
			return false;
		}
	}

	return false;
}

void Platform::DrawDebug() const
{
	utils::DrawRect(m_Hitbox, 2.0f);
}