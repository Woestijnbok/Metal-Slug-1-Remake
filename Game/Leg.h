#pragma once
#include "Texture.h"
#include "Sprite.h"

class Leg final
{
public:
	enum class State
	{
		idle,
		walking,
		jumping,
		NumberOfElements
	};

	explicit Leg(const State state);
	~Leg() = default;

	Leg(const Leg& other) = delete;
	Leg& operator=(const Leg& other) = delete;
	Leg(Leg&& other) = delete;
	Leg& operator=(Leg&& other) = delete;

	void SetState(const State state);
	void Update(float elapsedSeconds);
	void Draw() const;
	void Reset();
	Leg::State GetState() const;

private:
	const Texture m_ArrTextures[int(State::NumberOfElements)];
	Sprite m_ArrSprites[int(State::NumberOfElements)];
	const Point2f m_ArrOffsets[int(State::NumberOfElements)];
	State m_State;
};