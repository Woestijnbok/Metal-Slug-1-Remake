#pragma once
#include "vector"
#include "Vector2f.h"

class Platform;

class PlatformManager final
{
public:
	explicit PlatformManager();
	~PlatformManager();

	PlatformManager(const PlatformManager&) = delete;
	PlatformManager& operator=(const PlatformManager&) = delete;
	PlatformManager(PlatformManager&&) = delete;
	PlatformManager& operator=(PlatformManager&&) = delete;

	void HandleCollision(Rectf& actorHitbox, Vector2f& actorVelocity) const;
	bool IsOnGround(const Rectf& actorHitbox, const Vector2f& actorVelocity) const;
	void DrawDebug() const;

private:
	std::vector<Platform*> m_Platforms;
};