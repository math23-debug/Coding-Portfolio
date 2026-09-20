#include <SFML/Graphics.hpp>
#include <cmath>
#include <string>
#include <cstdlib>
#include <cctype>
#include <limits>
#include <vector>
#include <random>
#include <iostream>
#include <deque>

int randPos()
{
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<int> distX(0, 14);
    return distX(gen);
}

void draw(sf::Color color, sf::Vector2f position, sf::RenderWindow& window)
{
    sf::RectangleShape cell({ 40.f, 40.f });
    cell.setPosition({ position.x * 40.f, position.y * 40.f });
    cell.setFillColor(color);
    window.draw(cell);
}

void drawBackground(int x, int y, sf::Color color, sf::RenderWindow& window)
{
    sf::RectangleShape cell({ 40.f, 40.f });
    cell.setPosition({ x * 40.f, y * 40.f });
    cell.setFillColor(color);
    window.draw(cell);
}

int main()
{
    sf::RenderWindow window(sf::VideoMode({ 600, 600 }), "Snake", sf::Style::Titlebar | sf::Style::Close);

    sf::Vector2i moveDirection = { -1, 0 }; 
    sf::Vector2i inputDirection = { -1, 0 };
    sf::Clock moveClock;
    float moveInterval = 0.15;
    sf::Vector2f bounce({ 0,0 });
    sf::Vector2i foodPos({ randPos(), randPos() });

    int highscore = 0, score = 0;

    bool loss = false, start = true;

    sf::Color snakeHead(20, 90, 20);        // keep as-is, dark green
    sf::Color snakeBody(60, 130, 60);       // keep as-is, lighter green
    sf::Color foodColor(200, 50, 50);       // keep as-is, red pops well against green

    sf::Color lightCell(170, 215, 81);      // light grass green
    sf::Color darkCell(162, 209, 73);       // slightly darker grass green

    sf::RectangleShape food({ 40.f, 40.f });
    food.setFillColor(foodColor);

    std::deque<sf::Vector2i> snake;
    snake.push_back({ 7,7 });
    snake.push_back({ 8,7 });
    snake.push_back({ 9,7 });

    sf::Font font;

    if (!font.openFromFile("Requiner-6RRLM.otf"))
    {
        std::cout << "Failed to load Requiner font\n";
    }

    sf::Text scoreText(font, "Score", 25.f);
    scoreText.setFillColor(sf::Color::Black);
    scoreText.setPosition({ 10.f, 10.f});

    sf::Text highscoreText(font, "Highscore", 25.f);
    highscoreText.setFillColor(sf::Color::Black);
    highscoreText.setPosition({ 600.f - highscoreText.getGlobalBounds().size.x + 10.f, 10.f});

    while (window.isOpen())
    {
        while (const std::optional event = window.pollEvent())
        {
            if (event->is<sf::Event::Closed>())
                window.close();
        }
        
        if (!loss)
        {
            if ((sf::Keyboard::isKeyPressed(sf::Keyboard::Key::D) || sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Right)) && moveDirection != sf::Vector2i({ -1, 0 }))
            {
                inputDirection = { 1, 0 };
            }
            if ((sf::Keyboard::isKeyPressed(sf::Keyboard::Key::A) || sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Left)) && moveDirection != sf::Vector2i({ 1, 0 }))
            {
                inputDirection = { -1, 0 };
            }
            if ((sf::Keyboard::isKeyPressed(sf::Keyboard::Key::W) || sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Up)) && moveDirection != sf::Vector2i({ 0, 1 }))
            {
                inputDirection = { 0, -1 };
            }
            if ((sf::Keyboard::isKeyPressed(sf::Keyboard::Key::S) || sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Down)) && moveDirection != sf::Vector2i({ 0, -1 }))
            {
                inputDirection = { 0, 1 };
            }

            if (moveClock.getElapsedTime().asSeconds() > moveInterval)
            {
                moveDirection = inputDirection;
                snake.push_front(snake[0] + moveDirection);
                if (snake[0].x < 0 || snake[0].x > 14 || snake[0].y < 0 || snake[0].y > 14)
                {
                    loss = true;
                    snake.pop_front();
                    if (score > highscore) highscore = score;
                }
                for (int i = 1; i < snake.size(); i++)
                {
                    if (snake[0].x == snake[i].x && snake[0].y == snake[i].y)
                    {
                        loss = true;
                        snake.pop_front();
                        if (score > highscore) highscore = score;
                    }
                }

                if (snake[0] == foodPos)
                {
                    score += 1;
                    for (int i = 0; i < snake.size(); i++)
                    {
                        while (foodPos.x == snake[i].x && foodPos.y == snake[i].y)
                        {
                            foodPos = sf::Vector2i({ randPos(), randPos() });
                        }
                    }
                }
                else if (!loss)
                {
                    snake.pop_back();
                }
                moveClock.restart();
            }
        }
        else
        {
                if (moveClock.getElapsedTime().asSeconds() > 0.08)
                {
                    if (moveClock.getElapsedTime().asSeconds() > 0.4) bounce = { 0,0 };
                    else
                    {
                        if (moveDirection.x == -1) bounce = { 0.3, 0 };
                        if (moveDirection.x == 1) bounce = { -0.3, 0 };
                        if (moveDirection.y == -1) bounce = { 0, 0.3 };
                        if (moveDirection.y == 1) bounce = { 0, -0.3 };
                    }
                }

                if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Enter))
                {
                    loss = false; 
                    foodPos = sf::Vector2i({ randPos(), randPos() });
                    snake.clear();
                    snake.push_back({ 7,7 });
                    snake.push_back({ 8,7 });
                    snake.push_back({ 9,7 });
                    moveDirection = { -1, 0 };
                    inputDirection = { -1, 0 };
                    score = 0;
                }
        }

        food.setPosition({ foodPos.x * 40.f, foodPos.y * 40.f });

        scoreText.setString("Score: " + std::to_string(score));
        highscoreText.setString("High score: " + std::to_string(highscore));
        highscoreText.setPosition({ 600.f - highscoreText.getGlobalBounds().size.x - 10.f, 10.f });

        window.clear();
        for (int x = 0; x < 15; x++)
        {
            for (int y = 0; y < 15; y++)
            {
                if (((x%2) == 0) != ((y%2) == 0)) drawBackground(x, y, darkCell, window);
                else drawBackground(x, y, lightCell, window);
            }
        }
        window.draw(food);
        for (int i = snake.size() - 1; i >= 0; i--)
        {
            sf::Vector2f position = { static_cast<float>(snake[i].x) + bounce.x, static_cast<float>(snake[i].y) + bounce.y };
            if (i == 0) draw(snakeHead, position, window);
            else draw(snakeBody, sf::Vector2f({ static_cast<float>(snake[i].x), static_cast<float>(snake[i].y)}) , window);
        }
        window.draw(highscoreText);
        window.draw(scoreText);
        window.display();
    }
}
