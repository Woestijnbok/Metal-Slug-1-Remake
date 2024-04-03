#pragma once
#include "Projectile.h"
#include "Enumerations.h"
#include "Vector2f.h"
#include "Texture.h"

class RifleBullet : public Projectile
{
public:
	explicit RifleBullet(const Direction direction, const Point2f& position);
	virtual ~RifleBullet();

	RifleBullet(const RifleBullet& other) = delete;
	RifleBullet& operator=(const RifleBullet& other) = delete;
	RifleBullet(RifleBullet&& other) = delete;
	RifleBullet& operator=(RifleBullet&& other) = delete;

	virtual void Draw() const override;
	virtual void DrawDebug() const override;
	virtual void Update(float elapsedSeconds) override;
	virtual const Rectf& GetHitbox() const override;
	virtual int GetDamage() const override;

private:
	static int m_InstanceCounter;
	static const Texture* m_PtrTexture;
	static const Vector2f m_Velocity;
	static const int m_Damage;

	Rectf m_Hitbox;
	const Direction m_Direction;
};