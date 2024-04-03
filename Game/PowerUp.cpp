#include "pch.h"
#include "PowerUp.h"
#include "Texture.h"
#include "utils.h"

PowerUp::PowerUp(const Point2f& center, PowerUp::Type type) :
	m_Type{ type },
	m_pTexture{ new Texture{"Images/PowerUp.png"} },
	m_RotSpeed{ 360.0f },
	m_TextClip{ Rectf{ 0.0f, m_pTexture->GetHeight() / 2.0f * int(m_Type), m_pTexture->GetWidth(), m_pTexture->GetHeight() / 2.0f } },
	m_Shape{ Circlef{ center, m_TextClip.width / 2.0f } },
	m_Angle{ 0.0f }
{
}

PowerUp::~PowerUp()
{
	delete m_pTexture;
	m_pTexture = nullptr;
}

void PowerUp::Update(float elapsedSec)
{
	m_Angle += (m_RotSpeed * elapsedSec);
}

void PowerUp::Draw() const
{
	glPushMatrix();
		glTranslatef(m_Shape.center.x, m_Shape.center.y, 0.0f);
		glRotatef(m_Angle, 0.0f, 0.0f, 1.0f);
		glScalef(1.0f, 1.0f, 1.0f);
		m_pTexture->Draw(Point2f{ -m_pTexture->GetWidth() / 2.0f, -m_pTexture->GetHeight() / 4.0f }, m_TextClip);
	glPopMatrix();
}

bool PowerUp::IsOverlapping(const Rectf& rect) const
{
	return utils::IsOverlapping(rect, m_Shape);
}