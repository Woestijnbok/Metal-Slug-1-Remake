#include "base.h"
#include "Camera.h"
#include "algorithm"
#include "utils.h"
#include "Level.h"
#include "Avatar.h"

Camera::Camera(const Rectf& vieuwport) :
	m_Width{ vieuwport.width / 3.0f },
	m_Height{ vieuwport.height / 3.0f },
	m_Boundaries{},
	m_IndexCurrentBoundary{ 0 },
	m_PtrLevel{ nullptr },
	m_PtrPlayer{ nullptr }
{
	AddAndSetBoundary(Rectf{ 0.0f, 0.0f, 3480.0f, 224.0f });
	AddBoundary(Rectf{ 3359.0f, 39.0f, 300.0f, 224.0f });
	AddBoundary(Rectf{ 3521.0f, 80.0f, 300.0f, 224.0f });
	AddBoundary(Rectf{ 3747.0f, 112.0f, 405.0f, 224.0f });
}

void Camera::SetGameInformation(const Level& level, const Avatar& player)
{
	m_PtrLevel = &level;
	m_PtrPlayer = &player;
}

bool Camera::AddAndSetBoundary(const Rectf& boundary)
{
	if (IsValidBoundary(boundary))
	{
		m_Boundaries.push_back(boundary);

		if (int(m_Boundaries.size()) == 0)
		{
			m_IndexCurrentBoundary = 0;
		}
		else
		{
			m_IndexCurrentBoundary = int(m_Boundaries.size()) - 1;
		}

		return true;
	}

	return false;
}

bool Camera::AddBoundary(const Rectf& boundary)
{
	if (IsValidBoundary(boundary))
	{
		m_Boundaries.push_back(boundary);

		return true;
	}

	return false;
}

void Camera::Translate() const
{
	Point2f cameraBottomLeft{ Track(m_PtrPlayer->GetHitbox()) };

	Clamp(cameraBottomLeft);

	glTranslatef(-cameraBottomLeft.x, -cameraBottomLeft.y, 0.0f);
}

Point2f Camera::Track(const Rectf& targetRectf) const
{
	float x{ targetRectf.left + (targetRectf.width / 2.0f) - (m_Width / 2.0f) };
	float y{ targetRectf.bottom + (targetRectf.height / 2.0f) - (m_Height / 2.0f) };

	return Point2f{ x, y };
}

void Camera::Clamp(Point2f& point) const
{
	point.x = float(std::min(point.x, (m_Boundaries[m_IndexCurrentBoundary].left + m_Boundaries[m_IndexCurrentBoundary].width - m_Width))); // To much to the right
	point.x = float(std::max(point.x, m_Boundaries[m_IndexCurrentBoundary].left)); // To much to the left

	point.y = float(std::min(point.y, (m_Boundaries[m_IndexCurrentBoundary].bottom + m_Boundaries[m_IndexCurrentBoundary].height - m_Height))); // To high
	point.y = float(std::max(point.y, m_Boundaries[m_IndexCurrentBoundary].bottom)); // To Low
}

void Camera::Update()
{
	for (int i{ int(m_Boundaries.size() - 1) }; i >= 0; --i)
	{
		if (TargetRectfIsInBoundary(m_PtrPlayer->GetHitbox(), m_Boundaries[i]))
		{
			if (m_IndexCurrentBoundary != i)
			{
				m_IndexCurrentBoundary = i;

				return;
			}

			return;
		}
	}
}

bool Camera::TargetRectfIsInBoundary(const Rectf& targetRectf, const Rectf& boundary) const
{
	if ((targetRectf.left + targetRectf.width) > (boundary.left + boundary.width)) // to far to the right
	{
		return false;
	}
	else if (targetRectf.left < boundary.left)
	{
		return false;
	}
	else if ((targetRectf.bottom + targetRectf.height) > (boundary.bottom + boundary.height))
	{
		return false;
	}
	else if (targetRectf.bottom < boundary.bottom)
	{
		return false;
	}

	return true;
}

void Camera::DrawDebug() const
{
	const Color4f blue{ 0.2f, 0.2f, 1.0f, 0.5f };
	utils::SetColor(blue);

	for (auto& boundary : m_Boundaries)
	{
		utils::FillRect(boundary);
	}
}

bool Camera::IsValidBoundary(const Rectf& boundary) const
{
	return (boundary.width >= m_Width) && (boundary.height >= m_Height);
}

void Camera::Reset()
{
	m_IndexCurrentBoundary = 0;
}