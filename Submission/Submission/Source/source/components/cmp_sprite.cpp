#include "cmp_sprite.h"
#include "system_renderer.h"

using namespace std;

void ShapeComponent::update(double dt)
{
	_shape->setPosition(_parent->getPosition());
	_shape->setRotation(_parent->getRotation());
}

void ShapeComponent::render()
{
	Renderer::queue(_shape.get());
}

void ShapeComponent::unload()
{
	_parent->setForDelete();
}

sf::Shape& ShapeComponent::getShape() const { return *_shape; }

ShapeComponent::ShapeComponent(Entity* p) : Component(p), _shape(make_shared<sf::CircleShape>()) {}
