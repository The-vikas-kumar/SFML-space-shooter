#pragma once

#include <SFML/Graphics.hpp>
#include <map>
#include <memory>
#include <string>

class TextureManager{
    public:
    static void loadTexture(const std::string& name, const std::string& filePath);
    static sf::Texture& getTexture(const std::string& name);

    private:
    static std::map<std::string, std::unique_ptr<sf::Texture>> textures;
};

