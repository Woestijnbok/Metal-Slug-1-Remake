#pragma once
#include "Projectile.h"
#include "Texture.h"
#include "Vector2f.h"
#include "Sprite.h"

class Plasma : public Projectile
{
public:
	explicit Plasma(const Point2f& position, const Vector2f& velocity);
	virtual ~Plasma();

	Plasma(const Plasma&) = delete;
	Plasma& operator=(const Plasma&) = delete;
	Plasma(Plasma&&) = delete;
	Plasma& operator=(Plasma&&) = delete;

	virtual void Draw() const override;
	virtual void DrawDebug() const override;
	virtual void Update(float elapsedSeconds) override;
	virtual const Rectf& GetHitbox() const override;
	virtual int GetDamage() const override;

private:
	static int m_InstanceCounter;
	static const Texture* m_PtrTexture;
	static const Vector2f m_Acceleration;
	static const int m_Damage;

	Sprite m_Sprite;
	Rectf m_Hitbox;
	Vector2f m_Velocity;
};

