// Bruce Smith
// 2024-11-28
//
// Source file for resize_window.h
// Handles request to resize the window

#include "resize_window.h"
#include <SFML/Graphics.hpp>   // For window/rendering calls

// Function: resizeWindow
// - Check header for details
void resizeWindow(sf::RenderWindow &window, unsigned int scale)
{
   // Default ratio of the screen
   sf::Vector2u DefaultSize = {160, 144};

   // Create new screen ratio
   sf::Vector2u NewSize = {DefaultSize.x * scale,DefaultSize.y * scale};

   window.create(sf::VideoMode(NewSize.x, NewSize.y), "GameBuoy");
}
