// resize_window.h
// Bruce Smith
// 2024-11-28
//
// Header file for resize_window.h
// Handles request to resize the window

#pragma once

#include <SFML/Graphics.hpp>   // For window/rendering calls
#include "constants.h"   // Access to commonly used variables

// Function: resizeWindow
// - Handles requests to resize the window and its sprites
void resizeWindow(sf::RenderWindow &window, Player& player, unsigned int scale,
                  sf::Sprite (&VisibleGrid)[VISIBLE_HEIGHT][VISIBLE_WIDTH]);
