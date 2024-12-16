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
                          const std::vector<sf::Texture>& AdjacentTextures,
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

// Function: clearVisibleGrid
// - turns all tiles of the grid black
void clearVisibleGrid(sf::Sprite (&VisibleGrid)[VISIBLE_HEIGHT][VISIBLE_WIDTH],
                      const sf::Texture& black_texture)
{
   for (int y = 0; y < VISIBLE_HEIGHT; y++)
   {
      for (int x = 0; x < VISIBLE_WIDTH; x++)
      {
         VisibleGrid[y][x].setTexture(black_texture);
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
   int map_column_index = (player.pos_X - 1) + VISIBLE_WIDTH
                          - PLAYER_SCREEN_POS_X;

   // Check if we will index off edge of map on the x
   if (map_column_index < map.map_width && map_column_index > -1)
   {
      for (int y = 0; y < VISIBLE_HEIGHT; y++)
      {
         // Check if we index off edge of map on the y
         if (y + player.pos_Y - PLAYER_SCREEN_POS_Y < map.map_height)
         {
            VisibleGrid[y][VISIBLE_WIDTH - 1].setTexture(Textures[map.MapData[y + player.pos_Y - PLAYER_SCREEN_POS_Y][map_column_index]]);
         }
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
   int map_column_index = player.pos_X - PLAYER_SCREEN_POS_X;

   // Check if we will index off edge of map going left
   if (map_column_index > -1 && map_column_index < map.map_width)
   {
      for (int y = 0; y < VISIBLE_HEIGHT; y++)
      {
         // Check if we index off edge of map on the y
         if (y + player.pos_Y - PLAYER_SCREEN_POS_Y < map.map_height)
         {
            VisibleGrid[y][0].setTexture(Textures[map.MapData[y + player.pos_Y - PLAYER_SCREEN_POS_Y][map_column_index]]);
         }
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

// Function: translateVisibleGridDown()
// - translates tiles within a sprite to its upward neighbor
// - loads in a new row of tiles on the bottom row
void translateVisibleGridDown(sf::Sprite (&VisibleGrid)[VISIBLE_HEIGHT][VISIBLE_WIDTH],
                               const Map& map, const std::vector<sf::Texture>& Textures,
                               Player& player, const sf::Texture& black_texture)
{
   // Shift current tiles down
   for (int y = 0; y < VISIBLE_HEIGHT - 1; y++)
   {
      for (int x = 0; x < VISIBLE_WIDTH; x++)
      {
         // Take tile from the bottom
         VisibleGrid[y][x] = VisibleGrid[y + 1][x];
         // Update the position
         VisibleGrid[y][x].setPosition((x * TILE_WIDTH * getScaleFactor()),
                                        (y * TILE_HEIGHT * getScaleFactor()));
      }
   }

   // Used to index map
   int map_row_index = (player.pos_Y - 1) + VISIBLE_HEIGHT - PLAYER_SCREEN_POS_Y;

   // Check if we will index off edge of map on the y
   if (map_row_index < map.map_height && map_row_index > -1)
   {
      for (int x = 0; x < VISIBLE_WIDTH; x++)
      {
         // Check if we index off edge of map on the x
         if (x + player.pos_X - PLAYER_SCREEN_POS_X < map.map_width)
         {
            VisibleGrid[VISIBLE_HEIGHT - 1][x].setTexture(Textures[map.MapData[map_row_index][x + player.pos_X - PLAYER_SCREEN_POS_X]]);
         }
      }
   }
   // Put in completely black texture if map data doesn't exist
   else
   {
      for (int x = 0; x < VISIBLE_WIDTH; x++)
      {
         VisibleGrid[VISIBLE_HEIGHT - 1][x].setTexture(black_texture);
      }
   }
}

// Function: translateVisibleGridUp()
// - translates tiles within a sprite to its downward neighbor
// - loads in a new row  of tiles on the top row
void translateVisibleGridUp(sf::Sprite (&VisibleGrid)[VISIBLE_HEIGHT][VISIBLE_WIDTH],
                               const Map& map, const std::vector<sf::Texture>& Textures,
                               Player& player, const sf::Texture& black_texture)
{
   // Shift current tiles up
   for (int y = VISIBLE_HEIGHT - 1; y > 0; y--)
   {
      for (int x = 0; x < VISIBLE_WIDTH; x++)
      {
         // Take tile from the top
         VisibleGrid[y][x] = VisibleGrid[y - 1][x];
         // Update the position
         VisibleGrid[y][x].setPosition((x * TILE_WIDTH * getScaleFactor()),
                                        (y * TILE_HEIGHT * getScaleFactor()));
      }
   }

   // Used to index map
   int map_row_index = player.pos_Y - PLAYER_SCREEN_POS_Y;

   // Check if we will index off edge of map on the y
   if (map_row_index < map.map_height && map_row_index > -1)
   {
      for (int x = 0; x < VISIBLE_WIDTH; x++)
      {
         // Check if we index off edge of map on the x
         if (x + player.pos_X - PLAYER_SCREEN_POS_X < map.map_width)
         {
            VisibleGrid[0][x].setTexture(Textures[map.MapData[map_row_index][x + player.pos_X - PLAYER_SCREEN_POS_X]]);
         }
      }
   }
   // Put in completely black texture if map data doesn't exist
   else
   {
      for (int x = 0; x < VISIBLE_WIDTH; x++)
      {
         VisibleGrid[0][x].setTexture(black_texture);
      }
   }
}
