#include "Game.h"
#include "Constants.h"
#include <cmath>
#include <cstdlib>
#include <algorithm>

Game::Game()
    : window(sf::VideoMode({static_cast<unsigned>(WINDOW_WIDTH),
                            static_cast<unsigned>(WINDOW_HEIGHT)}),
             "Pulse"),
      state(gameState::MENU),
      globalSpeed(GLOBAL_START_SPEED),
      score(0),
      highscore(0),
      player(PLAYER_RADIUS),
      scorePoint(randomPos())
{
    window.setFramerateLimit(60);
    player.set_Position({WINDOW_WIDTH / 2.f, WINDOW_HEIGHT / 2.f});
}

void Game::run()
{
    while (window.isOpen())
    {
        handleEvents();
        update();
        draw();
    }
}

bool Game::collides(Entity &a, Entity &b)
{
    sf::Vector2f diff = a.get_Position() - b.get_Position();
    float dist = std::sqrt(diff.x * diff.x + diff.y * diff.y);
    return dist <= static_cast<float>(a.getRadius() + b.getRadius());
}

sf::Vector2f Game::randomPos()
{
    // Extra padding = scorepoint radius + 5px buffer so it never
    // visually clips into the HUD bar even at the boundary
    float margin = HUD_HEIGHT + SCOREPOINT_RADIUS + 5.f;
    float x = static_cast<float>(std::rand() % static_cast<int>(WINDOW_WIDTH));
    float y = margin + static_cast<float>(
                           std::rand() % static_cast<int>(WINDOW_HEIGHT - margin));
    return {x, y};
}

sf::Vector2f Game::randomPosFarFrom(sf::Vector2f target, float minDist)
{
    sf::Vector2f pos;
    do
    {
        pos = randomPos();
        sf::Vector2f diff = pos - target;
        float dist = std::sqrt(diff.x * diff.x + diff.y * diff.y);
        if (dist >= minDist)
            break;
    } while (true);
    return pos;
}

void Game::reset()
{
    player.set_Position({WINDOW_WIDTH / 2.f, WINDOW_HEIGHT / 2.f});
    player.reset();
    enemies.clear();
    state = gameState::PLAYING;
    globalSpeed = GLOBAL_START_SPEED;
    score = 0;
}

void Game::handleEvents()
{
    while (std::optional event = window.pollEvent())
    {
        if (event->is<sf::Event::Closed>())
            window.close();

        if (const auto *kp = event->getIf<sf::Event::KeyPressed>())
        {
            if (state == gameState::MENU)
            {
                if (kp->code == sf::Keyboard::Key::Num1)
                    applyDifficulty(EASY_SPEED);
                if (kp->code == sf::Keyboard::Key::Num2)
                    applyDifficulty(MEDIUM_SPEED);
                if (kp->code == sf::Keyboard::Key::Num3)
                    applyDifficulty(HARD_SPEED);
            }
            else if (state == gameState::GAMEOVER)
            {
                if (kp->code == sf::Keyboard::Key::R)
                    state = gameState::MENU;
            }
        }
    }
}

void Game::update()
{
    if (state != gameState::PLAYING)
        return;

    player.update({});

    // ScorePoint pickup
    if (collides(player, scorePoint))
    {
        score += SCORE_PICKUP;
        globalSpeed += SPEED_INCREMENT;
        player.setSpeed(globalSpeed);
        player.grow(PLAYER_GROW_AMOUNT);
        enemies.push_back(Enemy(randomPosFarFrom(player.get_Position(), 200.f), globalSpeed * ENEMY_SPEED_RATIO));
        scorePoint.set_Position(randomPos());
        if (score > highscore)
            highscore = score;
    }

    // Enemy updates + collisions
    for (int i = 0; i < static_cast<int>(enemies.size()); i++)
    {
        enemies[i].update(player.get_Position());

        if (collides(player, enemies[i]))
        {
            state = gameState::GAMEOVER;
            if (score > highscore)
                highscore = score;
            return;
        }

        for (int j = i + 1; j < static_cast<int>(enemies.size()); j++)
        {
            if (enemies[i].isDead || enemies[j].isDead)
                continue;
            if (collides(enemies[i], enemies[j]))
            {
                enemies[i].isDead = true;
                enemies[j].isDead = true;
                score += SCORE_ENEMY_COLLISION;
            }
        }
    }

    enemies.erase(
        std::remove_if(enemies.begin(), enemies.end(),
                       [](const Enemy &e)
                       { return e.isDead; }),
        enemies.end());

    hud.updatePlaying(score, highscore);
}

void Game::draw()
{
    window.clear(sf::Color::Black);

    if (state == gameState::MENU)
    {
        hud.drawMenu(window);
        window.display();
    }
    else if (state == gameState::PLAYING)
    {
        player.draw(window);
        scorePoint.draw(window);
        for (Enemy &e : enemies)
            e.draw(window);
        hud.draw(window);
        window.display();
    }

    else if (state == gameState::GAMEOVER)
    {
        hud.updateGameOver(score);
        hud.draw(window);
        window.display();
    }
}
void Game::applyDifficulty(float startSpeed)
{
    globalSpeed = startSpeed;
    player.reset();
    player.set_Position({WINDOW_WIDTH / 2.f, WINDOW_HEIGHT / 2.f});
    player.setSpeed(globalSpeed);
    enemies.clear();
    score = 0;
    scorePoint.set_Position(randomPos());
    state = gameState::PLAYING;
}
