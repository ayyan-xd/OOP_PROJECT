#pragma once
#include "Entity.h"

class Player : public Entity
{
    float speed;

public:
    explicit Player(float radius);
    void update(const sf::Vector2f &targetPos) override;
    void setSpeed(float s);
    void grow(float amount);
    void reset();
};