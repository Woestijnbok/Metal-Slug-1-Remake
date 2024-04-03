#include "pch.h"
#include "Level.h"
#include "utils.h"
#include "SVGParser.h"
#include "iostream"

Level::Level() :
	m_RockWaterfallBackgroundTexture{ "Images/Level/Background/Rock Waterfall Sprite.png" },
	m_FarWaterfallBackgroundTexture{ "Images/Level/Background/Far Waterfall Sprite.png" },
	m_WaterHutsBackgroundTexture{ "Images/Level/Background/Water Huts Sprite.png" },
	m_WaterNoBoatBackgroundTexture{ "Images/Level/Background/Water No Boat Sprite.png" },
	m_BoatBackgroundTexture{ "Images/Level/Background/Boat Sprite.png" },
	m_LowWaterfallForegroundTexture{ "Images/Level/Foreground/Low Waterfall Sprite.png" },
	m_WaterHutsForegroundTexture{ "Images/Level/Foreground/Water Huts Sprite.png" },
	m_WaterNoBoatForgroundTexture{ "Images/Level/Foreground/Water No Boat Sprite.png" },
	m_BotttomWaterTexture{ "Images/Boss/Bottom Water Sprite.png" },
	m_VentTexture{ "Images/Boss/Vent Texture.png" },
	m_MainBackgroundTexture{ "Images/Level/Background/Main Texture.png" },
	m_PalmBackgroundTexture{ "Images/Level/Background/Palm Texture.png" },
	m_ColorFill2BackgroundTexture{ "Images/Level/Background/Color Fill 2 Texture.png" },
	m_ColorFill1BackgroundTexture{ "Images/Level/Background/Color Fill 1 Texture.png" },
	m_RockWaterfallBackgroundSprite{ &m_RockWaterfallBackgroundTexture, 8, 1, 8, 1.0f / 8.0f },
	m_FarWaterfallBackgroundSprite{ &m_FarWaterfallBackgroundTexture, 8, 2, 4, 1.0f / 8.0f },
	m_WaterHutsBackgroundSprite{ &m_WaterHutsBackgroundTexture, 8, 8, 1, 1.0f / 8.0f },
	m_WaterNoBoatBackgroundSprite{ &m_WaterNoBoatBackgroundTexture, 8, 8, 1, 1.0f / 8.0f },
	m_BoatBackgroundSprite{ &m_BoatBackgroundTexture, 8, 2, 4, 1.0f / 8.0f },
	m_LowWaterfallForegroundSprite{ &m_LowWaterfallForegroundTexture, 8, 2, 4, 1.0f / 8.0f },
	m_WaterHutsForegroundSprite{ &m_WaterHutsForegroundTexture, 8, 8, 1, 1.0f / 8.0f },
	m_WaterNoBoatForgroundSprite{ &m_WaterNoBoatForgroundTexture, 8, 8, 1, 1.0f / 8.0f },
	m_BotttomWaterSprite{ &m_BotttomWaterTexture, 8, 2, 4, 1.0f / 8.0f },
	m_Vertices {},
	m_Boundaries{ 0.0f, 0.0f, m_MainBackgroundTexture.GetWidth(), m_MainBackgroundTexture.GetHeight() },
	m_PlatformManager{}
{
	std::vector<std::vector<Point2f>> vertices{};
	SVGParser::GetVerticesFromSvgFile("Level.svg", vertices);
	m_Vertices = vertices[0];
}

void Level::DrawBackground() const
{
	m_ColorFill1BackgroundTexture.Draw();
	m_ColorFill2BackgroundTexture.Draw(Point2f{ 3068.0f, 0.0f });
	m_BoatBackgroundSprite.Draw(Point2f{ 3221.0f, 32.0f });
	m_PalmBackgroundTexture.Draw(Point2f{ 1816.0f, 48.0f });
	m_WaterNoBoatBackgroundSprite.Draw(Point2f{ 2761.0f, 32.0f });
	m_WaterNoBoatBackgroundSprite.Draw(Point2f{ 3045.0f, 32.0f });
	m_MainBackgroundTexture.Draw();
	m_WaterHutsBackgroundSprite.Draw(Point2f{ 1860.0f, 32.0f });
	m_FarWaterfallBackgroundSprite.Draw(Point2f{ 3747.0f, 160.0f });
	m_RockWaterfallBackgroundSprite.Draw(Point2f{ 3338.0f, 32.0f });
}

