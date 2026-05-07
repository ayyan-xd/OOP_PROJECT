#include <iostream>
#include <SFML/Graphics.hpp>
#include <vector>
#include <cmath>
#include <ctime>
#include <algorithm>
using namespace std;

class Entity
{
protected:
    sf::CircleShape shape;

public:
    Entity(float radius, sf::Color color)
    {
        shape.setRadius(radius);
        shape.setOrigin({radius, radius});
        shape.setFillColor(color);
    }

    virtual void update(const sf::Vector2f &PlayerPos) = 0;
    bool isDead = false;
    double getRadius() const
    {
        return shape.getRadius();
    }
    sf::Vector2f get_Position()
    {
        return shape.getPosition();
    }
    void set_Position(const sf::Vector2f &pos)
    {
        shape.setPosition(pos);
    }
    void draw(sf::RenderWindow &window)
    {
        window.draw(shape);
    }
};

class Player : public Entity
{
    float speed;

public:
    Player(float r) : Entity(r, sf::Color::Blue), speed(5.5f) {}

    void update(const sf::Vector2f &PlayerPos) override
    {
        sf::Vector2f movement;
        sf::Vector2f pos = this->get_Position();
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::W))
            movement.y -= speed;
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::S))
            movement.y += speed;
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::A))
            movement.x -= speed;
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::D))
            movement.x += speed;
        pos += movement;
        this->set_Position(pos);

        float r = this->getRadius();
        if (pos.x < r)
            pos.x = r;
        if (pos.x > 1280.f - r)
            pos.x = 1280.f - r;
        if (pos.y < r)
            pos.y = r;
        if (pos.y > 720.f - r)
            pos.y = 720.f - r;
        this->set_Position(pos);
    }

    void setSpeed(float s)
    {
        speed = s;
    }

    void grow(float amount)
    {
        float newRadius = this->getRadius() + amount;
        if (newRadius > 25.f)
            newRadius = 25.f;
        float r = newRadius;
        shape.setRadius(r);
        shape.setOrigin({r, r});
    }
};

class Enemy : public Entity
{
    float speed;

public:
    Enemy(sf::Vector2f pos, float s) : Entity(8.f, sf::Color::Red), speed(s)
    {
        this->set_Position(pos);
    }

    void update(const sf::Vector2f &playerPos) override
    {
        sf::Vector2f pos = this->get_Position();
        sf::Vector2f direction = playerPos - pos;
        float distance = sqrt(direction.x * direction.x + direction.y * direction.y);
        if (distance > 5.f)
        {
            pos += (direction / distance) * speed;
            this->set_Position(pos);
        }
    }
};

class ScorePoint : public Entity
{
public:
    ScorePoint(sf::Vector2f pos) : Entity(5.f, sf::Color::Yellow)
    {
        this->set_Position(pos);
    }
    void update(const sf::Vector2f &p) override
    {
        // No movement for score point
    }
};

sf::Vector2f gen()
{
    sf::Vector2f index;
    index.x = rand() % 1280;
    index.y = rand() % 720;

    return index;
}

int main()
{
    srand(time(0));

    sf::RenderWindow window(sf::VideoMode({1280, 720}), "Pulse");
    window.setFramerateLimit(60);

    bool GameOver = false;
    float GlobalSpeed = 5.5f;

    Player player(10.f);
    player.set_Position({640.f, 360.f});
    std::vector<Enemy> enemies;

    ScorePoint scoreP(gen());

    // Font Set-up
    sf::Font font;
    bool hasfont = font.openFromFile("PressStart2P-Regular.ttf");
    sf::Text text(font);
    sf::Text highscoreText(font);

    if (hasfont)
    {
        text.setCharacterSize(30);
        text.setFillColor(sf::Color::White);
        highscoreText.setCharacterSize(30);
        highscoreText.setFillColor(sf::Color::White);
    }

    int score = 0;
    int highscore = 0;
    while (window.isOpen())
    {

        while (optional event = window.pollEvent())
        {
            if (event->is<sf::Event::Closed>())
            {
                window.close();
            }

            if (GameOver && sf::Keyboard::isKeyPressed(sf::Keyboard::Key::R))
            {
                player.set_Position({640.f, 360.f});
                enemies.clear();
                GameOver = false;
                GlobalSpeed = 5.5f;
                score = 0;
            }
        }

        if (!GameOver)
        {
            player.update({0.f, 0.f});

            // Score Points
            sf::Vector2f DisPS = player.get_Position() - scoreP.get_Position();
            if (sqrt(DisPS.x * DisPS.x + DisPS.y * DisPS.y) <= player.getRadius() + scoreP.getRadius())
            {
                score += 10;
                GlobalSpeed += 0.3f;
                player.setSpeed(GlobalSpeed);
                enemies.push_back(Enemy(gen(), GlobalSpeed * 0.6f));
                scoreP.set_Position(gen());
                player.grow(1.5);
            }

            // Enemies
            for (int i = 0; i < enemies.size(); i++)
            {
                enemies[i].update(player.get_Position());

                // collision with player
                sf::Vector2f DisPS = player.get_Position() - enemies[i].get_Position();
                if (sqrt(DisPS.x * DisPS.x + DisPS.y * DisPS.y) <= player.getRadius() + enemies[i].getRadius())
                {
                    GameOver = true;
                }

                // collision of enemies with one another
                for (int j = i + 1; j < enemies.size(); j++)
                {
                    if (enemies[i].isDead == true || enemies[j].isDead == true)
                        continue;

                    sf::Vector2f DisPS = enemies[i].get_Position() - enemies[j].get_Position();
                    if (sqrt(DisPS.x * DisPS.x + DisPS.y * DisPS.y) <= enemies[j].getRadius() + enemies[i].getRadius())
                    {
                        enemies[i].isDead = true;
                        enemies[j].isDead = true;
                        score += 5;
                    }
                }
            }

            enemies.erase(remove_if(enemies.begin(), enemies.end(), [](Enemy e)
                                    { return e.isDead == true; }),
                          enemies.end());
            if (hasfont)
            {
                text.setString("Score: " + std::to_string(score));
                text.setFillColor(sf::Color::Cyan);
                sf::FloatRect textRect = text.getLocalBounds();
                text.setOrigin({textRect.position.x + textRect.size.x / 2.0f,
                                textRect.position.x + textRect.size.y / 2.0f});
                text.setPosition({1280.f / 2.0f, 40.f});
                if (score > highscore)
                    highscore = score;
                highscoreText.setString("High Score: " + std::to_string(highscore));
                highscoreText.setPosition({20.f, 20.f});
            }
        }
        else
        {
            if (hasfont)
            {
                text.setString("GAME OVER!\nScore: " + std::to_string(score) + "\nPress R to Restart.");
                sf::FloatRect textRect = text.getLocalBounds();
                text.setOrigin({textRect.position.x + textRect.size.x / 2.0f,
                                textRect.position.y + textRect.size.y / 2.0f});
                text.setPosition({1280.f / 2.0f, 720.f / 2.0f});
            }
        }

        window.clear(sf::Color::Black);
        if (!GameOver)
        {

            player.draw(window);
            scoreP.draw(window);
            for (Enemy x : enemies)
            {
                x.draw(window);
            }
        }

        if (hasfont)
        {
            window.draw(text);
            window.draw(highscoreText);
        }
        window.display();
    }

    return 0;
}