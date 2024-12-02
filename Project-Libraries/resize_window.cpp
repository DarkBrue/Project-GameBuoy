// resize_window.cpp
// Bruce Smith
// 2024-11-28
//
// Source file for resize_window.h
// Handles request to resize the window

#include "resize_window.h"

// Function: resizeWindow
// - Check header for details
// NOTE: MIGHT TAKE LIST OF NPCS ON SCREEN TO RESIZE
void resizeWindow(sf::RenderWindow &window, Player& player, unsigned int scale,
                  sf::Sprite (&VisibleGrid)[VISIBLE_HEIGHT][VISIBLE_WIDTH])
{
   // Default ratio of the screen
   sf::Vector2u DefaultSize = {DEFAULT_WINDOW_WIDTH, DEFAULT_WINDOW_HEIGHT};

   // Create new screen ratio
   sf::Vector2u NewSize = {DefaultSize.x * scale, DefaultSize.y * scale};

   window.create(sf::VideoMode(NewSize.x, NewSize.y), "GameBuoy");

   for (int y = 0; y < VISIBLE_HEIGHT; y++)
   {
      for (int x = 0; x < VISIBLE_WIDTH; x++)
      {
         VisibleGrid[y][x].setScale(scale, scale);
         VisibleGrid[y][x].setPosition(x * TILE_WIDTH * scale,
                                       y * TILE_HEIGHT * scale);
         window.draw(VisibleGrid[y][x]);
      }
   }
   player.player_sprite.setScale(scale, scale);
   player.player_sprite.setPosition(PLAYER_SCREEN_POS_X * TILE_WIDTH * scale,
                                    PLAYER_SCREEN_POS_Y * TILE_HEIGHT * scale);

   window.draw(player.player_sprite);
   window.display();
}
