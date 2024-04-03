#pragma once

class Texture;

class Parralax final
{
public:
	Parralax(const Texture* const pointerTexture, const Point2f& startPoint, const Point2f& endPoint, const Rectf vieuwport, float scale);
	~Parralax();

	Parralax(const Parralax& other) = delete;
	Parralax& operator=(const Parralax& other) = delete;
	Parralax(Parralax&& other) = delete;
	Parralax& operator=(Parralax&& other) = delete;

	void Draw() const;
	void Update(float elapsedSeconds, float actorSpeed, float actorPositionX);
private:
	const Texture* const m_PtrTexture;
	const Point2f m_StartPoint;
	const Point2f m_EndPoint;
	Point2f m_CurrentPosition;
	const Rectf& m_Vieuwport;
	const float m_Scale;
};