#include <iostream>
#include <SFML/Graphics.hpp>
#include <ctime>
#include <cstdlib>
#include <cmath>
#include <string>
#include <sstream>
#include "Toolkit.hpp"

#define PVector sf::Vector2f

int random(double limit, int base)
{
    int r = rand() % int(limit) + base;
    if(r >= limit)
    {
        r = limit;
    }
    return r;
}

class CheckerBoard
{
    PVector cellSize;
    PVector boardSize;
    std::vector<sf::Color> colors;
    std::vector<sf::RectangleShape> rects;

    void generateColors(int cLimit)
    {
        for(int i = 0; i < cLimit; i++)
        {
            sf::Color color( random(255, 5), random(255, 5), random(255, 5), random(255, 5) );
            colors.push_back(color);
        }
    }
public:
    CheckerBoard(PVector windowSize, int rows, int col)
    {
        boardSize = windowSize;
        cellSize.x = boardSize.x / rows;
        cellSize.y = boardSize.y / col;

        colors.clear();
        generateColors( random(sqrt(rows * col), 2) );

        int counter = 0;
        for(float i = 0; i < windowSize.x; i+=cellSize.x)
        {
            for(float j = 0; j < windowSize.y; j+=cellSize.y)
            {
                sf::RectangleShape rect;
                rect.setPosition(i, j);
                rect.setSize(cellSize);

                sf::Color color = colors[counter];
                rect.setFillColor(color);
                counter ++;

                if(counter == colors.size())
                {
                    counter = 0;
                }

                rects.push_back(rect);
            }
        }
    }
    void draw(sf::RenderWindow& window)
    {
        for(int i = 0; i < rects.size(); i++)
        {
            window.draw(rects[i]);
        }
    }
    void draw(sf::RenderTexture& texture)
    {
        for(int i = 0; i < rects.size(); i++)
        {
            texture.draw(rects[i]);
        }
    }
};

class Game
{
    AdjustableView view;

    sf::Vector2f mousePos(sf::RenderWindow& screen)
    {
        sf::Vector2f mouse = sf::Vector2f(sf::Mouse::getPosition(screen));
        return mouse;
    }

    sf::Vector2f windowSize(sf::RenderWindow& screen)
    {
        sf::Vector2f winSize = sf::Vector2f(screen.getSize());
        return winSize;
    }
public:
    void main(sf::RenderWindow& window)
    {
        view.setSize(windowSize(window));

        CheckerBoard cb(windowSize(window), random(500, 1), random(500, 1));
        bool reset = false;

        std::vector<sf::Image*> screenshots;
        sf::Color bg = sf::Color::Black;

        float timer = 0;
        float time_limit = 2;

        int counter = 0;

        sf::Clock clock;
        while (window.isOpen())
        {
            float dt = clock.restart().asSeconds();

            timer += dt;
            if(timer >= time_limit)
            {
                timer = 0;
                reset = true;
            }

            sf::Event event;
            while (window.pollEvent(event))
            {
                if (event.type == sf::Event::Closed)
                {
                    window.close();
                }
            }
            window.clear(bg);

            cb.draw(window);
            window.display();

            if(reset)
            {
                counter ++;
                if(counter % 2 == 0)
                {
                    srand(time(NULL));
                }

                bg = sf::Color( random(75, 5), random(75, 5), random(75, 5) );

                sf::Image* image = new sf::Image(window.capture());
                screenshots.push_back(image);

                int cellLimit = random(150, 5);
                cb = CheckerBoard(windowSize(window), random(cellLimit, 5), random(cellLimit, 5));
                reset = false;
            }

            if(screenshots.size() > 0)
            {
                std::string filename = to_string(counter) + to_string(random(1000, 5)) + to_string(random(1000, 5)) + to_string(random(1000, 5));
                if( screenshots.back()->saveToFile("images/" + filename + ".png") )
                {
                    screenshots.pop_back();
                }
            }

        }
    }
};

int main()
{
    srand(time(NULL));
    sf::RenderWindow window(sf::VideoMode(1680, 1050), "Tessellation");
    Game().main(window);
    return 0;
}
