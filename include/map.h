///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// this file is not needed for now becouse i havent added this feature in the game yet and might not be added any time soon.
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
#pragma once

#include <SFML/Graphics.hpp>
#include <unordered_map>
#include <vector>
#include <string>

struct SpaceObject{
    sf::Sprite sprite;
    sf::Vector2f position;

    SpaceObject(sf::Texture& texture);
};

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

class Map
{
public:
    Map();
    void loadTexture(const sf::Texture &starTexture, const sf::Texture &planetTexture);
    void update(const sf::Vector2f &cameraPos);
    void draw(sf::RenderWindow &window);

private:
    std::string getChunkKey(int cx, int cy) const;
    void generateChunk(int cx, int cy);

    std::unordered_map<std::string, std::vector<SpaceObject>> chunks;
    sf::Texture starTexture, planetTexture;
    int chunkSize;
};