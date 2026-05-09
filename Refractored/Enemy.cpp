#include "Enemy.h"
#include "Constants.h"
#include <cmath>

Enemy::Enemy(sf::Vector2f spawnPos, float spd)
    : Entity(ENEMY_RADIUS, sf::Color::Red), speed(spd)
{
    set_Position(spawnPos);
}

void Enemy::update(const sf::Vector2f &playerPos)
{
    sf::Vector2f pos       = get_Position();
    sf::Vector2f direction = playerPos - pos;
    float distance = std::sqrt(direction.x * direction.x + direction.y * direction.y);

    if (distance > 5.f)
    {
        pos += (direction / distance) * speed;
        set_Position(pos);
    }
}