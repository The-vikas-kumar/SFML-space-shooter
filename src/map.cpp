///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// this file is not needed for now becouse i havent added this feature in the game yet and might not be added any time soon.
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

#include "map.h"

#include <SFML/Graphics.hpp>
#include <iostream>
#include <unordered_map>
#include <vector>
#include <string>

/////////////////////////////////////////////////////////////////////////////////////////////////////

SpaceObject::SpaceObject(sf::Texture& t) : sprite(t){}

/////////////////////////////////////////////////////////////////////////////////////////////////////
std::string Map::getChunkKey(int cx, int cy) const{
    return std::to_string(cx) + "_" + std::to_string(cy);
}

void Map::generateChunk(int cx, int cy){
    auto key = getChunkKey(cx, cy);
    if(chunks.count(key)){
        return;
    }

    // seed rng
    std::srand(cx * 73856093 ^ cy * 19349663);

    std::vector<SpaceObject> objs;
    int numStar = 50 + rand() % 50;
    for(int i = 0; i < numStar; i++){
        SpaceObject s(starTexture); 
        s.position = {
            static_cast<float>(cx * 1000 + std::rand() % chunkSize),
            static_cast<float>(cy * 1000 + std::rand() % chunkSize)
        };
        s.sprite.setPosition(s.position);
        s.sprite.setScale({30.f / static_cast<float>(starTexture.getSize().x), 30.f / static_cast<float>(starTexture.getSize().y)});
        objs.push_back(s);
    }

    if(std::rand() % 10 == 0){
        SpaceObject p(planetTexture);
        p.position = {
            static_cast<float>(cx * 1000 + std::rand() % chunkSize),
            static_cast<float>(cy * 1000 + std::rand() % chunkSize)
        };
        p.sprite.setPosition(p.position);
        p.sprite.setScale({50.f / static_cast<float>(planetTexture.getSize().x), 50.f / static_cast<float>(planetTexture.getSize().y)});
        objs.push_back(p);
    }
    chunks[key] = std::move(objs);
}

Map::Map(){}

void Map::loadTexture(const sf::Texture &starTexture, const sf::Texture &planetTexture){ 
    this->starTexture = starTexture;
    this->planetTexture = planetTexture;
}

void Map::update(const sf::Vector2f& cameraPos){
    int cx = static_cast<int>(cameraPos.x / chunkSize);
    int cy = static_cast<int>(cameraPos.y / chunkSize);
    for(int dx = -1; dx <= 1; ++dx){
        for(int dy = -1; dy <= 1; ++dy){
            generateChunk(cx + dx, cy + dy);
        }
    }
}

void Map::draw(sf::RenderWindow& window){
    for(auto& [key, vec] : chunks){
        for(auto& obj : vec){
            window.draw(obj.sprite);
        }
    }
}