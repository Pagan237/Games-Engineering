#include "cmp_bullet_movement.h"
#include "LevelSystem.h"
#include "engine.h"
#include <iostream>

using namespace sf;
using namespace std;

void BulletMovement::update(double dt)
{
	float horizontal = 0.0f;
	if (Keyboard::isKeyPressed(Keyboard::S))
		_fired = true;
	if (_fired)
	{
		horizontal++;
		move(horizontal * _speed, 0);
	}

}

void BulletMovement::render()
{
	 
}

BulletMovement::BulletMovement(Entity* p, bool fired) : Component(p), _isDirectionSet(false), _speed(2.f), _direction(5), _horizontal(0.f), _vertical(0.f), _fired(fired) {}

void BulletMovement::move(sf::Vector2f p)
{
	auto pp = _parent->getPosition() + p;
	_parent->setPosition(pp);
}

void BulletMovement::move(float x, float y)
{
	move(Vector2f(x, y));
}
