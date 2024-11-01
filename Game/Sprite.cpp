#include "base.h"
#include <cassert>
#include "Sprite.h"

Sprite::Sprite(const Texture* const ptrTexture, int frames, int rows, int columns, float frameTime) :
	m_PtrTexture{ ptrTexture },
	m_Frames{ frames },
	m_Rows{ rows },
	m_Columns{ columns },
	m_FrameTime{ frameTime },
	m_CurrentFrame{ 0 },
	m_AccumulatedTime{ 0.0f },
	m_IsPaused{ false },
	m_IsInverted{ false },
	m_NumberOfCycles{ 0 },
	m_MaxNumberOfCycles{ -1 } // any number below 0 is inf
{

}

Sprite::Sprite(Sprite&& other) noexcept :
	m_PtrTexture{ other.m_PtrTexture },
	m_Frames{ other.m_Frames },
	m_Rows{ other.m_Rows },
	m_Columns{ other.m_Columns },
	m_FrameTime{ other.m_FrameTime },
	m_CurrentFrame{ other.m_CurrentFrame },
	m_AccumulatedTime{ other.m_AccumulatedTime },
	m_IsPaused{ other.m_IsPaused },
	m_IsInverted{ other.m_IsInverted },
	m_NumberOfCycles{ other.m_NumberOfCycles },
	m_MaxNumberOfCycles{ other.m_MaxNumberOfCycles }
{
	
}

void Sprite::Update(float elapsedSeconds)
{
	if (!m_IsPaused)
	{
		m_AccumulatedTime += elapsedSeconds;

		if (m_AccumulatedTime > m_FrameTime)
		{
			if (m_IsInverted)
			{
				if (m_CurrentFrame == 0)
				{
					++m_NumberOfCycles;
				}

				if (m_NumberOfCycles == m_MaxNumberOfCycles)
				{
					Pause();
				}
				else
				{
					--m_CurrentFrame;

					if (m_CurrentFrame == -1)
					{
						m_CurrentFrame = m_Frames - 1;
					}
				}
			}
			else
			{
				if (m_CurrentFrame == m_Frames - 1)
				{
					++m_NumberOfCycles;
				}
				

				if (m_NumberOfCycles == m_MaxNumberOfCycles)
				{
					Pause();
				}
				else
				{
					++m_CurrentFrame;
					m_CurrentFrame %= m_Frames;
				}

			}

			m_AccumulatedTime = 0.0f;
		}
	}
}

void Sprite::Draw(const Point2f& position) const
{
	Rectf sourceRectf{};

	sourceRectf.width = m_PtrTexture->GetWidth() / m_Columns;
	sourceRectf.height = m_PtrTexture->GetHeight() / m_Rows;
	sourceRectf.left = (m_CurrentFrame % m_Columns) * sourceRectf.width;
	sourceRectf.bottom = ((m_CurrentFrame / m_Columns) + 1) * sourceRectf.height;

	m_PtrTexture->Draw(position, sourceRectf);
}

float Sprite::GetWidthFrame() const
{
	return m_PtrTexture->GetWidth() / m_Columns;
}

float Sprite::GetHeightFrame() const
{
	return m_PtrTexture->GetHeight() / m_Rows;
}

bool Sprite::IsAtFirstFrame() const
{
	return m_CurrentFrame  == 0;
}

bool Sprite::IsAtLastFrame() const
{
	return m_CurrentFrame + 1 == m_Frames;
}

void Sprite::SetMaxNumberOfCycles(int amount)
{
	m_MaxNumberOfCycles = amount;
}

void Sprite::Reset()
{
	m_CurrentFrame = 0;
	m_AccumulatedTime = 0.0f;
	m_IsPaused = false;
	m_IsInverted = false;
	m_NumberOfCycles = 0;
}

void Sprite::Resume()
{
	if (m_IsPaused)
	{
		m_IsPaused = false;
	}
}

void Sprite::Pause()
{
	if (!m_IsPaused)
	{
		m_IsPaused = true;
	}
}

int Sprite::GetCurrentFrame() const
{
	return m_CurrentFrame;
}

int Sprite::GetTotalFrames() const
{
	return m_Frames;
}

void Sprite::SetCurrentFrame(int frame)
{
	assert(frame > 0 && frame < m_Frames);
	m_CurrentFrame = frame;
}

void Sprite::Invert()
{
	m_IsInverted = !m_IsInverted;
}

bool Sprite::IsInverted() const
{
	return m_IsInverted;
}

bool Sprite::IsPaused() const
{
	return m_IsPaused;
}

void Sprite::SetTexture(const Texture* const ptrTexture)
{
	m_PtrTexture = ptrTexture;
}

bool Sprite::Finished() const
{
	return m_NumberOfCycles == m_MaxNumberOfCycles;
}