// player.h
// Bruce Smith
// 2024-12-17
//
// Header for player.cpp
// Handles anything related to the player

#pragma once

struct Player
{
   int pos_X; // Player x position within a map
   int pos_Y; // Player y position within a map
   sf::Sprite player_sprite;
   //std::vector<sf::Texture> PlayerAnimations (FILL LATER);
};
