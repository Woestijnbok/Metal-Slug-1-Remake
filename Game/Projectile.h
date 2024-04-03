#pragma once
#include "EnemyManager.h"

class Projectile
{
public:
	explicit Projectile() = default;
	virtual ~Projectile() = default;

	Projectile(const Projectile& other) = delete;
	Projectile& operator=(const Projectile& other) = delete;
	Projectile(Projectile&& other) = delete;
	Projectile& operator=(Projectile&& other) = delete;

	virtual void Draw() const = 0;
	virtual void DrawDebug() const = 0;
	virtual void Update(float elapsedSeconds) = 0;
	virtual const Rectf& GetHitbox() const = 0;
	virtual int GetDamage() const = 0;

protected:


private:

};