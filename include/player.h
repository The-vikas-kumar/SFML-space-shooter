#pragma once

#include <iostream>
#include <SFML/Graphics.hpp>
#include <cmath>

class Player{
    public:
    Player(const sf::Texture &t);
    void setPosition(sf::Vector2f pos);
    void resetPlayer();
    void newTexture(sf::Texture &t);
    void movePlayer(float dt);
    sf::Vector2f getPlayerDirection() const;
    sf::Vector2f playerPos() const;
    sf::FloatRect playerBound() const;
    void keepPlayerInside();
    void draw(sf::RenderWindow &window);

    private:
    void setOrigin();

    private:
    sf::Texture texture;
    sf::Sprite shape;
    float speed = 300.0f;
    float playerSize = 64.f;
};