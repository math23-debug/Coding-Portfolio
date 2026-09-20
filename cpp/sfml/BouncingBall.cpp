#include <SFML/Graphics.hpp>
#include <cmath>
#include <string>
#include <cstdlib>
#include <cctype>
#include <limits>
#include <vector>
#include <iostream>

class Ball
{
private: 
    float speedX = 0, speedY = 0;
    float friction = 0.9998f;
    sf::Vector2f startPos;
    sf::CircleShape circle;
    bool wasPressed = false, launched = false, relaunch = true;
    sf::VertexArray line;

public:
    Ball(float radius, sf::Vector2f position)
        : line(sf::PrimitiveType::Lines, 2)
    {
        circle.setRadius(radius);
        circle.setFillColor(sf::Color::Red);
        circle.setPosition(position);
        startPos = circle.getPosition();
        startPos.x += circle.getRadius();
        startPos.y += circle.getRadius();
    }

    bool isNotLaunched(sf::RenderWindow& window)
    {
        bool isPressed = sf::Mouse::isButtonPressed(sf::Mouse::Button::Left);
        sf::Vector2f mousePos = window.mapPixelToCoords(sf::Mouse::getPosition(window));

        if (isPressed)
        {
            line[0].position = startPos;
            line[0].color = sf::Color::White;
            line[1].position = mousePos;
            line[1].color = sf::Color::White;
            relaunch = false;
        }
        if (wasPressed && !isPressed)
        {
            sf::Vector2f dragVector = startPos - mousePos;
            speedX = dragVector.x * 3;
            speedY = dragVector.y * 3;
            wasPressed = isPressed;
            launched = true;
            return true;
        }
        else
        {
            wasPressed = isPressed;
            launched = false;
            return false;
        }
    }

    void bounce(sf::RenderWindow& window)
    {
        if (circle.getPosition().x < 0)
        {
            circle.setPosition({ 0.f, circle.getPosition().y });
            speedX *= -1;
        }
        if (circle.getPosition().x + (circle.getRadius() * 2) > window.getSize().x)
        {
            circle.setPosition({ window.getSize().x - (circle.getRadius() * 2), circle.getPosition().y});
            speedX *= -1;
        }
        if (circle.getPosition().y < 0)
        {
            circle.setPosition({ circle.getPosition().x, 0.f });
            speedY *= -1;
        }
        if (circle.getPosition().y + (circle.getRadius() * 2) > window.getSize().y)
        {
            circle.setPosition({ circle.getPosition().x, window.getSize().y - (circle.getRadius() * 2)});
            speedY *= -1;
        }
    }
    void move(float deltaTime)
    {
        circle.move({ speedX * deltaTime, speedY * deltaTime });
    }

    void stop()
    {
        if (std::abs(speedX) < 15.f && std::abs(speedY) < 15.f)
        {
            wasPressed = false;
            launched = false;
            relaunch = true;
            startPos = circle.getPosition();
            startPos.x += circle.getRadius();
            startPos.y += circle.getRadius();
        }
    }

    void applyFriction()
    {

        if (std::abs(speedX) < 225.f && std::abs(speedY) < 225.f) friction = 0.9995f;
        else friction = 0.9998f;

        speedX *= friction;
        speedY *= friction;

    }

    void draw(sf::RenderWindow& window)
    {
        if (!launched && !relaunch) window.draw(line);
        window.draw(circle);
    }

    bool isTheBallLaunched()
    {
        return launched;
    }
};

int main()
{
    sf::Vector2f position = { 300.f, 200.f };
    Ball ball(50, position);

    sf::RenderWindow window(sf::VideoMode({ 800, 600 }), "My First Window", sf::Style::Titlebar | sf::Style::Close);

    sf::Clock clock;

    while (window.isOpen())
    {
        while (const std::optional event = window.pollEvent())
        {
            if (event->is<sf::Event::Closed>())
                window.close();
        }

        float deltaTime = clock.restart().asSeconds();
        sf::Vector2u windSize = window.getSize();  

        if (!ball.isTheBallLaunched())
        {

            ball.isNotLaunched(window);
        }
        else
        {
            ball.bounce(window);

            ball.move(deltaTime);

            ball.stop();

            ball.applyFriction();
            
        }

        window.clear();
        ball.draw(window);
        window.display();
    }
}