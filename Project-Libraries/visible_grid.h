// visible_grid.h
// Bruce Smith
// 2024-12-01
//
// Header for visible_grid.cpp
// Houses functions related to VisibleGrid

#include "constants.h"   // Access to commonly used constants
#include "map_loader.h"   // Access to Map struct
#include <vector>   // For vector

// Function: drawVisibleGrid
// NOTE: MIGHT TAKE LIST OF NPCS ON SCREEN TO RESIZE
void drawVisibleGrid(sf::Sprite (&VisibleGrid)[VISIBLE_HEIGHT][VISIBLE_WIDTH],
                     sf::RenderWindow& window, Player& player);

// Function: initializeVisibleGrid
// - initalizes a grid of textures that will be displayed to the window
// - occurs during hard loading zone (e.g. doors)
void initializeVisibleGrid(sf::Sprite (&VisibleGrid)[VISIBLE_HEIGHT][VISIBLE_WIDTH],
                          const std::vector<sf::Texture>& Textures,
                          const Map& map, const Player& player);

// Function: translateVisibleGridRight()
// - translates tiles within a sprite to its left neighbor
// - loads in a new column of tiles on the far right side
void translateVisibleGridRight(sf::Sprite (&VisibleGrid)[VISIBLE_HEIGHT][VISIBLE_WIDTH],
                               const Map& map, const std::vector<sf::Texture>& Textures,
                               Player& player, const sf::Texture& black_texture);
