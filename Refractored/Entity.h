#pragma once
#include <SFML/Graphics.hpp>

class Entity
{
protected:
    sf::CircleShape shape;

public:
    Entity(float radius, sf::Color color);
    virtual void update(const sf::Vector2f &targetPos) = 0;
    virtual ~Entity() = default;

    bool isDead = false;

    double getRadius() const;
    sf::Vector2f get_Position();
    void set_Position(const sf::Vector2f &pos);
    void draw(sf::RenderWindow &window);
};