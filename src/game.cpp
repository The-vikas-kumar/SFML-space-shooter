#include "game.h"
#include "player.h"
#include "config.h"
#include "bullet.h"
#include "astroid.h"
#include "ui.h"
#include "resource_manager.h"

#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <iostream>
#include <fstream>
#include <algorithm>
#include <vector>
#include <ctime>
#include <cmath>

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

Game::Game() : window(sf::VideoMode({WINDOW_W, WINDOW_H}), "SPACE SHOOTER"){
    window.setFramerateLimit(60);
    windowSize = window.getSize();

    score = 0;
    highScore = 0;
    milestone = 0;
    currentState = GameState::StartMenu;

    // all textuer added here
    TextureManager::loadTexture("player1", "assets/ship.png");
    TextureManager::loadTexture("player2", "assets/ship1.png");
    TextureManager::loadTexture("player3", "assets/ship2.png");
    TextureManager::loadTexture("player4", "assets/ship3.png");
    TextureManager::loadTexture("player5", "assets/ship4.png");
    TextureManager::loadTexture("asteroid", "assets/asteroid.png");
    TextureManager::loadTexture("mainBackground", "assets/spaceBackground.jpg");
    TextureManager::loadTexture("uiBackground", "assets/uiBackground.jpg");
    TextureManager::loadTexture("startBackground", "assets/startBackground.png");
    TextureManager::loadTexture("startButton", "assets/startButton.png");
    TextureManager::loadTexture("settingsButton", "assets/settingsIcon.png");
    TextureManager::loadTexture("restartButton", "assets/restartButton.png");
    TextureManager::loadTexture("changeSkinButton", "assets/changeSkinButton.png");
    TextureManager::loadTexture("optionsButton", "assets/optionsButton.png");
    TextureManager::loadTexture("backButton", "assets/backIcon.png");
    TextureManager::loadTexture("homeButton", "assets/homeIcon.png");
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void Game::run()
{
    std::srand(static_cast<unsigned>(time(nullptr)));

    // sound effects and music
    // laser gun fire sound
    sf::SoundBuffer laserBuffer;
    if (!laserBuffer.loadFromFile("assets/laserGunShot.wav"))
    {
        std::cout << "cant load gun shot sound";
        //return -1;
    }
    sf::Sound lazerSound(laserBuffer);

    // explosion sound
    sf::SoundBuffer explosionBuffer;
    if (!explosionBuffer.loadFromFile("assets/explosion.wav"))
    {
        std::cout << "cant load explosion sound";
        //return -1;
    }
    sf::Sound explosionSound(explosionBuffer);

    // background music
    sf::Music backgroundMusic;
    if (!backgroundMusic.openFromFile("assets/spaceMusic.wav"))
    {
        std::cout << "cant load background music";
        //return -1;
    }
    backgroundMusic.setLooping(true);
    backgroundMusic.play();

////////////////////////////////////////////////////////////////////////////////////////////////////////////

    // add buttons
    // start button
    sf::Vector2f startButtonPos = {WINDOW_W / 2 - 100, WINDOW_H / 2 - 100};
    sf::Vector2f startButtonSize = {200, 100};
    Button startButton;
    startButton.aboutButton(TextureManager::getTexture("startButton"), startButtonPos, startButtonSize);

    // back button
    sf::Vector2f backButtonPos = {WINDOW_W - 50, 0};
    sf::Vector2f backButtonSize = {50, 50};
    Button backButton;
    backButton.aboutButton(TextureManager::getTexture("backButton"), backButtonPos, backButtonSize);

    // settings button
    sf::Vector2f settingsButtonPos = {WINDOW_W - 100, 50};
    sf::Vector2f settingsButtonSize = {50, 50};
    Button settingsButton;
    settingsButton.aboutButton(TextureManager::getTexture("settingsButton"), settingsButtonPos, settingsButtonSize);

    // change skin button
    sf::Vector2f skinButtonPos = {WINDOW_W / 2 - 100, WINDOW_H / 2};
    sf::Vector2f skinButtonSize = {200, 100};
    Button skinButton;
    skinButton.aboutButton(TextureManager::getTexture("changeSkinButton"), skinButtonPos, skinButtonSize);

    // options button
    sf::Vector2f optionsButtonPos = {WINDOW_W / 2 - 100, WINDOW_H / 2 + 150};
    sf::Vector2f optionsButtonSize = {200, 100};
    Button optionsButton;
    optionsButton.aboutButton(TextureManager::getTexture("optionsButton"), optionsButtonPos, optionsButtonSize);

    // restart button
    sf::Vector2f restartButtonPos = {WINDOW_W / 2 - 100, WINDOW_H / 2 + 150};
    sf::Vector2f restartButtonSize = {200, 100};
    Button restartButton;
    restartButton.aboutButton(TextureManager::getTexture("restartButton"), restartButtonPos, restartButtonSize);

    // home button
    sf::Vector2f homeButtonPos = {WINDOW_W / 2 - 50, 0};
    sf::Vector2f homeButtonSize = {50, 50};
    Button homeButton;
    homeButton.aboutButton(TextureManager::getTexture("homeButton"), homeButtonPos, homeButtonSize);

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

    // for highscore
    std::ifstream inputFile("assets/highscore.txt");
    if (inputFile.is_open())
    {
        inputFile >> highScore;
        inputFile.close();
    }

    // fonts for text
    sf::Font font;
    if (!font.openFromFile("assets/Dinofans.ttf"))
    {
        std::cout << "font did not load from file";
        //return -1;
    }
    sf::Font gameFont;
    if (!gameFont.openFromFile("assets/game_over.ttf"))
    {
        std::cout << "font did not load from file";
        //return -1;
    }

    // text
    // score text
    sf::Text scoreText(font);
    scoreText.setCharacterSize(48);
    scoreText.setFillColor(sf::Color::White);
    scoreText.setPosition(sf::Vector2f(20, 20));

    // game over text
    sf::Text gameOverText(gameFont);
    gameOverText.setCharacterSize(148);
    gameOverText.setFillColor(sf::Color::Red);
    gameOverText.setPosition(sf::Vector2f(WINDOW_W / 2 - 350, WINDOW_H / 2 - 250));

    // highscore text
    sf::Text highscoreText(font);
    highscoreText.setCharacterSize(48);
    highscoreText.setFillColor(sf::Color::White);
    highscoreText.setPosition(sf::Vector2f(WINDOW_W - 450, 20));

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

    // main game background
    sf::Sprite mainBackground(TextureManager::getTexture("mainBackground"));
    sf::Vector2u mainBackT = TextureManager::getTexture("mainBackground").getSize();
    float scaleXforMain = (float)windowSize.x / mainBackT.x;
    float scaleYforMain = (float)windowSize.y / mainBackT.y;
    mainBackground.setScale(sf::Vector2f(scaleXforMain, scaleYforMain));

    // start screen background
    sf::Sprite startBackground(TextureManager::getTexture("startBackground"));
    sf::Vector2u startBackT = TextureManager::getTexture("startBackground").getSize();
    float scaleXforStart = (float)windowSize.x / startBackT.x;
    float scaleYforStart = (float)windowSize.y / startBackT.y;
    startBackground.setScale(sf::Vector2f(scaleXforStart, scaleYforStart));

    // ui background
    sf::Sprite uiBackground(TextureManager::getTexture("uiBackground"));
    sf::Vector2u uiBackT = TextureManager::getTexture("uiBackground").getSize();
    float scaleXforUi = (float)windowSize.x / uiBackT.x;
    float scaleYforUi = (float)windowSize.y / uiBackT.y;
    uiBackground.setScale(sf::Vector2f(scaleXforUi, scaleYforUi));

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

    // delta clock
    sf::Clock deltaClock;

    // button clock
    sf::Clock buttonClock;
    float buttonCooldown = 0.5;

    // bullet cooldown timer
    sf::Clock fireClock;
    float bulletCooldown = 0.2f;

    // clock for astroid
    sf::Clock astroidClock;
    float astroidCooldown = 2.0f;

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

    // create player
    Player player(TextureManager::getTexture("player1"));
    player.setPosition(sf::Vector2f(WINDOW_W / 2, WINDOW_H / 2));

    // create bullet
    std::vector<Bullet> bullet;

    // create enemy
    std::vector<Astroid> astroid;

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    while (window.isOpen())
    {

        while (const std::optional event = window.pollEvent())
        {
            if (event->is<sf::Event::Closed>())
            {
                window.close();
            }

            if (const auto *mb = event->getIf<sf::Event::MouseButtonPressed>())
            {
                if (mb->button == sf::Mouse::Button::Left)
                {
                    sf::Vector2i mousePixel = sf::Mouse::getPosition(window);
                    sf::Vector2f mousePos = window.mapPixelToCoords(mousePixel);

                    switch (currentState)
                    {
                    case GameState::StartMenu:
                    {
                        if (startButton.getGlobalBounds(mousePos))
                        {
                            currentState = GameState::Playing;
                            astroidClock.restart();
                        }
                        if (settingsButton.getGlobalBounds(mousePos))
                        {
                            currentState = GameState::Settings;
                        }

                        break;
                    }

                    case GameState::Settings:
                    {
                        if (backButton.getGlobalBounds(mousePos))
                        {
                            currentState = GameState::StartMenu;
                        }
                        if (skinButton.getGlobalBounds(mousePos))
                        {
                            currentState = GameState::ChangeSkin;
                        }
                        if (optionsButton.getGlobalBounds(mousePos))
                        {
                            currentState = GameState::Options;
                        }

                        break;
                    }

                    case GameState::Options:
                    {
                        if (backButton.getGlobalBounds(mousePos))
                        {
                            currentState = GameState::Settings;
                        }

                        break;
                    }

                    case GameState::ChangeSkin:
                    {
                        if (backButton.getGlobalBounds(mousePos))
                        {
                            currentState = GameState::Settings;
                        }

                        break;
                    }

                    case GameState::Playing:
                    {
                        if (homeButton.getGlobalBounds(mousePos))
                        {
                            currentState = GameState::StartMenu;
                        }

                        break;
                    }
                    case GameState::GameOver:
                    {
                        if (restartButton.getGlobalBounds(mousePos))
                        {
                            currentState = GameState::Playing;
                        }
                        if (homeButton.getGlobalBounds(mousePos))
                        {
                            currentState = GameState::StartMenu;
                        }

                        break;
                    }
                    }
                }
            }
        }

        switch (currentState)
        {

        // START MENU PAGE
        case GameState::StartMenu:
        {
            sf::Vector2i mousePixel = sf::Mouse::getPosition(window);
            sf::Vector2f mousePos = window.mapPixelToCoords(mousePixel);

            startButton.setColor(sf::Color::White);
            if (startButton.getGlobalBounds(mousePos))
            {
                startButton.setColor(sf::Color::Green);
            }
            settingsButton.setColor(sf::Color::White);
            if (settingsButton.getGlobalBounds(mousePos))
            {
                settingsButton.setColor(sf::Color::Green);
            }

            window.clear();
            window.draw(startBackground);
            startButton.draw(window);
            settingsButton.draw(window);
            window.display();
            break;
        }
        // SETTINGS PAGE
        case GameState::Settings:
        {
            sf::Vector2i mousePixel = sf::Mouse::getPosition(window);
            sf::Vector2f mousePos = window.mapPixelToCoords(mousePixel);

            backButton.setColor(sf::Color::White);
            if (backButton.getGlobalBounds(mousePos))
            {
                backButton.setColor(sf::Color::Green);
            }
            skinButton.setColor(sf::Color::White);
            if (skinButton.getGlobalBounds(mousePos))
            {
                skinButton.setColor(sf::Color::Green);
            }
            optionsButton.setColor(sf::Color::White);
            if (optionsButton.getGlobalBounds(mousePos))
            {
                optionsButton.setColor(sf::Color::Green);
            }

            window.clear();
            window.draw(uiBackground);
            optionsButton.draw(window);
            backButton.draw(window);
            skinButton.draw(window);
            window.display();

            break;
        }

        // OPTIONS PAGE
        case GameState::Options:
        {
            sf::Vector2i mousePixel = sf::Mouse::getPosition(window);
            sf::Vector2f mousePos = window.mapPixelToCoords(mousePixel);

            backButton.setColor(sf::Color::White);
            if (backButton.getGlobalBounds(mousePos))
            {
                backButton.setColor(sf::Color::Green);
            }

            window.clear();
            window.draw(uiBackground);
            backButton.draw(window);
            window.display();
            break;
        }

        // CHANGE SKIN PAGE
        case GameState::ChangeSkin:
        {
            sf::Vector2i mousePixel = sf::Mouse::getPosition(window);
            sf::Vector2f mousePos = window.mapPixelToCoords(mousePixel);

            backButton.setColor(sf::Color::White);
            if (backButton.getGlobalBounds(mousePos))
            {
                backButton.setColor(sf::Color::Green);
            }

            Player  p1(TextureManager::getTexture("player1")), 
                    p2(TextureManager::getTexture("player2")), 
                    p3(TextureManager::getTexture("player3")), 
                    p4(TextureManager::getTexture("player4")), 
                    p5(TextureManager::getTexture("player5"));

            p1.setPosition({WINDOW_W / 4, WINDOW_H / 4});

            // first ship
            if (p1.playerBound().contains(mousePos))
            {

                if (sf::Mouse::isButtonPressed(sf::Mouse::Button::Left))
                {
                    player.newTexture(TextureManager::getTexture("player1"));
                    player.setPosition({WINDOW_W / 2, WINDOW_H / 2});
                }
            }

            // second ship
            p2.setPosition({WINDOW_W / 1.5, WINDOW_H / 1.5});

            if (p2.playerBound().contains(mousePos))
            {
                if (sf::Mouse::isButtonPressed(sf::Mouse::Button::Left))
                {
                    player.newTexture(TextureManager::getTexture("player2"));
                    player.setPosition({WINDOW_W / 2, WINDOW_H / 2});
                }
            }

            // third ship
            p3.setPosition({WINDOW_W / 2, WINDOW_H / 4});

            if (p3.playerBound().contains(mousePos))
            {
                if (sf::Mouse::isButtonPressed(sf::Mouse::Button::Left))
                {
                    player.newTexture(TextureManager::getTexture("player3"));
                    player.setPosition({WINDOW_W / 2, WINDOW_H / 2});
                }
            }

            // forth ship
            p4.setPosition({WINDOW_W / 4, WINDOW_H / 2});

            if (p4.playerBound().contains(mousePos))
            {
                if (sf::Mouse::isButtonPressed(sf::Mouse::Button::Left))
                {
                    player.newTexture(TextureManager::getTexture("player4"));
                    player.setPosition({WINDOW_W / 2, WINDOW_H / 2});
                }
            }

            // fifth ship
            p5.setPosition({WINDOW_W / 2, WINDOW_H / 2});

            if (p5.playerBound().contains(mousePos))
            {
                if (sf::Mouse::isButtonPressed(sf::Mouse::Button::Left))
                {
                    player.newTexture(TextureManager::getTexture("player5"));
                    player.setPosition({WINDOW_W / 2, WINDOW_H / 2});
                }
            }

            window.clear();
            window.draw(uiBackground);
            backButton.draw(window);
            p1.draw(window);
            p2.draw(window);
            p3.draw(window);
            p4.draw(window);
            p5.draw(window);
            window.display();

            break;
        }

        // GAME OVER PAGE
        case GameState::GameOver:
        {
            sf::Vector2i mousePixel = sf::Mouse::getPosition(window);
            sf::Vector2f mousePos = window.mapPixelToCoords(mousePixel);

            homeButton.setColor(sf::Color::White);
            if (homeButton.getGlobalBounds(mousePos))
            {
                homeButton.setColor(sf::Color::Green);
            }
            restartButton.setColor(sf::Color::White);
            if (restartButton.getGlobalBounds(mousePos))
            {
                restartButton.setColor(sf::Color::Green);
            }

            if (score > highScore)
            {
                highScore = score;
                std::ofstream outputFile("assets/highscore.txt");
                if (outputFile.is_open())
                {
                    outputFile << highScore;
                    outputFile.close();
                }
            }
            backgroundMusic.stop();
            gameOverText.setString(
                "            GAME OVER!\n"
                "                SCORE : " +
                std::to_string(score) +
                "\n          HIGHSCORE : " + std::to_string(highScore));
            window.clear();
            window.draw(uiBackground);
            restartButton.draw(window);
            window.draw(gameOverText);
            homeButton.draw(window);
            window.display();

            break;
        }

        // MAIN GAME PAGE
        case GameState::Playing:
        {
            sf::Vector2i mousePixel = sf::Mouse::getPosition(window);
            sf::Vector2f mousePos = window.mapPixelToCoords(mousePixel);

            homeButton.setColor(sf::Color::White);
            if (homeButton.getGlobalBounds(mousePos))
            {
                homeButton.setColor(sf::Color::Green);
            }

            if (score >= milestone + 5)
            {
                astroidCooldown /= 1.1;
                milestone += 5;
            }

            float dt = deltaClock.restart().asSeconds();

            player.movePlayer(dt);

            player.keepPlayerInside();

            // bullet logic
            sf::Vector2f playerPos = player.playerPos();

            if (sf::Keyboard::isKeyPressed(sf::Keyboard::Scan::Space) && fireClock.getElapsedTime().asSeconds() >= bulletCooldown)
            {
                sf::Vector2f dir = player.getPlayerDirection();
                Bullet b;
                lazerSound.play();
                b.fire(playerPos, dir);
                bullet.push_back(b);
                fireClock.restart();
            }

            // erase bullet
            bullet.erase(
                std::remove_if(bullet.begin(), bullet.end(), [](const Bullet &b)
                               { return b.isOffScrean(); }),
                bullet.end());

            // enemy logic
            if (astroidClock.getElapsedTime().asSeconds() >= astroidCooldown)
            {
                Astroid a;
                a.aboutEnemy(TextureManager::getTexture("asteroid"));
                a.enemyPosition();
                astroid.emplace_back(a);
                astroidClock.restart();
            }

            // Erase enemies that collided with player or any bullet
            astroid.erase(
                std::remove_if(astroid.begin(), astroid.end(), [&](const Astroid &a)
                               {
                // Check if enemy hits player
                if(a.forDeletingEnemy(player.playerBound())){
                    currentState = GameState::GameOver;
                    explosionSound.play();
                    return true;
                }

                // Check if enemy hits any bullet
                for (auto it = bullet.begin(); it != bullet.end(); ++it) {
                    if (a.forDeletingEnemy(it->bulletBond())) {
                        bullet.erase(it); // also remove the bullet
                        score += 1;
                        return true;
                    }
                }
                return false; }),
                astroid.end());

            scoreText.setString("SCORE : " + std::to_string(score));
            highscoreText.setString("HIGHSCORE : " + std::to_string(highScore));

            window.clear(sf::Color::White);

            // draw background first
            window.draw(mainBackground);

            // draw home button
            homeButton.draw(window);

            // draw bullet
            for (Bullet &b : bullet)
            {
                b.move(dt);
                b.draw(window);
            }

            // draw player
            player.draw(window);

            // draw enemy
            for (Astroid &a : astroid)
            {
                a.move(player.playerPos(), dt);
                a.draw(window);
            }

            // draw score and highscore
            window.draw(scoreText);
            window.draw(highscoreText);

            window.display();

            break;
        }
        }
    }
}
