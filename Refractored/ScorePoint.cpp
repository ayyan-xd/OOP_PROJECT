#include "ScorePoint.h"
#include "Constants.h"

ScorePoint::ScorePoint(sf::Vector2f spawnPos)
    : Entity(SCOREPOINT_RADIUS, sf::Color::Yellow)
{
    set_Position(spawnPos);
}