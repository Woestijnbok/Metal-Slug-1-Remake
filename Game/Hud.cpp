#include "base.h"
#include "Hud.h"
#include <cassert>

Hud::Hud(int lives) :
	m_MaxLives{ lives },
	m_Lives{ m_MaxLives },
	m_Time{ 0.0f },
	m_0{ "Images/Hud/Timer/0.png" },
	m_1{ "Images/Hud/Timer/1.png" },
	m_2{ "Images/Hud/Timer/2.png" },
	m_3{ "Images/Hud/Timer/3.png" },
	m_4{ "Images/Hud/Timer/4.png" },
	m_5{ "Images/Hud/Timer/5.png" },
	m_6{ "Images/Hud/Timer/6.png" },
	m_7{ "Images/Hud/Timer/7.png" },
	m_8{ "Images/Hud/Timer/8.png" },
	m_9{ "Images/Hud/Timer/9.png" },
	m_LivesIcon{ "Images/Hud/Lives Icon.png" },
	m_LevelText{ "Images/Hud/Level -.png" },
	m_LevelNumber{ "Images/Hud/1.png" }
{

}

void Hud::Draw() const
{
	DrawTimer();
	DrawLives();
	DrawLevelInfo();
}

void Hud::Update(float elapsedSeconds)
{
	m_Time += elapsedSeconds;
}

void Hud::Died()
{
	assert(0 <= m_Lives);
	--m_Lives;
}

void Hud::DrawTimer() const
{
	const Rectf vieuwport{ 0.0f, 0.0f, 300.0f, 224.0f };
	const float sizeDigit{ m_0.GetHeight() };
	Point2f position{ vieuwport.width / 2, vieuwport.height - 3.0f - sizeDigit };

	int truncatedTime{ int(trunc(m_Time)) };

	if (truncatedTime >= 100)
	{
		position.x -= 1.5f * sizeDigit;

		const int firstDigit{ truncatedTime / 100 };
		const int secondDigit{ (truncatedTime - (100 * firstDigit)) / 10 };
		const int ThirdDigit{ truncatedTime - (100 * firstDigit) - (10 * secondDigit) };

		DrawDigit(position, firstDigit);
		DrawDigit(position, secondDigit);
		DrawDigit(position, ThirdDigit);
	}
	else if (truncatedTime >= 10)
	{
		position.x -= 1.0f * sizeDigit;

		const int firstDigit{ truncatedTime / 10 };
		const int secondDigit{ truncatedTime - (10 * firstDigit) };

		DrawDigit(position, firstDigit);
		DrawDigit(position, secondDigit);
	}
	else if (truncatedTime >= 0)
	{
		position.x -= 0.5f * sizeDigit;

		const int firstDigit{ truncatedTime };

		DrawDigit(position, firstDigit);
	}
}

void Hud::DrawDigit(Point2f& position, int number) const
{
	switch (number)
	{
	case 0:
		m_0.Draw(position);
		position.x += m_0.GetWidth();
		break;
	case 1:
		m_1.Draw(position);
		position.x += m_1.GetWidth();
		break;
	case 2:
		m_2.Draw(position);
		position.x += m_2.GetWidth();
		break;
	case 3:
		m_3.Draw(position);
		position.x += m_3.GetWidth();
		break;
	case 4:
		m_4.Draw(position);
		position.x += m_4.GetWidth();
		break;
	case 5:
		m_5.Draw(position);
		position.x += m_5.GetWidth();
		break;
	case 6:
		m_6.Draw(position);
		position.x += m_6.GetWidth();
		break;
	case 7:
		m_7.Draw(position);
		position.x += m_7.GetWidth();
		break;
	case 8:
		m_8.Draw(position);
		position.x += m_8.GetWidth();
		break;
	case 9:
		m_9.Draw(position);
		position.x += m_9.GetWidth();
		break;
	}
}

void Hud::DrawLives() const
{
	Point2f position{ 3.0f, 3.0f };
	const float spacing{ m_LivesIcon.GetWidth() + 2.0f };

	for (int i{}; i < m_Lives; ++i)
	{
		m_LivesIcon.Draw(position);
		position.x += spacing;
	}
}

void Hud::DrawLevelInfo() const
{
	const Rectf vieuwport{ 0.0f, 0.0f, 300.0f, 224.0f };
	Point2f position{ vieuwport.width / 2 - ((m_LevelText.GetWidth() + m_LevelNumber.GetWidth() + 2.0f) / 2.0f), 3.0f};


	m_LevelText.Draw(position);
	position.x += m_LevelText.GetWidth() + 2.0f;
	m_LevelNumber.Draw(Rectf{ position.x, position.y, m_LevelNumber.GetWidth() / 2.0f, m_LevelNumber.GetHeight() / 2.0f });
}

void Hud::Reset()
{
	m_Lives = m_MaxLives;
	m_Time = 0.0f;
}