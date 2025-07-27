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
        objs.push_back(s);
    }

    if(std::rand() % 10 == 0){
        SpaceObject p(planetTexture);
        p.position = {
            static_cast<float>(cx * 1000 + std::rand() % chunkSize),
            static_cast<float>(cy * 1000 + std::rand() % chunkSize)
        };
        p.sprite.setPosition(p.position);
        objs.push_back(p);
    }
    chunks[key] = std::move(objs);
}

Map::Map(){}

void Map::loadTexture(const std::string& starPath, const std::string& planetPath){ 
    if(!starTexture.loadFromFile(starPath)){
        std::cerr << "Error: Could not load " << starPath << "\n";
    }
    if(!planetTexture.loadFromFile(planetPath)){
        std::cerr << "Error: Could not load " << planetPath << "\n";
    }
}

void Map::update(sf::Vector2f& cameraPos){

}

void Map::draw(sf::RenderWindow& window){
    
}