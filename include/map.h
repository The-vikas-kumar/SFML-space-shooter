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
    void loadTexture(const std::string &startPath, const std::string &planetPath);
    void update(sf::Vector2f &cameraPos);
    void draw(sf::RenderWindow &window);

private:
    std::string getChunkKey(int cx, int cy) const;
    void generateChunk(int cx, int cy);

    std::unordered_map<std::string, std::vector<SpaceObject>> chunks;
    sf::Texture starTexture, planetTexture;
    int chunkSize;
};