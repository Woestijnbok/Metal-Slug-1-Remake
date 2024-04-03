#pragma once
#include "Texture.h"
#include "Sprite.h"

class Torso final
{
public:
	enum class State
	{
		idle,
		walking,
		jumping,
		shooting,
		NumberOfElements
	};

	explicit Torso(const State state);
	~Torso() = default;

	Torso(const Torso& other) = delete;
	Torso& operator=(const Torso& other) = delete;
	Torso(Torso&& other) = delete;
	Torso& operator=(Torso&& other) = delete;

	void SetState(const State state);
	void Update(float elapsedSeconds);
	void Draw() const;
	void Reset();
	Torso::State GetState() const;
	bool FinishedShooting() const;

private:
	const Texture m_ArrTextures[int(State::NumberOfElements)];
	Sprite m_ArrSprites[int(State::NumberOfElements)];
	const Point2f m_ArrOffsets[int(State::NumberOfElements)];
	State m_State;
};