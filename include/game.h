#pragma once

#include "ui.h"

#include <SFML/Graphics.hpp>
#include <iostream>



class Game{
    public:
    Game();
    void run();

    private:
    sf::RenderWindow window;
    sf::Vector2u windowSize;
    sf::View windowView;
    int score;
    int highScore;
    int milestone;
    GameState currentState;
};