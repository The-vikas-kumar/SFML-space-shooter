#pragma once

#include <SFML/Graphics.hpp>

class Astroid
{
public:
    void aboutAsteroid(const sf::Texture &t);
    void spawnAsteroid(sf::Vector2f playerPos);
    void move(sf::Vector2f playerPos, float dt);
    bool forDeletingAsteroid(const sf::FloatRect &entitiBound) const;
    void draw(sf::RenderWindow &window);

    private:
    sf::RectangleShape shape;
    sf::RectangleShape hitBox;
    float speed = 70.0f;
    sf::Vector2f velocity;
};