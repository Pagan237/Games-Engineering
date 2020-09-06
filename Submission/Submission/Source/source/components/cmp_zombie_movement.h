#pragma once

#include "ecm.h"

class ZombieMovement : public Component
{
protected:
	float _speed;
public:
	ZombieMovement() = delete;
	
	void update(double dt)override;
	void render()override;
	void move(float x, float y);
	void move(const sf::Vector2f&);
	explicit ZombieMovement(Entity* p, float speed = 2.f);
	void MoveValidate(std::shared_ptr<Entity> play);

};