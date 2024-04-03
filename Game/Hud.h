#pragma once
#include "Texture.h"

class Hud final
{
public:
	explicit Hud(int lives);
	~Hud() = default;

	Hud(const Hud&) = delete;
	Hud& operator=(const Hud&) = delete;
	Hud(Hud&&) = delete;
	Hud& operator=(Hud&&) = delete;

	void Draw() const;
	void Update(float elapsedSeconds);
	void Died();
	void Reset();

private:
	int m_MaxLives;
	int m_Lives;
	float m_Time;
	const Texture m_0, m_1, m_2, m_3, m_4, m_5, m_6, m_7, m_8, m_9;
	const Texture m_LivesIcon;
	const Texture m_LevelText, m_LevelNumber;

	void DrawTimer() const;
	void DrawDigit(Point2f& position, int number) const;
	void DrawLives() const;
	void DrawLevelInfo() const;
};