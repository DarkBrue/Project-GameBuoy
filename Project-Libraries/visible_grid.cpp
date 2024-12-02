// visible_grid.cpp
// Bruce Smith
// 2024-12-01
//
// Source file for visible_grid.h
// Houses functions related to VisibleGrid

#include "visible_grid.h"
#include <iostream>   // For debugging

// Function: drawVisibleGrid
// NOTE: MIGHT TAKE LIST OF NPCS ON SCREEN TO RESIZE
void drawVisibleGrid(sf::Sprite (&VisibleGrid)[VISIBLE_HEIGHT][VISIBLE_WIDTH],
                     sf::RenderWindow& window, Player& player)
{
   window.clear();
   // Loop to draw the VisibleGrid
   for (int y = 0; y < VISIBLE_HEIGHT; y++)
   {
      for (int x = 0; x < VISIBLE_WIDTH; x++)
      {
         window.draw(VisibleGrid[y][x]);
      }
   }
   window.draw(player.player_sprite);
   window.display();
}

// Function: initializeVisibleGrid
// - initalizes a grid of textures that will be displayed to the window
// - occurs during hard loading zone (e.g. doors)
void initializeVisibleGrid(sf::Sprite (&VisibleGrid)[VISIBLE_HEIGHT][VISIBLE_WIDTH],
                          const std::vector<sf::Texture>& Textures,
                          const Map& map, const Player& player)
{
   // Used to determine which tiles in the map data are visible

   // These 4 variables will be used to index map data
   // I really don't want to explain it, maybe sometime later
   int start_X = std::max(player.pos_X - PLAYER_SCREEN_POS_X, 0);
   int end_X   = std::min((int)map.map_width,
                          start_X + VISIBLE_WIDTH);
   int start_Y = std::max(player.pos_Y - PLAYER_SCREEN_POS_Y, 0);
   int end_Y   = std::min((int)map.map_height,
                          start_Y + VISIBLE_HEIGHT);

   // Helps translate map coordinates to VisibleGrid coordinates
   int offset_X = PLAYER_SCREEN_POS_X - player.pos_X;
   int offset_Y = PLAYER_SCREEN_POS_Y - player.pos_Y;

   // Cut end short so we don't index off grid
   if (offset_X + end_X - 1 >= VISIBLE_WIDTH) end_X -= offset_X;
   if (offset_Y + end_Y - 1 >= VISIBLE_HEIGHT) end_Y -= offset_Y;

   for (int y = start_Y; y < end_Y; y++)
   {
      for (int x = start_X; x < end_X; x++)
      {
         VisibleGrid[y + offset_Y][x + offset_X].setTexture(Textures[map.MapData[y][x]]);
      }
   }
}

// Function: translateVisibleGridRight()
// - translates tiles within a sprite to its left neighbor
// - loads in a new column of tiles on the far right side
void translateVisibleGridRight(sf::Sprite (&VisibleGrid)[VISIBLE_HEIGHT][VISIBLE_WIDTH],
                               const Map& map, const std::vector<sf::Texture>& Textures,
                               Player& player, const sf::Texture& black_texture)
{
   // Shift current tiles left
   for (int y = 0; y < VISIBLE_HEIGHT; y++)
   {
      for (int x = 0; x < VISIBLE_WIDTH - 1; x++)
      {
         // Take tile from the right
         VisibleGrid[y][x] = VisibleGrid[y][x + 1];
         // Update the position
         VisibleGrid[y][x].setPosition((x * TILE_WIDTH * getScaleFactor()),
                                        (y * TILE_HEIGHT * getScaleFactor()));
      }
   }

   // Used to index map
   int new_column_index = player.pos_X + 6;

   // Check if we will index off edge of map
   if (new_column_index < map.map_width)
   {
      for (int y = 0; y < VISIBLE_HEIGHT; y++)
      {
         VisibleGrid[y][VISIBLE_WIDTH - 1].setTexture(Textures[map.MapData[y][new_column_index]]);
      }
   }
   // Put in completely black texture if map data doesn't exist
   else
   {
      for (int y = 0; y < VISIBLE_HEIGHT; y++)
      {
         VisibleGrid[y][VISIBLE_WIDTH - 1].setTexture(black_texture);
      }
   }
}

// Function: translateVisibleGridLeft()
// - translates tiles within a sprite to its right neighbor
// - loads in a new column of tiles on the far left side
void translateVisibleGridLeft(sf::Sprite (&VisibleGrid)[VISIBLE_HEIGHT][VISIBLE_WIDTH],
                               const Map& map, const std::vector<sf::Texture>& Textures,
                               Player& player, const sf::Texture& black_texture)
{
   // Shift current tiles right
   for (int y = 0; y < VISIBLE_HEIGHT; y++)
   {
      for (int x = VISIBLE_WIDTH - 1; x > 0; x--)
      {
         // Take tile from the left
         VisibleGrid[y][x] = VisibleGrid[y][x - 1];
         // Update the position
         VisibleGrid[y][x].setPosition((x * TILE_WIDTH * getScaleFactor()),
                                        (y * TILE_HEIGHT * getScaleFactor()));
      }
   }

   // Used to index map
   int new_column_index = player.pos_X - 5;

   // Check if we will index off edge of map
   if (new_column_index > -1)
   {
      for (int y = 0; y < VISIBLE_HEIGHT; y++)
      {
         VisibleGrid[y][0].setTexture(Textures[map.MapData[y][new_column_index]]);
      }
   }
   // Put in completely black texture if map index doesn't exist
   else
   {
      for (int y = 0; y < VISIBLE_HEIGHT; y++)
      {
         VisibleGrid[y][0].setTexture(black_texture);
      }
   }
}

