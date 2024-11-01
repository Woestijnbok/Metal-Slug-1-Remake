#include "base.h"
#include "Parralax.h"
#include "Texture.h"

Parralax::Parralax(const Texture* const pointerTexture, const Point2f& startPoint, const Point2f& endPoint, const Rectf vieuwport, float scale)	:
	m_PtrTexture{ pointerTexture },
	m_StartPoint{ startPoint },
	m_EndPoint{ endPoint },
	m_CurrentPosition{ startPoint },
	m_Vieuwport{ vieuwport },
	m_Scale{ scale }
{

}

Parralax::~Parralax()
{
	delete m_PtrTexture;
}

void Parralax::Draw() const
{
	m_PtrTexture->Draw(m_CurrentPosition);
}

void Parralax::Update(float elapsedSeconds, float actorSpeed, float actorPositionX)
{
	if (actorPositionX >= (m_StartPoint.x - (300.0f / 2.0f )) && actorPositionX <= (m_StartPoint.x + (300.0f / 2.0f)))
	{
		const float distanceParralax{ m_EndPoint.x - m_StartPoint.x - m_PtrTexture->GetWidth() };
		const float distanceActor{ m_EndPoint.x - m_StartPoint.x + (300.0f) };

		const float speed{ (distanceParralax / distanceActor) * actorSpeed };
		m_CurrentPosition.x += (elapsedSeconds * speed);
	}
}