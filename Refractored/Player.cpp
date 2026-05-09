#include "Player.h"
#include "Constants.h"

Player::Player(float radius)
    : Entity(radius, sf::Color::Blue), speed(PLAYER_START_SPEED) {}

void Player::update(const sf::Vector2f & /*targetPos*/)
{
    sf::Vector2f movement;
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::W))
        movement.y -= speed;
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::S))
        movement.y += speed;
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::A))
        movement.x -= speed;
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::D))
        movement.x += speed;

    sf::Vector2f pos = get_Position() + movement;

    float r = static_cast<float>(getRadius());
    if (pos.x < r)
        pos.x = r;
    if (pos.x > WINDOW_WIDTH - r)
        pos.x = WINDOW_WIDTH - r;
    if (pos.y < r + HUD_HEIGHT)
        pos.y = r + HUD_HEIGHT;
    if (pos.y > WINDOW_HEIGHT - r)
        pos.y = WINDOW_HEIGHT - r;

    set_Position(pos);
}

void Player::setSpeed(float s)
{
    speed = s;
}

void Player::grow(float amount)
{
    float newRadius = static_cast<float>(getRadius()) + amount;
    if (newRadius > PLAYER_MAX_RADIUS)
        newRadius = PLAYER_MAX_RADIUS;
    shape.setRadius(newRadius);
    shape.setOrigin({newRadius, newRadius});
}

void Player::reset()
{
    shape.setRadius(PLAYER_RADIUS);
    shape.setOrigin({PLAYER_RADIUS, PLAYER_RADIUS});
    speed = PLAYER_START_SPEED;
}