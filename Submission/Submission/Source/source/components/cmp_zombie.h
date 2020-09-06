#pragma once

#include "ecm.h"

class ZombieComponent : public Component
{
protected:
	float _health;
	bool _del;
public:
	void update(double dt)override;
	void render()override;
	ZombieComponent() = delete;
	ZombieComponent(Entity* p, float health = 1.f, bool del = false);
	bool Remove(bool rem);
};