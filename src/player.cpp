
#include "player.h"
#include "config.h"
#include "resource_manager.h"

#include <SFML/Graphics.hpp>
#include <iostream>
#include <cmath>

void Player::setOrigin()
{
    auto lb = shape.getLocalBounds(); // local (untransformed) width/height
    shape.setOrigin({lb.position.x + lb.size.x / 2,
                     lb.position.y + lb.size.y / 2});

    auto hlb = hitBox.getLocalBounds(); // local (untransformed) width/height
    hitBox.setOrigin({hlb.position.x + hlb.size.x / 2,
                     hlb.position.y + hlb.size.y / 2});
}

Player::Player(const sf::Texture &t) : shape(t), speed(300.f), playerSize(64.f)
{
    shape.setScale({playerSize / static_cast<float>(t.getSize().x), playerSize / static_cast<float>(t.getSize().y)});

    // hitBox.setFillColor(sf::Color::Green);
    sf::Vector2f pSize = shape.getGlobalBounds().size;
    hitBox.setSize({pSize.x - 15, pSize.y - 15});

    setOrigin();
}

void Player::setPosition(const sf::Vector2f pos)
{
    shape.setPosition({pos});
    hitBox.setPosition({pos});
}

void Player::resetPlayer(){
    setOrigin();
    shape.setPosition({WINDOW_W / 2, WINDOW_H / 2});
    shape.setRotation(sf::degrees(0));
    hitBox.setPosition({WINDOW_W / 2, WINDOW_H / 2});
} 

void Player::setSize(float size){
    const sf::Texture& t = shape.getTexture();
    shape.setScale({size/ static_cast<float>(t.getSize().x), size / static_cast<float>(t.getSize().y)});
}

void Player::newTexture(const sf::Texture &t)
{
    shape.setTexture(t, true);
    shape.setScale({playerSize / static_cast<float>(t.getSize().x), playerSize / static_cast<float>(t.getSize().y)});

    sf::Vector2f pSize = shape.getGlobalBounds().size;
    hitBox.setSize({pSize.x - 15, pSize.y - 15});

    setOrigin();
}

void Player::movePlayer(float dt)
{
    sf::Vector2f direction{0.0f, 0.0f};

    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Scan::D))
    {
        direction.x += 1;
    }
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Scan::A))
    {
        direction.x -= 1;
    }
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Scan::W))
    {
        direction.y -= 1;
    }
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Scan::S))
    {
        direction.y += 1;
    }

    if (direction.x != 0 || direction.y != 0)
    {
        float len = std::sqrt(direction.x * direction.x + direction.y * direction.y);
        direction /= len;

        float angleRed = std::atan2(direction.y, direction.x);
        float angleDeg = angleRed * 180.f / 3.14159265f;
        shape.setRotation(sf::degrees(angleDeg + 90));
    }

    shape.move({direction * speed * dt});
    auto pos = shape.getPosition();
    hitBox.setPosition({pos});
}

sf::Vector2f Player::getPlayerDirection() const
{
    float angleDeg = shape.getRotation().asDegrees() - 90.f;
    float angleRed = angleDeg * (3.14159265f / 180.f);
    return sf::Vector2f(std::cos(angleRed), std::sin(angleRed));
}

sf::Vector2f Player::playerPos() const
{
    return shape.getPosition();
}

sf::FloatRect Player::playerBound() const
{
    return hitBox.getGlobalBounds();
}

void Player::keepPlayerInside()
{
    sf::Vector2f pos = shape.getPosition();
    sf::Vector2f size = shape.getGlobalBounds().size;

    float clampedX = std::max(size.x / 2, std::min(pos.x, static_cast<float>(WINDOW_W) - size.x / 2));
    float clampedY = std::max(size.y / 2, std::min(pos.y, static_cast<float>(WINDOW_H) - size.y / 2));

    shape.setPosition(sf::Vector2f(clampedX, clampedY));
}

void Player::draw(sf::RenderWindow &window)
{
    window.draw(shape);
    // window.draw(hitBox);
}
