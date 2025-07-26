#pragma once

#include <SFML/Graphics.hpp>

class Bullet
{
public:
    Bullet();
    void fire(sf::Vector2f pos, sf::Vector2f dir);
    void move(float dt);
    sf::FloatRect bulletBond() const;
    bool isOffScrean() const;
    void draw(sf::RenderWindow &window);

private:
    sf::RectangleShape shape;
    float speed;
    sf::Vector2f direction;
};