void Level::DrawDebug() const
{
	const Color4f black{ 0.0f, 0.0f, 0.0f, 1.0f };
	utils::SetColor(black);
	utils::DrawPolygon(m_Vertices, true, 2.0f);
	m_PlatformManager.DrawDebug();
}

void Level::DrawForeground() const
{
	m_WaterHutsForegroundSprite.Draw(Point2f{ 1860.0f, 0.0f });
	m_WaterNoBoatForgroundSprite.Draw(Point2f{ 2761.0f, 0.0f });
	m_LowWaterfallForegroundSprite.Draw(Point2f{ 3320.0f, 0.0f });
	m_BotttomWaterSprite.Draw(Point2f{ 3768.0f + 224.0f, 80.0f });
	//m_VentTexture.Draw(Point2f{ 3768.0f + 256.0f, 80.0f + 59.0f });
}

void Level::HandleCollision(Rectf& actorShape, Vector2f& actorVelocity) const
{
	// Horizontal ray cast

	Point2f startPointRay{ actorShape.left - 1.0f, actorShape.bottom + (actorShape.height / 2.0f) };
	Point2f endPointRay{ actorShape.left + actorShape.width + 1.0f, actorShape.bottom + (actorShape.height / 2.0f) };
	utils::HitInfo hitInfo{};

	if (utils::Raycast(m_Vertices, startPointRay, endPointRay, hitInfo))
	{
		if (actorVelocity.x > 0.0f) // looking to the right
		{
			actorShape.left = hitInfo.intersectPoint.x - actorShape.width;
		}
		else // looking to the left
		{
			actorShape.left = hitInfo.intersectPoint.x;
		}
		
		actorVelocity.x = 0.0f;
	}

	// Vertical raycast

	startPointRay = Point2f{ actorShape.left + (actorShape.width / 2.0f), actorShape.bottom - 1.0f };
	endPointRay = Point2f{ actorShape.left + (actorShape.width / 2.0f), actorShape.bottom + actorShape.height };
	hitInfo = utils::HitInfo{};

	if (utils::Raycast(m_Vertices, startPointRay, endPointRay, hitInfo))
	{
		actorShape.bottom = hitInfo.intersectPoint.y;
		actorVelocity.y = 0.0f;
	}

	m_PlatformManager.HandleCollision(actorShape, actorVelocity);
}

bool Level::IsOnGround(const Rectf& actorShape, Vector2f& actorVelocity) const
{
	if (actorVelocity.y == 0.0f) // we are not falling
	{
		const Point2f startPointRay{ actorShape.left + (actorShape.width / 2.0f), actorShape.bottom - 1.0f };
		const Point2f endPointRay{ actorShape.left + (actorShape.width / 2.0f), actorShape.bottom + actorShape.height };
		utils::HitInfo hitInfo{};

		if (utils::Raycast(m_Vertices, startPointRay, endPointRay, hitInfo)) // he is on the level ground
		{
			return true;
		}
		else // since he is not on the main ground we check if he is on a platform
		{
			return m_PlatformManager.IsOnGround(actorShape, actorVelocity);
		}
	}

	return false;
}

Rectf Level::GetBoundaries() const
{
	return m_Boundaries;
}

const std::vector<Point2f>& Level::GetGround() const
{
	return m_Vertices;
}

void Level::Update(float elapsedSeconds)
{
	m_FarWaterfallBackgroundSprite.Update(elapsedSeconds);
	m_BoatBackgroundSprite.Update(elapsedSeconds);
	m_RockWaterfallBackgroundSprite.Update(elapsedSeconds);
	m_WaterHutsBackgroundSprite.Update(elapsedSeconds);
	m_WaterNoBoatBackgroundSprite.Update(elapsedSeconds);
	m_LowWaterfallForegroundSprite.Update(elapsedSeconds);
	m_WaterHutsForegroundSprite.Update(elapsedSeconds);
	m_WaterNoBoatForgroundSprite.Update(elapsedSeconds);
	m_BotttomWaterSprite.Update(elapsedSeconds);
}