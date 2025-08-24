#include "game.h"

#include <filesystem>

std::filesystem::path getProjectRoot() {
    std::filesystem::path path = std::filesystem::current_path();
    if (path.filename() != "SpaceShooter") path = path.parent_path();
    return path;
}

int main()
{
    std::cout << "Working directory: " 
              << std::filesystem::current_path() << "\n";

    std::filesystem::current_path(getProjectRoot());

    std::cout << "Working directory: " 
              << std::filesystem::current_path() << "\n";

    Game game;
    game.run();
    return 0;
}