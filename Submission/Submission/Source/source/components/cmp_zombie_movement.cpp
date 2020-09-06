#include "cmp_zombie_movement.h"
#include "engine.h"
#include <iostream>


void ZombieMovement::update(double dt)
{

}

void ZombieMovement::render()
{

}

void ZombieMovement::MoveValidate(std::shared_ptr<Entity> play)
{
	
}

ZombieMovement::ZombieMovement(Entity* p, float speed) : Component(p), _speed(speed) {}

void ZombieMovement::move(const sf::Vector2f& p)
{
	auto pp = _parent->getPosition() + p;
	_parent->setPosition(pp);
}

void ZombieMovement::move(float x, float y)
{
	move(sf::Vector2f(x, y));
}
