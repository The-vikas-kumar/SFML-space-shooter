#include "ui.h"

#include <SFML/Graphics.hpp>

void Button::aboutButton(sf::Texture &texture, sf::Vector2f pos, sf::Vector2f size)
{
    shape.setPosition(pos);
    shape.setSize(size);
    shape.setTexture(&texture);
}

void Button::setColor(sf::Color color)
{
    shape.setFillColor(color);
}

bool Button::getGlobalBounds(sf::Vector2f mousePos) const
{
    return shape.getGlobalBounds().contains(mousePos);
}

void Button::draw(sf::RenderWindow &window)
{
    window.draw(shape);
}
