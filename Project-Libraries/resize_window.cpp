// resize_window.cpp
// Bruce Smith
// 2024-11-28
//
// Source file for resize_window.h
// Handles request to resize the window

#include <SFML/Graphics.hpp>   // For window/rendering calls
#include "resize_window.h"

// Function: resizeWindow
// - Check header for details
void resizeWindow(sf::RenderWindow &window, unsigned int scale,
                  sf::Sprite (&VisibleGrid)[VISIBLE_HEIGHT][VISIBLE_WIDTH])
{
   // Default ratio of the screen
   sf::Vector2u DefaultSize = {160, 144};

   // Create new screen ratio
   sf::Vector2u NewSize = {DefaultSize.x * scale, DefaultSize.y * scale};

   window.create(sf::VideoMode(NewSize.x, NewSize.y), "GameBuoy");

   for (int y = 0; y < VISIBLE_HEIGHT; y++)
   {
      for (int x = 0; x < VISIBLE_WIDTH; x++)
      {
         VisibleGrid[y][x].setScale(scale, scale);
         VisibleGrid[y][x].setPosition(x * TILE_SIZE * scale,
                                       y * TILE_SIZE * scale);
         window.draw(VisibleGrid[y][x]);
      }
   }
   window.display();
}
