// constants.h
// Bruce Smith
// 2024-11-28
//
// Contains commonly used variables needed by other files

#pragma once

#include <SFML/Graphics.hpp>   // For window/rendering calls

inline constexpr int VISIBLE_WIDTH = 10;   // 10 tiles wide
inline constexpr int VISIBLE_HEIGHT = 9;   // 9 tiles tall

inline constexpr int DEFAULT_WINDOW_WIDTH = 160;   // 160 pixels wide
inline constexpr int DEFAULT_WINDOW_HEIGHT = 144;   // 144 pixels tall

inline constexpr int TILE_SIZE = 16;   // Defualt tile size of 16 pixels

// Create shorthand variables for valid key input
inline constexpr sf::Keyboard::Key UP_KEY    = sf::Keyboard::Up;
inline constexpr sf::Keyboard::Key DOWN_KEY  = sf::Keyboard::Down;
inline constexpr sf::Keyboard::Key LEFT_KEY  = sf::Keyboard::Left;
inline constexpr sf::Keyboard::Key RIGHT_KEY = sf::Keyboard::Right;

inline constexpr sf::Keyboard::Key NUM1_KEY = sf::Keyboard::Num1;
inline constexpr sf::Keyboard::Key NUM2_KEY = sf::Keyboard::Num2;
inline constexpr sf::Keyboard::Key NUM3_KEY = sf::Keyboard::Num3;
