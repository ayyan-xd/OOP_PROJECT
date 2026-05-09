#pragma once
#include <SFML/Graphics.hpp>
#include <string>

class HUD
{
    sf::Font font;
    bool hasFont;
    sf::Text scoreText;
    sf::Text highscoreText;
    sf::RectangleShape hudBar;

public:
    HUD();
    void updatePlaying(int score, int highscore);
    void updateGameOver(int score);
    void draw(sf::RenderWindow &window);
    bool loaded() const { return hasFont; }
    void drawMenu(sf::RenderWindow &window);
};