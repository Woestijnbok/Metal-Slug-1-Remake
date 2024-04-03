#pragma once
#include "structs.h"
#include "vector"
#include "Vector2f.h"
#include "Sprite.h"
#include "Texture.h"
#include "PlatformManager.h"

class Level final
{
public:
	explicit Level();
	~Level() = default;

	Level(const Level& other) = delete;
	Level& operator=(const Level& other) = delete;
	Level(Level&& other) = delete;
	Level& operator=(Level&& other) = delete;

	void DrawBackground() const;
	void DrawForeground() const;
	void HandleCollision(Rectf& actorShape, Vector2f& actorVelocity) const;
	bool IsOnGround(const Rectf& actorShape, Vector2f& actorVelocity) const;
	Rectf GetBoundaries() const;
	const std::vector<Point2f>& GetGround() const;
	void Update(float elapsedSeconds);
	void DrawDebug() const;

private:
	const Texture m_RockWaterfallBackgroundTexture;
	const Texture m_FarWaterfallBackgroundTexture;
	const Texture m_WaterHutsBackgroundTexture;
	const Texture m_WaterNoBoatBackgroundTexture;
	const Texture m_BoatBackgroundTexture;
	const Texture m_LowWaterfallForegroundTexture;
	const Texture m_WaterHutsForegroundTexture;
	const Texture m_WaterNoBoatForgroundTexture;
	const Texture m_BotttomWaterTexture;
	const Texture m_VentTexture;
	const Texture m_MainBackgroundTexture;
	const Texture m_PalmBackgroundTexture;
	const Texture m_ColorFill2BackgroundTexture;
	const Texture m_ColorFill1BackgroundTexture;
	Sprite m_RockWaterfallBackgroundSprite;
	Sprite m_FarWaterfallBackgroundSprite;
	Sprite m_WaterHutsBackgroundSprite;
	Sprite m_WaterNoBoatBackgroundSprite;
	Sprite m_BoatBackgroundSprite;
	Sprite m_LowWaterfallForegroundSprite;
	Sprite m_WaterHutsForegroundSprite;
	Sprite m_WaterNoBoatForgroundSprite;
	Sprite m_BotttomWaterSprite;
	std::vector<Point2f> m_Vertices;
	const Rectf m_Boundaries;
	PlatformManager m_PlatformManager;
};