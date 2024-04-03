#pragma once
#include "vector"
#include "structs.h"

class Avatar;
class Level;

class Camera final
{
public:
	explicit Camera(const Rectf& vieuwport);
	~Camera() = default;

	Camera(const Camera& other) = delete;
	Camera& operator=(const Camera& other) = delete;
	Camera(Camera&& other) = delete;
	Camera& operator=(Camera&& other) = delete;

	bool AddAndSetBoundary(const Rectf& boundary);
	bool AddBoundary(const Rectf& boundary);
	void Translate() const;
	void Update();
	void DrawDebug() const;
	void SetGameInformation(const Level& level, const Avatar& player);
	void Reset();

private:
	const float m_Width;
	const float m_Height;
	std::vector<Rectf> m_Boundaries;
	int m_IndexCurrentBoundary;
	const Level* m_PtrLevel;
	const Avatar* m_PtrPlayer;

	Point2f Track(const Rectf& targetRectf) const;
	void Clamp(Point2f& point) const;
	bool TargetRectfIsInBoundary(const Rectf& targetRectf, const Rectf& boundary) const;
	bool IsValidBoundary(const Rectf& boundary) const;
};