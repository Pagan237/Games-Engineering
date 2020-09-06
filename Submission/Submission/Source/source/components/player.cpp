#include "player.h"

void PlayerComponent::update(double dt)
{
	if (_TimeSinceHit >= 5.f)
		_health = 5;
	if (_health == 0)
	{
		_parent->setForDelete();
		_isDead = true;
	}
	_TimeSinceHit += dt;
}

void PlayerComponent::render()
{

}

PlayerComponent::PlayerComponent(Entity* p, int health, bool isHit, float TimeSinceHit, bool isDead) : Component(p), _health(health), _isHit(isHit), _TimeSinceHit(TimeSinceHit), _isDead(isDead){}

void PlayerComponent::isHit()
{
	_health = _health - 1;
	_TimeSinceHit = 0;
}

bool& PlayerComponent::death()
{
	return _isDead;
}
