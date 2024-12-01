// constants.h
// Bruce Smith
// 2024-11-28
//
// Contains commonly used variables needed by other files

#pragma once

#include <SFML/Graphics.hpp>   // For window/rendering calls

struct Player
{
   int pos_X; // Player x position within a map
   int pos_Y; // Player y position within a map
   sf::Sprite player_sprite;
   //std::vector<sf::Texture> player_animations (FILL LATER);
};

inline constexpr int VISIBLE_WIDTH = 10;   // 10 tiles wide
inline constexpr int VISIBLE_HEIGHT = 9;   // 9 tiles tall

// Indexing from 0, will store where player is located on screen
// E.x: POS_X = 4 means player is on the 5th x-axis tile
inline constexpr int PLAYER_SCREEN_POS_X = 4;
inline constexpr int PLAYER_SCREEN_POS_Y = 4;

inline constexpr int DEFAULT_WINDOW_WIDTH = 160;   // 160 pixels wide
inline constexpr int DEFAULT_WINDOW_HEIGHT = 144;   // 144 pixels tall

inline constexpr int TILE_WIDTH = 16;   // Defualt tile width
inline constexpr int TILE_HEIGHT = 16;   // Defualt tile height

// Create shorthand variables for valid key input
inline constexpr sf::Keyboard::Key UP_KEY    = sf::Keyboard::Up;
inline constexpr sf::Keyboard::Key DOWN_KEY  = sf::Keyboard::Down;
inline constexpr sf::Keyboard::Key LEFT_KEY  = sf::Keyboard::Left;
inline constexpr sf::Keyboard::Key RIGHT_KEY = sf::Keyboard::Right;

inline constexpr sf::Keyboard::Key NUM1_KEY = sf::Keyboard::Num1;
inline constexpr sf::Keyboard::Key NUM2_KEY = sf::Keyboard::Num2;
inline constexpr sf::Keyboard::Key NUM3_KEY = sf::Keyboard::Num3;
