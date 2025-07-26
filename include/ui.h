#pragma once

#include <SFML/Graphics.hpp>

enum class GameState
{
    StartMenu,
    Settings,
    ChangeSkin,
    Options,
    GameOver,
    Playing
};

struct Button
{
public:
    void aboutButton(sf::Texture &texture, sf::Vector2f pos, sf::Vector2f size);
    void setColor(sf::Color color);
    bool getGlobalBounds(sf::Vector2f mousePos) const;
    void draw(sf::RenderWindow &window);

private:
    sf::RectangleShape shape;
};