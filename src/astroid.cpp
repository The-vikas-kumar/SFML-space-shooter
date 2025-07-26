#include "config.h"
#include "astroid.h"

#include <SFML/Graphics.hpp>
#include <cmath>

void Astroid::aboutEnemy(sf::Texture &et)
{
    shape.setSize(sf::Vector2f(70, 60));
    shape.setTexture(&et);
}

void Astroid::enemyPosition()
{
    // enemy logic
    float x, y;
    int side = rand() % 4;
    switch (side)
    {
    case 0:
        x = rand() % (WINDOW_W);
        y = -50;
        break;

    case 1:
        x = WINDOW_W + 50;
        y = rand() % (WINDOW_H + 50);
        break;

    case 2:
        x = rand() % (WINDOW_W + 50);
        y = WINDOW_H + 50;
        break;

    case 3:
        x = -50;
        y = rand() % (WINDOW_H);
        break;
    }

    shape.setPosition(sf::Vector2f(x, y));
}

void Astroid::move(sf::Vector2f playerPos, float dt)
{
    sf::Vector2f direction = playerPos - shape.getPosition();
    float length = std::sqrt(direction.x * direction.x + direction.y * direction.y);
    if (length != 0)
    {
        vilocity = direction / length * speed;
    }
    shape.move(vilocity * dt);
}

bool Astroid::forDeletingEnemy(const sf::FloatRect &entitiBound) const
{
    return shape.getGlobalBounds().findIntersection(entitiBound).has_value();
}

void Astroid::draw(sf::RenderWindow &window)
{
    window.draw(shape);
}
