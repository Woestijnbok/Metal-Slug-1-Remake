#pragma once
#include "Texture.h"

class Sprite final
{
public:
	explicit Sprite(const Texture* const ptrTexture, int frames, int rows, int columns, float frameTime);
	~Sprite() = default;

	Sprite(const Sprite& other) = delete;
	Sprite& operator=(const Sprite& other) = delete;
	Sprite(Sprite&& other) noexcept;
	Sprite& operator=(Sprite&& other) = delete;

	void Update(float elapsedSeconds);
	void Draw(const Point2f& position = Point2f{ 0.0f, 0.0f }) const;
	float GetWidthFrame() const;
	float GetHeightFrame() const;
	bool IsAtFirstFrame() const;
	bool IsAtLastFrame() const;
	void SetMaxNumberOfCycles(int amount);
	void Reset();
	void Resume();
	void Pause();
	int GetTotalFrames() const;
	int GetCurrentFrame() const;
	void SetCurrentFrame(int frame);
	void Invert();
	bool IsInverted() const;
	bool IsPaused() const;
	void SetTexture(const Texture* const ptrTexture);
	bool Finished() const;

private:
	const Texture* m_PtrTexture;
	const int m_Frames;
	const int m_Rows;
	const int m_Columns;
	const float m_FrameTime;
	int m_CurrentFrame;
	float m_AccumulatedTime;
	bool m_IsPaused;
	bool m_IsInverted;
	int m_NumberOfCycles;
	int m_MaxNumberOfCycles;
};