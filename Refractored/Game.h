#pragma once
#include <SFML/Graphics.hpp>
#include <vector>
#include "Player.h"
#include "Enemy.h"
#include "ScorePoint.h"
#include "HUD.h"

enum class gameState
{
    MENU,
    PLAYING,
    GAMEOVER
};
class Game
{
    sf::RenderWindow window;
    gameState state;
    float globalSpeed;
    int score;
    int highscore;

    Player player;
    std::vector<Enemy> enemies;
    ScorePoint scorePoint;
    HUD hud;

    bool collides(Entity &a, Entity &b);
    sf::Vector2f randomPos();
    sf::Vector2f randomPosFarFrom(sf::Vector2f target, float minDist);
    void reset();

    void handleEvents();
    void update();
    void draw();
    void applyDifficulty(float startSpeed);

public:
    Game();
    void run();
};