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
#include <fstream>
#include <algorithm>



void drawLevel(sf::RenderWindow& window, const std::vector<std::string>& grid, const float tileSize)
{
    sf::RectangleShape cell({ tileSize, tileSize });

    for (size_t row = 0; row < grid.size(); row++)
    {
        for (size_t col = 0; col < grid[row].size(); col++)
        {
            cell.setPosition({ tileSize * col, tileSize * row });
            switch (grid[row][col])
            {
            case '#':
                cell.setFillColor(sf::Color(143, 86, 59));
                break;
            case 'P':
            case '.':
                cell.setFillColor(sf::Color(34, 32, 52));
                break;
            case 'G':
                cell.setFillColor(sf::Color(251, 242, 54));
                break;
            default:
                cell.setFillColor(sf::Color(235, 52, 198));
                break;
            }
            window.draw(cell);
        }
    }
}

std::vector<sf::FloatRect> buildWalls(const std::vector<std::string>& grid, const float tileSize)
{
    std::vector<sf::FloatRect> walls;
    for (size_t row = 0; row < grid.size(); row++)
    {
        for (size_t col = 0; col < grid[0].size(); col++)
        {
            if (grid[row][col] == '#')
            {
                sf::FloatRect wall({ tileSize * col, tileSize * row }, { tileSize, tileSize });
                walls.push_back(wall);
            }
        }
    }
    return walls;
}

sf::Vector2f findPlayerStartPos(const std::vector<std::string>& grid, const float tileSize)
{
    for (size_t row = 0; row < grid.size(); row++)
    {
        for (size_t col = 0; col < grid[0].size(); col++)
        {
            if (grid[row][col] == 'P')
            {
                return { tileSize * col + tileSize / 4, tileSize * row + tileSize / 4 };
            }
        }
    }
    std::cout << "WARNING!\nNo player found";
    return { 0.f, 0.f };
}

sf::FloatRect findGoal(const std::vector<std::string>& grid, const float tileSize)
{
    for (size_t row = 0; row < grid.size(); row++)
    {
        for (size_t col = 0; col < grid[0].size(); col++)
        {
            if (grid[row][col] == 'G')
            {
                return sf::FloatRect({ tileSize * col, tileSize * row }, { tileSize, tileSize });
            }
        }
    }
    std::cout << "WARNING!\nNo goal found";
    return sf::FloatRect({ 0.f, 0.f }, { 1.f, 1.f });
}

bool isHit(const std::vector<sf::FloatRect>& walls, const sf::FloatRect& playerBounds)
{
    return std::any_of(walls.begin(), walls.end(),
        [&playerBounds](const sf::FloatRect& wall)
        {
            return playerBounds.findIntersection(wall).has_value();
        });
}

int main()
{
    std::vector<std::string> grid;
    std::ifstream file("level2.txt");
    if (!file) 
    {
        std::cout << "File did not load"; 
        return 1;
    }

    const float tileSize = 64.f;

    std::string line;
    while (std::getline(file, line))
    {
        grid.push_back(line);
    }
    for (const std::string& row : grid)
    {
        std::cout << row << "\n";
    }

    sf::Font font;

    if (!font.openFromFile("Requiner-6RRLM.otf"))
    {
        std::cout << "Failed to load Requiner font\n";
    }

    sf::Text winText(font, "", 90);
    winText.setPosition({ 95, 250 });
    winText.setFillColor(sf::Color::Blue);

    const float speed = 350;

    sf::Clock clock;

    sf::RectangleShape player({ tileSize / 2, tileSize / 2 });
    player.setFillColor({ sf::Color(3, 112, 3) });
    player.setPosition(findPlayerStartPos(grid, tileSize));
    std::vector<sf::FloatRect> walls = buildWalls(grid, tileSize);
    sf::FloatRect goal(findGoal(grid, tileSize));

    unsigned int width = static_cast<unsigned int>(grid[0].size() * tileSize);
    unsigned int height = static_cast<unsigned int>(grid.size() * tileSize);

    sf::RenderWindow window(sf::VideoMode({ width, height}), "Maze V1", sf::Style::Titlebar | sf::Style::Close);

    bool win = false;

    while (window.isOpen())
    {
        while (const std::optional event = window.pollEvent())
        {
            if (event->is<sf::Event::Closed>())
                window.close();
        }

        if (!win)
        {
            float deltaTime = clock.restart().asSeconds();

            if (deltaTime > 0.05) { deltaTime = 0.05; }
            float speedConst = 1;
            int moveX = 0, moveY = 0;

            if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::D) || sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Right)) { moveX = 1; }
            if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::A) || sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Left)) { moveX = -1; }
            if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::W) || sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Up)) { moveY = -1; }
            if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::S) || sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Down)) { moveY = 1; }

            // if (moveX != 0 && moveY != 0) { speedConst = std::sqrt(2); }
            sf::Vector2f oldPos = player.getPosition();
            if (moveX != 0)
            {
                player.move({ speed * deltaTime * moveX / speedConst, 0.f });
                sf::FloatRect playerBounds = player.getGlobalBounds();
                if (isHit(walls, playerBounds))
                {
                    player.setPosition(oldPos);
                }
            }
            oldPos = player.getPosition();
            if (moveY != 0)
            {
                player.move({ 0.f, speed * deltaTime * moveY / speedConst });
                sf::FloatRect playerBounds = player.getGlobalBounds();
                if (isHit(walls, playerBounds))
                {
                    player.setPosition(oldPos);
                }
            }
            sf::Vector2f playerCenter = { player.getPosition().x + (tileSize / 2), player.getPosition().y + (tileSize / 2) };
            if (goal.contains(playerCenter))
            {
                winText.setString("YOU WIN!");
                win = true;
            }
        }
        window.clear();
        drawLevel(window, grid, tileSize);
        window.draw(player);
        window.draw(winText);
        window.display();
    }
}
