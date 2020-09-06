#include "cmp_bullet.h"
#include "system_renderer.h"

using namespace std;

void BulletComponent::update(double dt)
{
	_lifetime -= dt;
	if (_lifetime <= 0.f)
		_parent->setForDelete();
}

void BulletComponent::render()
{

}

BulletComponent::BulletComponent(Entity* p, float lifetime) : Component(p), _lifetime(lifetime){}

