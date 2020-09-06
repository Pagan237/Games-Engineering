#pragma once

#include <ecm.h>

class BulletMovement : public Component
{
protected:
	bool _fired;
	bool _isDirectionSet;
	float _speed;
	int _direction;
	float _horizontal;
	float _vertical;
public:
	void update(double dt)override;
	void render()override;
	void move(float x, float y);
	void move(sf::Vector2f);
	explicit BulletMovement(Entity* p, bool fired = false);
	BulletMovement() = delete;
	//int setDirection(int dir);
};