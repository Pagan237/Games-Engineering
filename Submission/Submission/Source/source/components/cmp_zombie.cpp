#include "cmp_zombie.h"
#include "../game.h"
#include "system_renderer.h"

void ZombieComponent::update(double dt)
{

}

void ZombieComponent::render()
{

}

ZombieComponent::ZombieComponent(Entity* p, float health, bool del) : Component(p), _health(health), _del(del) {}

bool ZombieComponent::Remove(bool rem)
{
	rem = true;
	return rem;
}