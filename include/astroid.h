#pragma once

#include <SFML/Graphics.hpp>

class Astroid
{
public:
    void aboutEnemy(sf::Texture &et);
    void enemyPosition();
    void move(sf::Vector2f playerPos, float dt);
    bool forDeletingEnemy(const sf::FloatRect &entitiBound) const;
    void draw(sf::RenderWindow &window);

    private:
    sf::RectangleShape shape;
    float speed = 70.0f;
    sf::Vector2f vilocity;
};