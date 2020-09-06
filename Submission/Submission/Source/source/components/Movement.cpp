#include "Movement.h"
#include "LevelSystem.h"
#include "engine.h"
#include <iostream>

using namespace sf;
using namespace std;

void MovementComponent::update(double dt)
{
	float horizontal = 0.0f;
	float vertical = 0.0f;
	if (Keyboard::isKeyPressed(Keyboard::Up))
		vertical--;
	if (Keyboard::isKeyPressed(Keyboard::Down))
		vertical++;
	if (Keyboard::isKeyPressed(Keyboard::Left))
		horizontal--;
	if (Keyboard::isKeyPressed(Keyboard::Right))
		horizontal++;
	move(horizontal, vertical);
}

void MovementComponent::render()
{

}

MovementComponent::MovementComponent(Entity* p) : _speed(100.0f), Component(p) {}
/*
bool MovementComponent::validMove(const sf::Vector2f& pos)
{
	return (LevelSystem::getTileAt(pos) != LevelSystem::WALL);
}
*/

void MovementComponent::move(const sf::Vector2f& p)
{
	auto pp = _parent->getPosition() + p;
	_parent->setPosition(pp);
}

void MovementComponent::move(float x, float y)
{
	move(Vector2f(x, y));
}