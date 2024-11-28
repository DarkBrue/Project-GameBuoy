// Bruce Smith
// 2024-11-28
//
// Header file for resize_window.h
// Handles request to resize the window

#pragma once

#include <SFML/Graphics.hpp>   // For window/rendering calls

// Function: resizeWindow
// - Handles requests to resize the window and its sprites
void resizeWindow(sf::RenderWindow &window, unsigned int scale);
