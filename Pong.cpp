#include <SFML/Graphics.hpp>
#include <cmath>
#include <string>
#include <cstdlib>
#include <cctype>
#include <limits>
#include <vector>
#include <random>
#include <iostream>

sf::Vector2f getRandomDot(float minX, float maxX)
{
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_real_distribution<float> distX(minX, maxX);
    std::uniform_real_distribution<float> distY(100.f, 500);
    return sf::Vector2f(distX(gen), distY(gen));
}

int main()
{
    sf::RenderWindow window(sf::VideoMode({ 800, 600 }), "My First Window");

    sf::Clock clock;
    sf::Clock pause;

    float startingSpeed = 250;
    float speedX = startingSpeed, speedY = startingSpeed;

    int scoreOne = 0, scoreTwo = 0;

    bool point = true, One = false, win = false, restart = false;

    sf::CircleShape ball(14.f);
    ball.setFillColor(sf::Color::White);
    ball.setPosition(getRandomDot(100, 400));

    sf::RectangleShape playerOne({ 17.f, 130.f });
    playerOne.setFillColor(sf::Color::Blue);
    playerOne.setPosition({ 10.f, 215.f });

    sf::RectangleShape playerTwo({ 17.f, 130.f });
    playerTwo.setFillColor(sf::Color::Red);
    playerTwo.setPosition({ 773.f, 215.f });

    sf::Font font;

    if (!font.openFromFile("Requiner-6RRLM.otf"))
    {
        std::cout << "Failed to load Requiner font\n";
    }

    sf::Text scoreOneText(font, "Player One Score: 0", 18);
    scoreOneText.setFillColor(sf::Color::Blue);
    scoreOneText.setPosition({ 40, 10 });

    sf::Text scoreTwoText(font, "Player Two Score: 0", 18);
    scoreTwoText.setFillColor(sf::Color::Red);
    scoreTwoText.setPosition({ 550, 10 });

    sf::Text winText(font, "", 60);
    winText.setPosition({ 87, 270 });

    sf::Text restartText(font, "Press Enter to Restart", 24);
    restartText.setFillColor(sf::Color::Yellow);
    restartText.setPosition({ 265.f, 560 });


    while (window.isOpen())
    {

        while (const std::optional event = window.pollEvent())
        {
            if (event->is<sf::Event::Closed>())
                window.close();
        }

        float deltaTime = clock.restart().asSeconds();

        if (!win)
        {
            if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::W))
            {
                playerOne.move({ 0.f, -300 * deltaTime });
            }
            if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::S))
            {
                playerOne.move({ 0.f, 300 * deltaTime });
            }

            if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Up))
            {
                playerTwo.move({ 0.f, -300 * deltaTime });
            }
            if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Down))
            {
                playerTwo.move({ 0.f, 300 * deltaTime });
            }

            sf::Vector2u winSize = window.getSize();
            sf::Vector2f playerOnePos = playerOne.getPosition();
            sf::Vector2f playerTwoPos = playerTwo.getPosition();

            if (playerOnePos.y < 0) playerOne.setPosition({ playerOnePos.x, 0 });
            if (playerOnePos.y + playerOne.getSize().y > winSize.y) playerOne.setPosition({ playerOnePos.x, winSize.y - playerOne.getSize().y });
            if (playerTwoPos.y < 0) playerTwo.setPosition({ playerTwoPos.x, 0 });
            if (playerTwoPos.y + playerTwo.getSize().y > winSize.y) playerTwo.setPosition({ playerTwoPos.x, winSize.y - playerTwo.getSize().y });

            if (!point)
            {
                ball.move({ speedX * deltaTime, speedY * deltaTime });
                sf::Vector2f ballPos = ball.getPosition();

                if (ballPos.y < 0)
                {
                    ball.setPosition({ ballPos.x, 0 });
                    speedY *= -1;
                }
                if (ballPos.y + ball.getRadius() * 2 > winSize.y)
                {
                    ball.setPosition({ ballPos.x, winSize.y - ball.getRadius() * 2 });
                    speedY *= -1;
                }
                if (ball.getGlobalBounds().findIntersection(playerOne.getGlobalBounds()))
                {
                    sf::FloatRect paddleBounds = playerOne.getGlobalBounds();
                    float ballCenterY = ball.getPosition().y + ball.getRadius();

                    if (ballCenterY >= paddleBounds.position.y && ballCenterY <= paddleBounds.position.y + paddleBounds.size.y)
                    {
                        ball.setPosition({ playerOne.getPosition().x + playerOne.getSize().x, ball.getPosition().y });
                        speedX -= 50;
                        speedX *= -1;
                    }
                    else
                    {
                        speedY *= -1;
                    }
                }
                if (ball.getGlobalBounds().findIntersection(playerTwo.getGlobalBounds()))
                {
                    sf::FloatRect paddleBounds = playerTwo.getGlobalBounds();
                    float ballCenterY = ball.getPosition().y + ball.getRadius();

                    if (ballCenterY >= paddleBounds.position.y && ballCenterY <= paddleBounds.position.y + paddleBounds.size.y)
                    {
                        ball.setPosition({ playerTwo.getPosition().x - ball.getRadius() * 2, ball.getPosition().y });
                        speedX += 50;
                        speedX *= -1;
                    }
                    else
                    {
                        speedY *= -1;
                    }
                }

                if (ball.getPosition().x < 0)
                {
                    scoreTwo += 1;
                    scoreTwoText.setString("Player Two Score: " + std::to_string(scoreTwo));
                    point = true;
                    pause.restart();
                    One = true;
                    ball.setPosition(getRandomDot(400, 700));
                }

                if (ball.getPosition().x + ball.getRadius() * 2 > winSize.x)
                {
                    scoreOne += 1;
                    scoreOneText.setString("Player One Score: " + std::to_string(scoreOne));
                    pause.restart();
                    One = false;
                    point = true;
                    ball.setPosition(getRandomDot(100, 400));
                }
                if (scoreOne == 5)
                {
                    winText.setString("PLAYER ONE WINS!");
                    winText.setFillColor(sf::Color::Blue);
                    win = true;
                }
                if (scoreTwo == 5)
                {
                    winText.setString("PLAYER TWO WINS!");
                    winText.setFillColor(sf::Color::Red);
                    win = true;
                }

            }
            else
            {
                if (pause.getElapsedTime().asSeconds() > 3)
                {
                    if (One) speedX = startingSpeed * -1;
                    if (!One) speedX = startingSpeed;
                    speedY = startingSpeed;
                    point = false;
                }
            }
        }
        else
        {
            if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Enter))
            {
                win = false;
                scoreOne = 0;
                scoreOneText.setString("Player One Score: " + std::to_string(scoreOne));
                scoreTwo = 0;
                scoreTwoText.setString("Player Two Score: " + std::to_string(scoreTwo));
                

            }
        }

        window.clear();
        window.draw(ball);
        window.draw(playerOne);
        window.draw(playerTwo);
        window.draw(scoreOneText);
        window.draw(scoreTwoText);
        if (win)
        {
            window.draw(winText);
            window.draw(restartText);
        }
        window.display();
    }
}
