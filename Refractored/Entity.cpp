#include "Entity.h"

Entity::Entity(float radius, sf::Color color)
{
    shape.setRadius(radius);
    shape.setOrigin({radius, radius});
    shape.setFillColor(color);
}

double Entity::getRadius() const
{
    return shape.getRadius();
}

sf::Vector2f Entity::get_Position()
{
    return shape.getPosition();
}

void Entity::set_Position(const sf::Vector2f &pos)
{
    shape.setPosition(pos);
}

void Entity::draw(sf::RenderWindow &window)
{
    window.draw(shape);
}