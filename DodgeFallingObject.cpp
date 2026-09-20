#include <SFML/Graphics.hpp>
#include <cmath>
#include <string>
#include <cstdlib>
#include <cctype>
#include <limits>
#include <vector>
#include <random>
#include <iostream>

float randPosition(sf::RenderWindow& window, float radius)
{
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_real_distribution<float> distX(0.f, window.getSize().x - radius * 2);
    return distX(gen);
}

int main()
{
    sf::RenderWindow window(sf::VideoMode({ 600, 800 }), "My First Window", sf::Style::Titlebar | sf::Style::Close);

    sf::Clock clock, spawnClock;

    float ballSpeed = 400, spawnInterval = 0.5, margin = 15.f;

    bool gameOver = false, start = false;

    std::vector<sf::CircleShape> obstacles;

    sf::Texture Spider;

    if (!Spider.loadFromFile("cave-spider.png"))
    {
        std::cout << "Failed to load golem texture\n";
    }

    sf::Font font;

    if (!font.openFromFile("Requiner-6RRLM.otf"))
    {
        std::cout << "Failed to load Requiner font\n";
    }

    sf::Text gameOverText(font, "GAME OVER", 80.f);
    gameOverText.setFillColor(sf::Color::Red);
    gameOverText.setPosition({ 300 - gameOverText.getGlobalBounds().size.x / 2, 400 - gameOverText.getGlobalBounds().size.y / 2 });

    sf::Sprite spider(Spider);
    spider.setScale({ 3.f, 3.f });
    sf::FloatRect spiderBounds = spider.getGlobalBounds();
    spider.setPosition({ 300 - spiderBounds.size.x / 2, 800 - 15 - spiderBounds.size.y});
    sf::FloatRect tightBounds;
    tightBounds.size = { spiderBounds.size.x - margin * 2, spiderBounds.size.y - margin * 2 };

    while (window.isOpen())
    {
        while (const std::optional event = window.pollEvent())
        {
            if (event->is<sf::Event::Closed>())
                window.close();
        }

        if (!start)
        {
            gameOver = false;
            if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Right) ||
                sf::Keyboard::isKeyPressed(sf::Keyboard::Key::D) ||
                sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Left) ||
                sf::Keyboard::isKeyPressed(sf::Keyboard::Key::A))
            {
                start = true;
                clock.restart();
            }
        }
        else
        {
            if (!gameOver)
            {
                if (spawnClock.getElapsedTime().asSeconds() > spawnInterval)
                {
                    sf::CircleShape obstacle(40.f);
                    obstacle.setPosition({ randPosition(window, 40.f), -40.f });
                    obstacle.setFillColor(sf::Color::Blue);
                    obstacles.push_back(obstacle);
                    spawnClock.restart();
                }

                float deltaTime = clock.restart().asSeconds();

                if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Right) || sf::Keyboard::isKeyPressed(sf::Keyboard::Key::D)) spider.move({ 400.f * deltaTime, 0.f });
                if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Left) || sf::Keyboard::isKeyPressed(sf::Keyboard::Key::A)) spider.move({ -400.f * deltaTime, 0.f });
                if (spider.getPosition().x < 0) spider.setPosition({ 0.f, spider.getPosition().y });
                if (spider.getPosition().x + spiderBounds.size.x > window.getSize().x) spider.setPosition({ window.getSize().x - spiderBounds.size.x, spider.getPosition().y });

                for (int i = 0; i < obstacles.size(); i++)
                {
                    obstacles[i].move({ 0.f, ballSpeed * deltaTime });
                }

                for (int i = 0; i < obstacles.size(); i++)
                {
                    if (obstacles[i].getPosition().y > window.getSize().y)
                    {
                        obstacles.erase(obstacles.begin() + i);
                        i--;
                    }
                }


                for (int i = 0; i < obstacles.size(); i++)
                {
                    sf::FloatRect currentSpiderBounds = spider.getGlobalBounds();
                    tightBounds.position = { currentSpiderBounds.position.x + margin, currentSpiderBounds.position.y + margin };
                    if (obstacles[i].getGlobalBounds().findIntersection(tightBounds))
                    {
                        gameOver = true;
                    }
                }
            }
            else
            {
                if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Enter))
                {
                    spider.setPosition({ 300 - spiderBounds.size.x / 2, 800 - 15 - spiderBounds.size.y });
                    obstacles.clear();
                    start = false;
                    clock.restart();
                }
            }
        }

        window.clear();
        window.draw(spider);
        for (int i = 0; i < obstacles.size(); i++)
        {
            window.draw(obstacles[i]);
        }
        if (gameOver) window.draw(gameOverText);
        window.display();
    }
}
