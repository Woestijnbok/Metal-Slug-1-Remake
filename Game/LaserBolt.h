#pragma once
#include "Projectile.h"
#include "Texture.h"
#include "Vector2f.h"
#include "Sprite.h"
#include "Texture.h"

class LaserBolt : public Projectile
{
public:
	explicit LaserBolt(const Point2f& position);
	virtual ~LaserBolt();

	LaserBolt(const LaserBolt&) = delete;
	LaserBolt& operator=(const LaserBolt&) = delete;
	LaserBolt(LaserBolt&&) = delete;
	LaserBolt& operator=(LaserBolt&&) = delete;

	virtual void Draw() const override;
	virtual void DrawDebug() const override;
	virtual void Update(float elapsedSeconds) override;
	virtual const Rectf& GetHitbox() const override;
	virtual int GetDamage() const override;

private:
	static int m_InstanceCounter;
	static const Texture* m_PtrTexture;
	static const int m_Damage;
	static const Vector2f m_Velocity;

	Sprite m_Sprite;
	Rectf m_Hitbox;
};