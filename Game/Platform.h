#pragma once
#include "Vector2f.h"
#include "vector"

class Platform final
{
public:
	explicit Platform(const Rectf& hitbox);
	~Platform() = default;

	Platform(const Platform&) = delete;
	Platform& operator=(const Platform&) = delete;
	Platform(Platform&&) = delete;
	Platform& operator=(Platform&&) = delete;

	void HandleCollision(Rectf& actorHitbox, Vector2f& actorVelocity) const;
	bool IsOnGround(const Rectf& actorHitbox, const Vector2f& actorVelocity) const;
	void DrawDebug() const;

private:
	const Rectf m_Hitbox;
};