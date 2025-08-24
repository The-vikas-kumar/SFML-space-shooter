#include "config.h"
#include "astroid.h"

#include <SFML/Graphics.hpp>
#include <random>
#include <cmath>

void Astroid::aboutAsteroid(const sf::Texture &t)
{
    shape.setSize(sf::Vector2f(70, 60));
    shape.setTexture(&t);
    auto lb = shape.getLocalBounds(); // local (untransformed) width/height
    shape.setOrigin({lb.position.x + lb.size.x / 2,
                     lb.position.y + lb.size.y / 2});
    // hitbox
    hitBox.setSize({50, 43});
    // hitBox.setFillColor(sf::Color::Green);
    auto hlb = hitBox.getLocalBounds();
    hitBox.setOrigin({hlb.position.x + hlb.size.x / 2,
                     hlb.position.y + hlb.size.y / 2});
    
}

void Astroid::spawnAsteroid(sf::Vector2f playerPos)
{
    static std::random_device rd;
    static std::mt19937 gen(rd()); // Mersenne Twister RNG

    // Distributions
    std::uniform_real_distribution<float> angleDist(0.f, 2.f * 3.14159265f); // 0 to 2π
    std::uniform_real_distribution<float> radiusDist(1000.f, 1200.f);          // Min to Max distance

    // Generate random angle and radius
    float angle = angleDist(gen);
    float distance = radiusDist(gen);

    // Convert polar coordinates to Cartesian (relative to player)
    float x = playerPos.x + distance * std::cos(angle);
    float y = playerPos.y + distance * std::sin(angle);

    shape.setPosition({x, y});
    hitBox.setPosition({x, y});
}

void Astroid::move(sf::Vector2f playerPos, float dt)
{
    sf::Vector2f direction = playerPos - shape.getPosition();
    float length = std::sqrt(direction.x * direction.x + direction.y * direction.y);
    if (length != 0)
    {
        velocity = direction / length * speed;
    }
    shape.move(velocity * dt);
    shape.rotate(sf::degrees(1));

    hitBox.move(velocity * dt);
    // hitBox.rotate(sf::degrees(1));
}

bool Astroid::forDeletingAsteroid(const sf::FloatRect &entitiBound) const
{
    return hitBox.getGlobalBounds().findIntersection(entitiBound).has_value();
}

void Astroid::draw(sf::RenderWindow &window)
{
    window.draw(shape);
    // window.draw(hitBox);
}

