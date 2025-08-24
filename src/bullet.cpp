#include "config.h"
#include "bullet.h"

#include <SFML/Graphics.hpp>



Bullet::Bullet() : speed(500.0f), deletRadius(600.f){
    shape.setSize(sf::Vector2f(10, 10));
    shape.setOrigin({5, 5});
    shape.setFillColor(sf::Color::White);
}

void Bullet::fire(sf::Vector2f pos, sf::Vector2f dir)
{
    shape.setPosition(pos);
    spawnPos = pos;
    direction = dir;
}

void Bullet::move(float dt)
{
    shape.move(direction * speed * dt);
}

sf::FloatRect Bullet::bulletBond() const
    {
        return shape.getGlobalBounds();
    }

    bool Bullet::forDeletingBullet() const
    {
        sf::Vector2f pos = shape.getPosition();
        float dx = pos.x - spawnPos.x;
        float dy = pos.y - spawnPos.y;
        float distanceSquared = dx * dx + dy * dy;

        return distanceSquared > deletRadius * deletRadius;
    }

    void Bullet::draw(sf::RenderWindow &window)
    {
        window.draw(shape);
    }

