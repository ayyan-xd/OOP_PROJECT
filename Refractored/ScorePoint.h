#pragma once
#include "Entity.h"

class ScorePoint : public Entity
{
public:
    explicit ScorePoint(sf::Vector2f spawnPos);
    void update(const sf::Vector2f &) override {}
};