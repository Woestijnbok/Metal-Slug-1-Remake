#include "pch.h"
#include "Leg.h"

Leg::Leg(const State state) :
	m_ArrTextures{
					Texture{ "Images/Character/Leg/Idle Texture.png" },
					Texture{ "Images/Character/Leg/Walking Sprite.png" },
					Texture{ "Images/Character/Leg/Jumping Sprite.png" }
					},
	m_ArrSprites{
					Sprite{ &m_ArrTextures[0], 1, 1, 1, 1.0f },
					Sprite{ &m_ArrTextures[1], 6, 2, 3, 1.0f / 6.0f },
					Sprite{ &m_ArrTextures[2], 6, 2, 3, 1.0f / 6.0f }
					},
	m_ArrOffsets{
					Point2f{ 4.0f, 16.0f },
					Point2f{ 8.0f, 20.0f },
					Point2f{ 3.0f, 23.0f }
					},
	m_State{ state }
{

}

void Leg::SetState(const State state)
{
	m_State = state;
}

void Leg::Update(float elapsedSeconds)
{
	m_ArrSprites[int(m_State)].Update(elapsedSeconds);
}

void Leg::Draw() const
{
	const Point2f offset{ m_ArrOffsets[int(m_State)] };

	glPushMatrix();
		m_ArrSprites[int(m_State)].Draw();
		glTranslatef(offset.x, offset.y, 0.0f);
}

void Leg::Reset()
{
	for (auto& sprite : m_ArrSprites)
	{
		sprite.Reset();
	}
}

Leg::State Leg::GetState() const
{
	return m_State;
}