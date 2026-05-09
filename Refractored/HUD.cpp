#include "HUD.h"
#include "Constants.h"

HUD::HUD()
    : hasFont(false),
      scoreText(font),
      highscoreText(font)
{
    hasFont = font.openFromFile("PressStart2P-Regular.ttf");

    if (hasFont)
    {
        scoreText.setCharacterSize(24);
        scoreText.setFillColor(sf::Color::Cyan);

        highscoreText.setCharacterSize(24);
        highscoreText.setFillColor(sf::Color::White);
        highscoreText.setPosition({20.f, 20.f});
    }

    hudBar.setSize({WINDOW_WIDTH, HUD_HEIGHT});
    hudBar.setFillColor(sf::Color(0, 0, 0, 180));
    hudBar.setPosition({0.f, 0.f});
}

void HUD::updatePlaying(int score, int highscore)
{
    if (!hasFont)
        return;

    scoreText.setFillColor(sf::Color::Cyan);
    scoreText.setString("Score: " + std::to_string(score));
    sf::FloatRect r = scoreText.getLocalBounds();
    scoreText.setOrigin({0.f, 0.f});
    scoreText.setPosition({WINDOW_WIDTH - r.size.x - 20.f, 20.f});

    highscoreText.setString("Best: " + std::to_string(highscore));
    highscoreText.setPosition({20.f, 20.f});
}

void HUD::updateGameOver(int score)
{
    if (!hasFont)
        return;

    scoreText.setFillColor(sf::Color::White);
    scoreText.setString("GAME OVER!\nScore: " + std::to_string(score) +
                        "\nPress R to Restart.");
    sf::FloatRect r = scoreText.getLocalBounds();
    scoreText.setOrigin({r.position.x + r.size.x / 2.f,
                         r.position.y + r.size.y / 2.f});
    scoreText.setPosition({WINDOW_WIDTH / 2.f, WINDOW_HEIGHT / 2.f});
}

void HUD::draw(sf::RenderWindow &window)
{
    window.draw(hudBar);
    if (hasFont)
    {
        window.draw(scoreText);
        window.draw(highscoreText);
    }
}

void HUD::drawMenu(sf::RenderWindow &window)
{
    if (!hasFont)
        return;
    sf::Text title(font);
    title.setCharacterSize(48);
    title.setFillColor(sf::Color::Green);
    title.setString("BALLZ");
    sf::FloatRect r = title.getLocalBounds();
    title.setOrigin({r.position.x + r.size.x / 2.f, r.position.y + r.size.y / 2.f});
    title.setPosition({WINDOW_WIDTH / 2.f, 200.f});
    window.draw(title);

    sf::Text opts(font);
    opts.setCharacterSize(48);
    opts.setFillColor(sf::Color::White);
    opts.setString("EASY : PRESS 1 \n\n MEDIUM : PRESS 2\n\nHARD : PRESS 3");
    r = opts.getLocalBounds();
    opts.setOrigin({r.position.x + r.size.x / 2.f, r.position.y + r.size.y / 2.f});
    opts.setPosition({WINDOW_WIDTH / 2.f, 380.f});
    window.draw(opts);
}