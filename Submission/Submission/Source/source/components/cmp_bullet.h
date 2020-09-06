#pragma once

#include <ecm.h>

class BulletComponent : public Component
{
protected:
	float _lifetime;

public:
	BulletComponent() = delete;
	void update(double dt)override;
	void render()override;
	explicit BulletComponent(Entity* p, float lifetime = 3.f);
};