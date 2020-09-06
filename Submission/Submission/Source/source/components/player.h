#pragma once
#include <ecm.h>

class PlayerComponent : public Component
{
protected:
	int _health;
	bool _isHit;
	float _TimeSinceHit;
	bool _isDead;
public:
	void update(double dt)override;
	PlayerComponent() = delete;
	void render()override;
	explicit PlayerComponent(Entity* p, int health = 5, bool isHit = false, float TimeSinceHit = 0.f, bool isDead = false);
	void isHit();
	bool& death();
};