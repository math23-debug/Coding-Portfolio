#include <SFML/Graphics.hpp>
#include <cmath>
#include <string>
#include <cstdlib>
#include <cctype>
#include <limits>
#include <vector>
#include <random>
#include <iostream>

sf::Vector2f getRandomDot(sf::RenderWindow& Window, float radius)
{
    sf::Vector2u winSize = Window.getSize();
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_real_distribution<float> distX(0.f, winSize.x - radius*2);
    std::uniform_real_distribution<float> distY(0.f, winSize.y - radius*2);
    return sf::Vector2f(distX(gen), distY(gen));
}

int main()
{
    sf::RenderWindow window(sf::VideoMode({ 800, 600 }), "Collect the dot", sf::Style::Titlebar | sf::Style::Close);

    sf::Clock clock;
    sf::Clock gameTime;

    sf::Texture golem;
    sf::Font font;

    float speedConst = 1, speed = 350;

    int score = 0, timeLimit = 30, highScore = 0;
    int timeLeft = timeLimit;
    int flash;

    bool start = false, gameOver = false, restart = false;

    if (!golem.loadFromFile("stone-golem.png"))
    {
        std::cout << "Failed to load golem texture\n";
    }
    if (!font.openFromFile("Pokra.otf"))
    {
        std::cout << "Failed to load Pokra font\n";
    }

    sf::Text scoreText(font, "Score: 0", 24);
    scoreText.setFillColor(sf::Color::White);
    scoreText.setPosition({ 10.f, 10.f });

    sf::Text highScoreText(font, "High score: 0", 24);
    highScoreText.setFillColor(sf::Color::White);
    highScoreText.setPosition({ 10.f, 40.f });

    sf::Text clockText(font, "Time left: " + std::to_string(timeLimit), 24);
    clockText.setFillColor(sf::Color::White);
    clockText.setPosition({ 652.f, 10.f });

    sf::Text gameOverText(font, "GAME OVER", 50);
    gameOverText.setFillColor(sf::Color::Red);
    gameOverText.setPosition({ 240.f, 250.f });

    sf::Text finalScoreText(font, "Final Score:", 34);
    finalScoreText.setFillColor(sf::Color::Green);
    finalScoreText.setPosition({ 307.f, 315.f });

    sf::Text finalHighScoreText(font, "High score:", 24);
    finalHighScoreText.setFillColor(sf::Color::Green);
    finalHighScoreText.setPosition({ 320.f, 355.f });

    sf::Text restartText(font, "Press Enter to Restart", 24);
    restartText.setFillColor(sf::Color::Yellow);
    restartText.setPosition({ 297.f, 570 });


    sf::Sprite stoneGolem(golem);
    stoneGolem.setPosition({ 100.f, 100.f });
    stoneGolem.setScale({ 3.f, 3.f });

    sf::CircleShape dot(8.f);
    dot.setPosition(getRandomDot(window, 8.f));
    dot.setFillColor(sf::Color::Blue);


    while (window.isOpen())
    {

        while (const std::optional event = window.pollEvent())
        {
            if (event->is<sf::Event::Closed>())
                window.close();
        }

        sf::Vector2u winSize = window.getSize();
        sf::Vector2f golemPos = stoneGolem.getPosition();
        sf::FloatRect golemBounds = stoneGolem.getGlobalBounds();

        if (!restart)
        {
            if (!gameOver)
            {

                if (stoneGolem.getGlobalBounds().findIntersection(dot.getGlobalBounds()))
                {
                    dot.setPosition(getRandomDot(window, 8.f));
                    score += 1;
                    scoreText.setString("Score: " + std::to_string(score));
                }

                float deltaTime = clock.restart().asSeconds();

                if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::S) && sf::Keyboard::isKeyPressed(sf::Keyboard::Key::A)) speedConst = std::sqrt(2);
                if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::S) && sf::Keyboard::isKeyPressed(sf::Keyboard::Key::D)) speedConst = std::sqrt(2);
                if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::W) && sf::Keyboard::isKeyPressed(sf::Keyboard::Key::A)) speedConst = std::sqrt(2);
                if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::W) && sf::Keyboard::isKeyPressed(sf::Keyboard::Key::D)) speedConst = std::sqrt(2);

                if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::D))
                {
                    stoneGolem.move({ speed * deltaTime / speedConst, 0.f });
                    start = true;
                }
                if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::A))
                {
                    stoneGolem.move({ -1 * speed * deltaTime / speedConst, 0.f });
                    start = true;
                }
                if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::W))
                {
                    stoneGolem.move({ 0.f, -1 * speed * deltaTime / speedConst });
                    start = true;
                }
                if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::S))
                {
                    stoneGolem.move({ 0.f, speed * deltaTime / speedConst });
                    start = true;
                }

                if (golemPos.x < 0) stoneGolem.setPosition({ 0, golemPos.y });
                if (golemPos.x + golemBounds.size.x > winSize.x) stoneGolem.setPosition({ winSize.x - golemBounds.size.x, golemPos.y });
                if (golemPos.y < 0) stoneGolem.setPosition({ golemPos.x, 0 });
                if (golemPos.y + golemBounds.size.y > winSize.y) stoneGolem.setPosition({ golemPos.x, winSize.y - golemBounds.size.y });

                speedConst = 1;

                if (start) timeLeft = timeLimit + 1 - gameTime.getElapsedTime().asSeconds();
                else gameTime.restart();

                clockText.setString("Time Left: " + std::to_string(timeLeft));

                flash = gameTime.getElapsedTime().asSeconds() * 2;

                if (timeLeft <= 5)
                {
                    if (flash % 2)
                    {
                        clockText.setFillColor(sf::Color::Red);
                    }
                    else
                    {
                        clockText.setFillColor(sf::Color::White);
                    }
                }

                if (timeLeft < 1)
                {
                    gameOver = true;
                    finalScoreText.setString("Final score: " + std::to_string(score));
                    restart = true;
                    if (score > highScore) highScore = score;
                    finalHighScoreText.setString("High score: " + std::to_string(highScore));
                    highScoreText.setString("High score: " + std::to_string(highScore));
                }
            }
        }
        else
        {
            if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Enter))
            {
                restart = false;
                start = false;
                gameOver = false;
                dot.setPosition(getRandomDot(window, 8.f));
                stoneGolem.setPosition({ 100.f, 100.f });
                timeLeft = timeLimit;
                score = 0;
            }
        }

        window.clear();
        window.draw(dot);
        window.draw(stoneGolem);
        window.draw(scoreText);
        window.draw(highScoreText);
        window.draw(clockText);
        if (gameOver)
        {
            window.draw(gameOverText);
            window.draw(finalScoreText);
            window.draw(finalHighScoreText);
        }
        if (restart) window.draw(restartText);
        window.display();
    }
}


