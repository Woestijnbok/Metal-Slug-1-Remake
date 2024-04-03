#include "pch.h"
#include "Torso.h"

Torso::Torso(const State state) :
	m_ArrTextures{
					Texture{"Images/Character/Torso/Idle Sprite.png"},
					Texture{"Images/Character/Torso/Walking Sprite.png"},
					Texture{"Images/Character/Torso/Jumping Sprite.png"},
					Texture{"Images/Character/Torso/Shooting Right Sprite.png"}
					},
	m_ArrSprites{
					Sprite{ &m_ArrTextures[0], 4, 2, 2, 1.0f / 4.0f },
					Sprite{&m_ArrTextures[1], 6, 2, 3, 1.0f / 6.0f },
					Sprite{&m_ArrTextures[2], 6, 2, 3, 1.0f / 6.0f },
					Sprite{&m_ArrTextures[3], 10, 3, 4, 1.0f / 10.0f }
					},
	m_ArrOffsets{
					Point2f{ -7.0f, -6.0f },
					Point2f{ -8.0f, -6.0f },
					Point2f{ -9.0f, -2.0f },
					Point2f{ -6.0f, -6.0f}
					},
	m_State{state}
{

}

void Torso::SetState(const State state)
{
	m_State = state;
}

void Torso::Update(float elapsedSeconds)
{
	m_ArrSprites[int(m_State)].Update(elapsedSeconds);
}

void Torso::Draw() const
{
	const Point2f offset{m_ArrOffsets[int(m_State)]};

		glTranslatef(offset.x, offset.y, 0.0f);
		m_ArrSprites[int(m_State)].Draw();
	glPopMatrix();
}

void Torso::Reset()
{
	for (auto& sprite : m_ArrSprites)
	{
		sprite.Reset();
	}
}

Torso::State Torso::GetState() const
{
	return m_State;
}

bool Torso::FinishedShooting() const
{
	return m_ArrSprites[int(State::shooting)].IsAtLastFrame();
}