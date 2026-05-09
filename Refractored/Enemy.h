#pragma once
#include "Entity.h"

class Enemy : public Entity
{
    float speed;

public:
    Enemy(sf::Vector2f spawnPos, float speed);
    void update(const sf::Vector2f &playerPos) override;
};