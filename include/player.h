#pragma once

#include <iostream>
#include <SFML/Graphics.hpp>
#include <cmath>

class Player{
public:
    Player(const sf::Texture &t);
    void setPosition(const sf::Vector2f pos);
    void setSize(float size);
    void resetPlayer();
    void newTexture(const sf::Texture &t);
    void movePlayer(float dt);
    sf::Vector2f getPlayerDirection() const;
    sf::Vector2f playerPos() const;
    sf::FloatRect playerBound() const;
    void keepPlayerInside();
    void draw(sf::RenderWindow &window);

private:
    void setOrigin();

private:
    sf::RectangleShape hitBox;
    sf::Sprite shape;
    float speed;
    float playerSize;
};